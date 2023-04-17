#include <chrono>
#include <thread>
#include <iostream>
#include "rgapi.hpp"

int testid = 0;
#ifdef _WIN32
int WinMain(int argc, char* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
    RGAPI_UseLocalhost = true;
    RGAPI_Load(true, "api-test", "robinbouma#8343");
    RGAPI_GetVersion(true);
    RGAPI_GetServerVersion(true);
    #ifdef _WIN32
    std::string playername = RGAPI_GetName(__argc, __argv);
    std::string session = RGAPI_GetSession(__argc, __argv);
    #else
    std::string playername = RGAPI_GetName(argc, argv);
    std::string session = RGAPI_GetSession(argc, argv);
    #endif
    
    if(playername != "") {
        testid = RGAPI_NameToID(playername);
        std::cout << "id for player: " << testid << "\n";
        std::string myname = RGAPI_IDToName(testid);
        std::cout << "name for id: " << myname << "\n";
        int wrcount = RGAPI_GetWRCount(testid);
        std::cout << "player has " << wrcount << " world records in doolhof, de game!\n";
    }
    else {
        std::cout << "playername is undefined\n";
    }
    if(session != "") {
        std::cout << "session: " << session << "\n";
        if(testid != 0) {
            if(RGAPI_CheckSession(testid, session)) {
                std::cout << "session is correct\n";
                session = RGAPI_NewSession(testid);
                std::cout << "new session: " << session << "\n";
            }
            else {
                std::cout << "session is incorect\n";
            }
        }
        
    }
    else {
        std::cout << "session is undefined\n";
        
    }
    if(playername == "" || session == "") {
        std::cout << "arguments:\n";
        #ifdef _WIN32
        for(int i = 0; i < __argc; i++) {
            std::cout << __argv[i] << "\n";
        
        }
        #else
        for(int i = 0; i < argc; i++) {
            std::cout << argv[i] << "\n";
        
        }
        #endif
       
    }
    return 0;
}

