#include "rgapi.hpp"
#include <iostream>
#include<stdio.h>
#include<string>
#include <curl/curl.h>

CURL* curl;

bool devmode = true;

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

void loadrgapi() {
    std::cout << "loading ricardogames api\n";
}
void getapiversion() {
    curl = curl_easy_init();
    std::cout << "your version is " << RGAPI_VERSION << "\n";

    if(devmode) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=getlatestapiver");
    }
    else {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.ricardogames.ml?r=getlatestapiver");
    }
    
    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
    CURLcode res = curl_easy_perform(curl);

    
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
       std::cout << "latest version is " << response_string << "\n";
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
}
int getidfromname(const char* name) {
    return getidfromname(std::string(name));
}
int getidfromname(std::string name) {
    curl = curl_easy_init();
    
    if(devmode) {
        std::string url = "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=nametoid&name=" + name;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    else {
        std::string url = "https://api.ricardogames.ml/?r=nametoid&name=" + name;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

    std::string response_string;
    std::string header_string;
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
            return num;
        }
    }

   

   return -1;
}
std::string getnamefromid(int id) {
    curl = curl_easy_init();
    
    if(devmode) {
        std::string url = "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=idtoname&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    else {
        std::string url = "https://api.ricardogames.ml/?r=idtoname&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
   
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        return response_string;
    }
    return "ERROR: no player found";

}
std::string getplayername() {
    for(int i = 0; i < __argc; i++) {
        if(__argv[i] == std::string("--name")) {
            return __argv[i + 1];
        }
    }
    return NULL;
}
std::string getplayersession() {
    for(int i = 0; i < __argc; i++) {
        if(__argv[i] == std::string("--session")) {
            return __argv[i + 1];
        }
    }
    return 0;
}