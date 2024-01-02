#include "ServerDatabase.h"

#include <iostream> // 입출력 스트림을 사용하기 위한 헤더 파일
#include <array> // 표준 배열을 사용하기 위한 헤더 파일
#include <map> // 표준 맵을 사용하기 위한 헤더 파일
#include <boost/asio.hpp> // Boost.Asio 라이브러리를 사용하기 위한 헤더 파일
#include <mysql/mysql.h> // MariaDB C API를 사용하기 위한 헤더 파일
#include <nlohmann/json.hpp> // JSON 파싱을 위한 nlohmann/json 라이브러리 헤더 파일
#include <mutex>

using namespace boost::asio;
using json = nlohmann::json;

class AsyncTCPServer {
public:
    // 생성자 (io_service, port번호 매개변수)
    AsyncTCPServer(io_service& io_service, short port)
        :   acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), port)),
            socket_(io_service) 
    {
        StartAccept();
    }
    // 소멸자
    ~AsyncTCPServer() {}

private:
	// queue<pair<std::shared_ptr<ip::tcp::socket>, streambuf> client_queue;

	static const int max_clients_ = 200000;  // 최대 클라이언트 수 200,000
	std::mutex mutex_; // 스레드 간 동기화를 위한 뮤텍스
    int num_clients_ = 0; // 현재 연결된 클라이언트 수
	
	std::array<std::shared_ptr<ip::tcp::socket>, max_clients_> clients_; // 최대 클라이언트 수에 따른 TCP 소켓
	std::map<std::shared_ptr<ip::tcp::socket>, streambuf> buffers_;  // 클라이언트별로 버퍼를 관리하는 맵. 소켓과 연결된 버퍼 저장

	ip::tcp::acceptor acceptor_; // TCP 연결 수용
    ip::tcp::socket socket_; // TCP 소켓

    Database db_;

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
                    db_.SaveToDatabase(message); // DB에 저장
                    // StartRead(client); // 재귀
                    RemoveClient(client);
                }
            });
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
