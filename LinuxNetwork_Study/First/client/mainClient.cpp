#include "ClientJson.h"

#include <iostream> // 입출력 스트림을 사용하기 위한 헤더 파일
#include <fstream> // 파일 입출력을 위한 헤더 파일
#include <string> // 문자열 관련 헤더 파일
#include <sstream> // 문자열 관련 헤더 파일
#include <dirent.h> // 디렉토리 관리 헤더 파일
#include <boost/asio.hpp> // boost::asio 헤더 파일
#include <boost/system/error_code.hpp> // boost error 헤더 파일
#include <nlohmann/json.hpp> // nlohmann/json 헤더 파일

using namespace boost::asio;
using json = nlohmann::json;

// 상수 정의
const int MAX_INTERFACES = 10; // 최대 네트워크 인터페이스 개수
const int MY_IFNAMSIZ = 16; // 네트워크 인터페이스 이름의 최대 길이



// 함수 선언
// std::string readNICFile(const std::string &filePath); // 파일 읽기 함수

class AsyncTCPClient {
private:
    ip::tcp::resolver resolver_; // DNS 해결기 객체
    ip::tcp::socket socket_; // TCP 소켓 객체

    streambuf buffer_; // 데이터 버퍼
    ip::tcp::resolver::iterator endpoint_iterator_;  // 서버 주소 및 포트에 대한 resolver 반복자

    std::shared_ptr<deadline_timer> timer_; // 재시작 시키기 위한 타이머

    Json json_;

public:
    // AsyncTCPClient 클래스 생성자
    AsyncTCPClient(io_service& io_service, const std::string& server_ip, short server_port) : resolver_(io_service), socket_(io_service) {
        // 서버 주소 및 포트로부터 resolver를 초기화하고 연결 시작
        endpoint_iterator_ = resolver_.resolve({ ip::tcp::v4(), server_ip, std::to_string(server_port) });
    }

    // 연결 시작 함수
    void StartConnect() {
        // 비동기적으로 소켓을 서버에 연결하고 연결 결과에 대한 콜백 함수 정의
        async_connect(socket_, endpoint_iterator_, [this](boost::system::error_code ec, ip::tcp::resolver::iterator) {
            if (ec) {
                std::cerr << "서버에 연결 중 오류 발생: " << ec.message() << std::endl;
            } else {
                std::cout << "서버에 연결되었습니다" << std::endl;
                TransferJsonData(json_.makeJson());
            }
        });
    }

	// 데이터 송신 함수
    void TransferJsonData(nlohmann::json json) {
        // json dump 하기
        std::string msg = json.dump() + "\n";

        // 파일 내용을 서버에 비동기적으로 전송하고 전송 결과에 대한 콜백 함수 정의
        async_write(socket_, boost::asio::buffer(msg, msg.size()), [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                std::cout << "데이터 송신 성공" << std::endl;
                socket_.close(); 
                // 서버와의 연결이 성공적으로 종료된 후에 타이머 시작
                ResendDataTimer();
            } else {
                std::cerr << "데이터 송신 중 오류 발생: " << ec.message() << std::endl;
            }
        });
    }

    // 생성된 output.json 파일 읽는 함수    
    std::string FileRead(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "파일을 열 수 없습니다." << std::endl;
            return "";
        }
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

	// 동작 타이머
    void ResendDataTimer() {
        // 타이머 주기
        const int intervalSeconds = 1;

        // 타이머 생성
        timer_ = std::make_shared<deadline_timer>(socket_.get_executor(), boost::posix_time::seconds(intervalSeconds));

        // 타이머 이벤트 핸들러 등록
        timer_->async_wait([this](const boost::system::error_code& ec) {
            if (!ec) {
                // 소켓을 다시 열고 서버에 다시 연결
                socket_.open(ip::tcp::v4());
                StartConnect();
            }
        });
    }
};

int main() {
    // JSON 객체 생성
    json systemdata;

    try {
        // Boost.Asio IO 서비스 객체 생성
        boost::asio::io_service io_service;

        // 비동기 TCP 클라이언트 객체 생성 및 서버에 연결 시도
        AsyncTCPClient client(io_service, "192.168.56.101", 12345);
        client.StartConnect();

        // 주기적으로 정보 송신을 시작
        client.ResendDataTimer();

        // IO 서비스 루프 시작
        io_service.run();
    } catch (std::exception& e) {
        // 예외 발생 시 오류 메시지 출력
        std::cerr << "예외 발생: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}