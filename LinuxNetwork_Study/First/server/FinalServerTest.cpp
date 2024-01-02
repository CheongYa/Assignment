#include <iostream> // 입출력 스트림을 사용하기 위한 헤더 파일
#include <array> // 표준 배열을 사용하기 위한 헤더 파일
#include <map> // 표준 맵을 사용하기 위한 헤더 파일
#include <boost/asio.hpp> // Boost.Asio 라이브러리를 사용하기 위한 헤더 파일
#include <mysql/mysql.h> // MariaDB C API를 사용하기 위한 헤더 파일
#include <nlohmann/json.hpp> // JSON 파싱을 위한 nlohmann/json 라이브러리 헤더 파일

using namespace boost::asio;
using json = nlohmann::json;

class AsyncTCPServer {
public:
    // 생성자 (io_service, port번호 매개변수)
    AsyncTCPServer(io_service& io_service, short port)
        :   acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
            socket_(io_service) 
    {
        ConnectToMariaDB();
        StartAccept();
    }
    // 소멸자
    ~AsyncTCPServer() {
        // MariaDB 연결 해제
        if (db_connection_ != nullptr) {
            mysql_close(db_connection_);
            std::cout << "MariaDB 연결 해제" << std::endl;
        }
    }

private:
	// queue<pair<std::shared_ptr<ip::tcp::socket>, streambuf> client_queue;

	static const int max_clients_ = 200000;  // 최대 클라이언트 수 200,000
	std::mutex mutex_; // 스레드 간 동기화를 위한 뮤텍스
    int num_clients_ = 0; // 현재 연결된 클라이언트 수
	
	std::array<std::shared_ptr<ip::tcp::socket>, max_clients_> clients_; // 최대 클라이언트 수에 따른 TCP 소켓
	std::map<std::shared_ptr<ip::tcp::socket>, streambuf> buffers_;  // 클라이언트별로 버퍼를 관리하는 맵. 소켓과 연결된 버퍼 저장

	ip::tcp::acceptor acceptor_; // TCP 연결 수용
    ip::tcp::socket socket_; // TCP 소켓
    
	MYSQL* db_connection_; // MariaDB 연결 핸들러


    // 새로운 클라이언트 연결 수락 및 비동기 통신 시작 함수
    void StartAccept() {
        // acceptor_ = 비동기적으로 들어오는 연결 수락
        // 수락된 이후 람다 함수 호출
        acceptor_.async_accept(socket_,
            [this](boost::system::error_code ec) {
                if(ec) {
                    std::cerr << "연결 수락 중 오류 발생: " << ec.message() << std::endl;
                } else {
                    // 새로운 클라이언트를 관리하기 위해 소켓을 배열에 추가
                    auto new_socket = std::make_shared<ip::tcp::socket>(std::move(socket_));
                    AddClient(new_socket);

                    // 다음 클라이언트 연결 대기
                    StartAccept();

                    // 현재 클라이언트에 대한 비동기 통신 시작
                    StartRead(clients_[num_clients_ - 1]);
                }
        });
    }
 
    // 새로운 클라이언트 배열에 추가 및 연결 메시지 출력 함수
    void AddClient(std::shared_ptr<ip::tcp::socket> client) {
        std::lock_guard<std::mutex> lock(mutex_);
    
        if (num_clients_ < max_clients_) {
            clients_[num_clients_] = client;
            num_clients_++;
    
            // 연결 메시지 출력
            std::cout << client->remote_endpoint().address().to_string() + "와 연결되었습니다." << std::endl;
        } else {
            std::cerr << "최대 클라이언트 수를 초과하여 연결을 수락할 수 없습니다." << std::endl;
            client->close();
        }

    }
 
    // 클라이언트에 대한 비동기 읽기 시작 함수
    void StartRead(std::shared_ptr<ip::tcp::socket> client) {
        // 클라이언트에 연관된 버퍼를 가져옴
        auto& buffer = buffers_[client];

        // \n를 읽을 때까지 비동기적으로 읽음
        async_read_until(*client, buffer, '\n',
            [this, client, &buffer](boost::system::error_code ec, std::size_t length) {
                if (ec) {
                    RemoveClient(client);
                } else {
                    std::istream is(&buffer); // 입력 스트림 생성
                    std::string message;
                    std::getline(is, message); // is에서 \n이 나타날 때까지 message에 저장
                    SaveToDatabase(message); // DB에 저장
                    StartRead(client); // 재귀
                }
            });
    }

    // MariaDB 연결 함수
    void ConnectToMariaDB() {
        db_connection_ = mysql_init(nullptr);
        if (db_connection_ == nullptr) {
            std::cerr << "MariaDB 연결 초기화 실패" << std::endl;
            exit(1);
        }

        const char* host = "localhost";
        const char* user = "root";
        const char* password = "1234";
        const char* database = "servertest";
        unsigned int port = 3306;

        if (mysql_real_connect(db_connection_, host, user, password, database, port, nullptr, 0) == nullptr) {
            std::cerr << "MariaDB 연결 실패: " << mysql_error(db_connection_) << std::endl;
            exit(1);
        }

        std::cout << "MariaDB 연결 성공" << std::endl;
    }

    // 데이터베이스에 정보 저장 함수
    void SaveToDatabase(const std::string& message) {
       // 예시: JSON으로 가정하고 데이터베이스에 저장하는 코드
       try {
            auto j = json::parse(message);
            std::lock_guard<std::mutex> lock(mutex_);
            
            if (j.find("CPU") != j.end()) {
               SaveCpuToDatabase(j["CPU"]);
            }
            if (j.find("NIC") != j.end()) {
               SaveNicToDatabase(j["NIC"]);
            }
            if (j.find("Memory") != j.end()) {
               SaveMemoryToDatabase(j["Memory"]);
            }
            if (j.find("Disk") != j.end()) {
               SaveDiskToDatabase(j["Disk"]);
            }

           std::cout << "데이터베이스에 저장 완료" << std::endl;
        } catch (const nlohmann::detail::parse_error& e) { // JSON 파싱 오류 캐치
           std::cerr << "JSON 파싱 오류: " << e.what() << std::endl;
           std::cerr << "오류가 발생한 메시지: " << message << std::endl;
        } catch (const std::exception& e) { // DB 오류 캐치
           std::cerr << "데이터베이스 저장 실패: " << e.what() << std::endl;
           std::cerr << "오류가 발생한 메시지: " << message << std::endl;
        }
    }

    // CPU 데이터 추출 및 저장 함수
    void SaveCpuToDatabase(const json& cpuData) {
        for (const auto& processor : cpuData) {
            // 각 프로세서 정보 추출
            std::string cores = processor["Cores"].get<std::string>();
            std::string model = processor["Model"].get<std::string>();
            std::string siblings = processor["Siblings"].get<std::string>();
            
            // 쿼리 생성 후 DB에 데이터 저장
            std::string query = "INSERT INTO cpu_table (cores, model, siblings) VALUES ('" + cores + "', '" + model + "', '" + siblings + "')";
            if (mysql_query(db_connection_, query.c_str()) != 0) {
                std::cerr << "CPU 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(db_connection_) << std::endl;
            }
        }
    }

    // NIC 데이터 추출 및 저장 함수
    void SaveNicToDatabase(const json& nicData) {
        for (const auto& nic : nicData) {
            // 각 nic 정보 추출
            std::string interface = nic["Interface"].get<std::string>();
            std::string mac_address = nic["MAC Address"].get<std::string>();
            std::string operational_state = nic["Operational State"].get<std::string>();
            std::string speed = nic["Speed"].get<std::string>();

            // 쿼리 생성 후 DB에 데이터 저장
            std::string query = "INSERT INTO nic_table (interface, mac_address, operational_state, speed) VALUES ('" + interface + "', '" + mac_address + "', '" + operational_state + "', '" + speed + "')";
            int queryResult = mysql_query(db_connection_, query.c_str());
            if (queryResult != 0) {
                std::cerr << "NIC 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(db_connection_) << std::endl;
            }
        }
    }

    // Memory 데이터 추출 및 저장 함수
    void SaveMemoryToDatabase(const json& memoryData) {
        for (const auto& memory : memoryData) {
            // 각 memory 정보 추출
            std::string active = memory["Active"].get<std::string>();
            std::string active_anon = memory["Active(anon)"].get<std::string>();
            std::string active_file = memory["Active(file)"].get<std::string>();
            std::string anonHugePages = memory["AnonHugePages"].get<std::string>();
            std::string anonPages = memory["AnonPages"].get<std::string>();
            std::string bounce = memory["Bounce"].get<std::string>();
            std::string buffers = memory["Buffers"].get<std::string>();
            std::string cached = memory["Cached"].get<std::string>();
            std::string cmaFree = memory["CmaFree"].get<std::string>();
            std::string cmaTotal = memory["CmaTotal"].get<std::string>();
            std::string commitLimit = memory["CommitLimit"].get<std::string>();
            std::string committed_AS = memory["Committed_AS"].get<std::string>();
            std::string directMap2M = memory["DirectMap2M"].get<std::string>();
            std::string directMap4k = memory["DirectMap4k"].get<std::string>();
            std::string dirty = memory["Dirty"].get<std::string>();
            std::string fileHugePages = memory["FileHugePages"].get<std::string>();
            std::string filePmdMapped = memory["FilePmdMapped"].get<std::string>();
            std::string hardwareCorrupted = memory["HardwareCorrupted"].get<std::string>();
            std::string hugePages_Free = memory["HugePages_Free"].get<std::string>();
            std::string hugePages_Rsvd = memory["HugePages_Rsvd"].get<std::string>();
            std::string hugePages_Surp = memory["HugePages_Surp"].get<std::string>();
            std::string hugePages_Total = memory["HugePages_Total"].get<std::string>();
            std::string hugepagesize = memory["Hugepagesize"].get<std::string>();
            std::string hugetlb = memory["Hugetlb"].get<std::string>();
            std::string inactive = memory["Inactive"].get<std::string>();
            std::string inactive_anon = memory["Inactive(anon)"].get<std::string>();
            std::string inactive_file = memory["Inactive(file)"].get<std::string>();
            std::string kreclaimable = memory["KReclaimable"].get<std::string>();
            std::string kernelStack = memory["KernelStack"].get<std::string>();
            std::string mapped = memory["Mapped"].get<std::string>();
            std::string memAvailable = memory["MemAvailable"].get<std::string>();
            std::string memFree = memory["MemFree"].get<std::string>();
            std::string memTotal = memory["MemTotal"].get<std::string>();
            std::string mlocked = memory["Mlocked"].get<std::string>();
            std::string nFS_Unstable = memory["NFS_Unstable"].get<std::string>();
            std::string pageTables = memory["PageTables"].get<std::string>();
            std::string percpu = memory["Percpu"].get<std::string>();
            std::string sReclaimable = memory["SReclaimable"].get<std::string>();
            std::string sUnreclaim = memory["SUnreclaim"].get<std::string>();
            std::string shmem = memory["Shmem"].get<std::string>();
            std::string shmemHugePages = memory["ShmemHugePages"].get<std::string>();
            std::string shmemPmdMapped = memory["ShmemPmdMapped"].get<std::string>();
            std::string slab = memory["Slab"].get<std::string>();
            std::string swapCached = memory["SwapCached"].get<std::string>();
            std::string swapFree = memory["SwapFree"].get<std::string>();
            std::string swapTotal = memory["SwapTotal"].get<std::string>();
            std::string unevictable = memory["Unevictable"].get<std::string>();
            std::string vmallocChunk = memory["VmallocChunk"].get<std::string>();
            std::string vmallocTotal = memory["VmallocTotal"].get<std::string>();
            std::string vmallocUsed = memory["VmallocUsed"].get<std::string>();
            std::string writeback = memory["Writeback"].get<std::string>();
            std::string writebackTmp = memory["WritebackTmp"].get<std::string>();
            std::string zswap = memory["Zswap"].get<std::string>();
            std::string zswapped = memory["Zswapped"].get<std::string>();

			// 쿼리 생성 후 DB에 데이터 저장
            std::string query = "INSERT INTO memory_table (active, active_anon, active_file, anonHugePages, anonPages, bounce, buffers, cached, cmaFree, cmaTotal, commitLimit, committed_AS, directMap2M, directMap4k, dirty, fileHugePages, filePmdMapped, hardwareCorrupted, hugePages_Free, hugePages_Rsvd, hugePages_Surp, hugePages_Total, hugepagesize, hugetlb, inactive, inactive_anon, inactive_file, kreclaimable, kernelStack, mapped, memAvailable, memFree, memTotal, mlocked, nFS_Unstable, pageTables, percpu, sReclaimable, sUnreclaim, shmem, shmemHugePages, shmemPmdMapped, slab, swapCached, swapFree, swapTotal, unevictable, vmallocChunk, vmallocTotal, vmallocUsed, writeback, writebackTmp, zswap, zswapped) VALUES ('" + active + "', '" + active_anon + "', '" + active_file + "', '" + anonHugePages + "', '" + anonPages + "', '" + bounce + "', '" + buffers + "', '" + cached + "', '" + cmaFree + "', '" + cmaTotal + "', '" + commitLimit + "', '" + committed_AS + "', '" + directMap2M + "', '" + directMap4k + "', '" + dirty + "', '" + fileHugePages + "', '" + filePmdMapped + "', '" + hardwareCorrupted + "', '" + hugePages_Free + "', '" + hugePages_Rsvd + "', '" + hugePages_Surp + "', '" + hugePages_Total + "', '" + hugepagesize + "', '" + hugetlb + "', '" + inactive + "', '" + inactive_anon + "', '" + inactive_file + "', '" + kreclaimable + "', '" + kernelStack + "', '" + mapped + "', '" + memAvailable + "', '" + memFree + "', '" + memTotal + "', '" + mlocked + "', '" + nFS_Unstable + "', '" + pageTables + "', '" + percpu + "', '" + sReclaimable + "', '" + sUnreclaim + "', '" + shmem + "', '" + shmemHugePages + "', '" + shmemPmdMapped + "', '" + slab + "', '" + swapCached + "', '" + swapFree + "', '" + swapTotal + "', '" + unevictable + "', '" + vmallocChunk + "', '" + vmallocTotal + "', '" + vmallocUsed + "', '" + writeback + "', '" + writebackTmp + "', '" + zswap + "', '" + zswapped + "')";
            int queryResult = mysql_query(db_connection_, query.c_str());
            if (queryResult != 0) {
                std::cerr << "Memory 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(db_connection_) << std::endl;
            }
        }
    }

    // Disk 데이터 추출 및 저장 함수
    void SaveDiskToDatabase(const json& diskData) {
        for (const auto& disk : diskData) {
            std::string device = disk["Device"].get<std::string>();
            int completed_io_operations = disk["Completed I/O operations"].get<int>();
            int merged_io_operations = disk["Merged I/O operations"].get<int>();
            int time_spent_reading = disk["Time spent reading (ms)"].get<int>();
            int time_spent_writing = disk["Time spent writing (ms)"].get<int>();
            int total_sectors = disk["Total sectors"].get<int>();
            
            // 쿼리 생성 후 DB에 데이터 저장
            std::stringstream query;
            query << "INSERT INTO disk_table (device, completed_io_operations, merged_io_operations, time_spent_reading, time_spent_writing, total_sectors) VALUES ('"
                  << device << "', " << completed_io_operations << ", " << merged_io_operations << ", " << time_spent_reading << ", " << time_spent_writing << ", " << total_sectors << ")";
            int queryResult = mysql_query(db_connection_, query.str().c_str());
            if (queryResult != 0) {
                std::cerr << "Disk 정보를 데이터베이스에 저장하는 중 오류 발생: " << mysql_error(db_connection_) << std::endl;
            }
        }
    }
   
    // 클라이언트 배열에서 제거 및 연결 종료 메시지 출력 함수
    void RemoveClient(std::shared_ptr<ip::tcp::socket> client) {
        for (int i = 0; i < max_clients_; ++i) {
            // 해당하는 클라이언트 색출 후 제거
            if (clients_[i] == client) {
                clients_[i] = nullptr;
                num_clients_--;

                // 연결 종료 메시지 출력
                std::cout << client->remote_endpoint().address().to_string() + "와 연결이 종료되었습니다." << std::endl;

                boost::system::error_code ec;
				buffers_.erase(client);
                client->shutdown(ip::tcp::socket::shutdown_both, ec);
                client->close(ec);
			    
                break;
            }
        }
    }
};

int main() {
    try {
        boost::asio::io_service io_service; // io_service 객체 생성
        AsyncTCPServer server(io_service, 12345); // AsyncTCPServer 클래스의 객체 생성(객체, 포트번호)
        while(true) {
            io_service.run(); // 이벤트 루프 시작
        }
    } catch (std::exception& e) {
        std::cerr << "예외 발생: " << e.what() << std::endl;
    }

    return 0;
}
