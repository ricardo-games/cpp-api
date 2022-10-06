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

    if(devmode) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=getlatestapiver");
    }
    else {
        curl_easy_setopt(curl, CURLOPT_URL, "http://api.ricardogames.ml?r=getlatestapiver");
    }
    
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
        if(std::string(RGAPI_VERSION) == response_string) {
            std::cout << "api is up to date (" << response_string << ")\n";
        }
        else {
            std::cout << "api version is outdated. if you are the developer please update the api.\n";
            std::cout << "your version is " << RGAPI_VERSION << "\n";
        	std::cout << "latest version is " << response_string << "\n";
        }
       
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
        std::string url = "http://api.ricardogames.ml/?r=nametoid&name=" + name;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

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
        std::string url = "http://api.ricardogames.ml/?r=idtoname&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

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
    curl = curl_easy_init();
    
    if(devmode) {
        std::string url = "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=getwrcount&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    else {
        std::string url = "http://api.ricardogames.ml/?r=idtoname&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

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
            return num;
        }
    }
    return -1;
}
std::string newsession(int id, std::string session) {
    curl = curl_easy_init();
    
    if(devmode) {
        std::string url = "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=newsession&session=" + session + "&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    else {
        std::string url = "http://api.ricardogames.ml/?r=newsession&session=" + session + "&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

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
            return response_string;
        }
        else {
            std::cout << response_string << "\n";
        }
    }
    return "empty";
}
bool checksession(int id, std::string session) {
    curl = curl_easy_init();
    
    if(devmode) {
        std::string url = "http://localhost/ricardogames-site/api.ricardogames.ml/htdocs/?r=checksession&session=" + session + "&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
    else {
        std::string url = "http://api.ricardogames.ml/?r=checksession&session=" + session + "&id=" + std::to_string(id);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }

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
            return true;
       }
        if(response_string != "false") {
            std::cout << response_string << "\n";
        }
    }
    return false;
}