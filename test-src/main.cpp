#include <chrono>
#include <thread>
#include <iostream>
#include "rgapi.hpp"

int WinMain(int argc, char* argv[]) {
    loadrgapi();
    getapiversion();
    int testid = getidfromname(std::string("robin"));
    std::cout << "id for robin: " << testid << "\n";
    std::string myid = getnamefromid(2);
    std::cout << "name for id 2: " << myid << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return 0;
}

