#include "rgapi.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <curl/curl.h>

CURL* curl;

bool devmode = true;

std::string url;

std::string apiver;
std::string serverapiver;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

void loadrgapi() {
    if(devmode) {
        url = "http://localhost/ricardogames-site/api/?v=" + std::string(RGAPI_SERVER_VERSION);
    }
    else {
        url = "http://api.ricardogames.nl/?v=" + std::string(RGAPI_SERVER_VERSION);
    }
    std::cout << "ricardogames api version " << RGAPI_VERSION << " loaded.\n";
}
bool getapiversion(bool dologging) {
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, (url + "&r=getlatestapiver&language=cpp").c_str());
    
    std::string response_string;
    std::string header_string;

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
       
    CURLcode res = curl_easy_perform(curl);

    bool uptodate = false;
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        apiver = response_string;
        if(std::string(RGAPI_VERSION) == response_string) {
            uptodate = true;
            if(dologging) {
                std::cout << "api is up to date (" << response_string << ")\n";
            }
        }
        else {
            std::cout << "api version is outdated. if you are the developer please update the api.\n";
            std::cout << "your version is: " << RGAPI_VERSION << "\n";
        	std::cout << "latest version is: " << response_string << "\n";
        }
       
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
    return uptodate;
}
bool getserverapiversion(bool dologging) {
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, (url + "&r=getlatestapiver").c_str());
    
    std::string response_string;
    std::string header_string;

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
       
    CURLcode res = curl_easy_perform(curl);

    bool uptodate = false;
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        serverapiver = response_string;
        if(std::string(RGAPI_SERVER_VERSION) == response_string) {
            if(dologging) {
                std::cout << "api is using the latest server api version (" << response_string << ")\n";
            }
            
            uptodate = true;
        }
        else {
            std::cout << "your api library is using an old server api version\n";
            std::cout << "if you are the developer please update before this version gets depricated\n";
            std::cout << "your version is: " << RGAPI_SERVER_VERSION << "\n";
            std::cout << "latest version on the server is: " << response_string << "\n";
            
        }
       
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
    return uptodate;
}
int getidfromname(const char* name) {
    return getidfromname(std::string(name));
}
int getidfromname(std::string name) {
    curl = curl_easy_init();
    
   
    std::string requesturl = url + "&r=nametoid&name=" + name;
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());


    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
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

            if(devmode) {
                std::cout << num << "\n";
            }
            curl_easy_cleanup(curl);
            return num;
        }
    }

   
    curl_easy_cleanup(curl);
    return -1;
}
std::string getnamefromid(int id) {
    curl = curl_easy_init();
    
    std::string requesturl = url + "&r=idtoname&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());
    

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        curl_easy_cleanup(curl);
        return response_string;
    }
    curl_easy_cleanup(curl);
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
    curl = curl_easy_init();
    
    
    std::string requesturl = url + "&r=getwrcount&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());
   

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
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
            curl_easy_cleanup(curl);
            return num;
        }
    }
    curl_easy_cleanup(curl);
    return -1;
}
std::string newsession(int id, std::string session) {
    curl = curl_easy_init();
    
   
    std::string requesturl = url + "&r=newsession&session=" + session + "&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        if(response_string.length() == 32) {
            curl_easy_cleanup(curl);
            return response_string;
        }
        else {
            std::cout << response_string << "\n";
        }
    }
    curl_easy_cleanup(curl);
    return "ERROR";
}
bool checksession(int id, std::string session) {
    curl = curl_easy_init();
    
    
   std::string requesturl = url + "&r=checksession&session=" + session + "&id=" + std::to_string(id);
    curl_easy_setopt(curl, CURLOPT_URL, requesturl.c_str());

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
       if(response_string == "true") {
            curl_easy_cleanup(curl);
            return true;
       }
        if(response_string != "false") {
            std::cout << response_string << "\n";
        }
    }
    curl_easy_cleanup(curl);
    return false;
}