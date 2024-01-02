#include "swdata.h"
#include "hwdata.h"

#include <iostream>
#include <unistd.h>

int main(){
    HWdata hw;
    SWdata sw;

    while (true)
    {
        try {
            std::cout << "HW와 SW정보를 수집하여 DB에 저장합니다." << std::endl;
            hw.startHwDB();
            sw.startSwDB();

            sleep(10);
        } catch (const std::exception& e) {
            // 예외가 발생하면 처리
            std::cerr << "에러 발생: " << e.what() << std::endl;
            break;
        }
    }
    
    return 0;
}