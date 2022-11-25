#include "rgapi.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <curl/curl.h>

CURL* curl;

bool uselocalhost;

std::string url;

std::string apiver;
std::string serverapiver;

std::string response_string;
std::string header_string;

std::string fullapiver;
std::string fullserverver;


size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

void loadrgapi() {
    fullapiver = std::string(RGAPI_MAJOR_VERSION) + "." + std::string(RGAPI_MINOR_VERSION) + "." + std::string(RGAPI_FIX_VERSION);
    fullserverver = std::string(RGAPI_SERVER_MAJOR_VERSION) + "." + std::string(RGAPI_SERVER_MINOR_VERSION) + "." + std::string(RGAPI_SERVER_FIX_VERSION);
    if(uselocalhost) {
        url = "http://localhost/ricardogames-site/api/?v=" + fullserverver;
    }
    else {
        url = "https://api.ricardogames.nl/?v=" + fullserverver;
    }
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

   
    
    std::cout << "initialized ricardogames api " << fullapiver << "\n";
}
void quitrgapi() {
    curl_easy_cleanup(curl);
}
int getapiversion(bool dologging) {
    

    curl_easy_setopt(curl, CURLOPT_URL, (url + "&r=getlatestapiver&language=cpp").c_str());
    
    response_string = "";
    header_string = "";
    
    CURLcode res = curl_easy_perform(curl);
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        apiver = response_string;
        if(isdigit(response_string[0])) {
            if(fullapiver == response_string) {
                if(dologging) {
                    std::cout << "api is up to date (" << response_string << ")\n";
                }
                return 1;
            }
            else if(response_string == "ERROR: version is incorrect or depricated") {
                if(dologging) {
                    std::cout << "api version is depricated. if you are the developer please update the api.\n";
                    std::cout << "your version is: " << fullapiver << "\n";
                    std::cout << "latest version is: " << response_string << "\n";
                }
            }
            else {
                //FIXME: create correct version parsing
                int majorver = -1;
                int minorver = -1;
                int fixver = -1;
                int tempval = 0;
                for(int i = 0; i < response_string.length(); i++) {
                    if(majorver == -1) {
                        if(str == ".") {
                            std::cout << "test: " << tempval << "\n";
                            majorver = tempval;
                            tempval = 0;
                        }
                        else {
                            tempval = tempval * 10;
                            
                            tempval += stoi(str);
                        }
                    }
                    else if(minorver == -1) {
                        if(str == ".") {
                            minorver = tempval;
                            tempval = 0;
                        }
                        else {
                            tempval = tempval * 10;
                            
                            tempval += stoi(str);
                        }
                    }
                    else {
                        if(str == ".") {
                            fixver = tempval;
                            tempval = 0;
                        }
                        else {
                            tempval = tempval * 10;
                            
                            tempval += stoi(str);
                        }
                    }
                    std::cout << str;
                }
                std::cout << "\nvertest: " << majorver << "." << minorver << "." << fixver << "\n";
                
            }
            /*else {
                if(dologging) {
                    std::cout << "api version is outdated. if you are the developer please update the api.\n";
                    std::cout << "your version is: " << fullapiver << "\n";
                    std::cout << "latest version is: " << response_string << "\n";
                }
                return 0;

            }*/

        }
        
       
    }

    return -1;
}
int getserverapiversion(bool dologging) {

    curl_easy_setopt(curl, CURLOPT_URL, (url + "&r=getlatestapiver").c_str());

    response_string = "";
    header_string = "";
       
    CURLcode res = curl_easy_perform(curl);
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        serverapiver = response_string;
        if(fullserverver == response_string) {
            if(dologging) {
                std::cout << "api is using the latest server api version (" << response_string << ")\n";
            }
            return 1;
        }
        else {
            if(response_string == "ERROR: version is incorrect or depricated") {
                if(dologging) {
                    std::cout << "your api library is using an depricated server api version\n";
                    std::cout << "your version is: " << fullserverver << "\n";
                    std::cout << "latest version on the server is: " << response_string << "\n";
                }
            }
            else {
                 if(dologging) {
                    std::cout << "your api library is using an old server api version\n";
                    std::cout << "if you are the developer please update before this version gets depricated\n";
                    std::cout << "your version is: " << fullserverver << "\n";
                    std::cout << "latest version on the server is: " << response_string << "\n";
                }
                return 0;

            }
           
        }
       
    }
    return -1;
}
int getidfromname(const char* name) {
    return getidfromname(std::string(name));
}
int getidfromname(std::string name) {
    
   
    std::string requesturl = url + "&r=nametoid&name=" + name;
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());
    response_string = "";
    header_string = "";
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        if(!isdigit(response_string[0])) {
            std::cout << response_string << "\n";
        }
        else {
            int num = stoi(response_string);
            return num;
        }
    }

   
    return -1;
}
std::string getnamefromid(int id) {
    
    std::string requesturl = url + "&r=idtoname&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());

    response_string = "";
    header_string = "";
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        return response_string;
    }
    return "ERROR: no player found";

}
std::string getplayername(int argc, char* argv[]) {
    for(int i = 0; i < argc - 1; i++) {
        if(std::string(argv[i]) == std::string("--name")) {
            if(std::string(argv[i + 1]) != std::string("--session")) {
                return argv[i + 1];
            }
        }
    }
    return "";
}
std::string getplayersession(int argc, char* argv[]) {
    for(int i = 0; i < argc - 1; i++) {
        if(std::string(argv[i]) == std::string("--session")) {
            if(std::string(argv[i + 1]) != std::string("--name")) {
                return argv[i + 1];
            }
        }
    }
    return "";
}
int getwrcount(int id) {
    
    
    std::string requesturl = url + "&r=getwrcount&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());
   

    response_string = "";
    header_string = "";
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        if(!isdigit(response_string[0])) {
            std::cout << response_string << "\n";
        }
        else {
            int num = stoi(response_string);
            return num;
        }
    }
    return -1;
}
std::string newsession(int id, std::string session) {
    
   
    std::string requesturl = url + "&r=newsession&session=" + session + "&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());

    response_string = "";
    header_string = "";
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        if(response_string.length() == 32) {
            return response_string;
        }
        else {
            std::cout << response_string << "\n";
        }
    }
    return "ERROR";
}
bool checksession(int id, std::string session) {
    
    
    std::string requesturl = url + "&r=checksession&session=" + session + "&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());

    response_string = "";
    header_string = "";
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
       if(response_string == "true") {
            return true;
       }
        if(response_string != "false") {
            std::cout << response_string << "\n";
        }
    }
    return false;
}