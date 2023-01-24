#include "rgapi.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
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

std::string RGAPI_LatestVer;
std::string RGAPI_LatestServerVer;

struct curl_slist *list = NULL;


size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

void RGAPI_Load(bool dologging, std::string description, std::string contactinfo) {
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

    if(contactinfo == "") {
        contactinfo = "no contact info set";
        std::cout << "no contact info set, this program will be banned if it abuses the api\n";
        std::cout << "if you are the developer, please pass trough contact info so i can contact you if something is wrong.\n";
    }
    if(description == "") {
        description = "no description set";
        std::cout << "no description set, if you are the developer please add one.\n";
        std::cout << "with a description i can monitor mor easily and will ban your app less quickly\n";
        std::cout << "it is best tho have the same name as the name on the launcher\n";
    }

    list = curl_slist_append(list, ("contactinfo: " + contactinfo).c_str());
    list = curl_slist_append(list, ("description: " + description).c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);


    if(dologging) {
         std::cout << "initialized ricardogames api " << fullapiver << "\n";
    }
}
void RGAPI_Load(bool dologging, const char* description, const char* contactinfo) {
    RGAPI_Load(dologging, std::string(description), std::string(contactinfo));
}
void RGAPI_Quit() {
    curl_easy_cleanup(curl);
}
int RGAPI_GetVersion(bool dologging) {
    

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
            RGAPI_LatestVer = response_string;
            if(fullapiver == response_string) {
                if(dologging) {
                    std::cout << "api is up to date (" << response_string << ")\n";
                }
                return 1;
            }
            else {
                int version[3];
                int localversion[3];
                std::string verstr = response_string;
                for(int i = 0; i < 3; i++) {
                    size_t pos = verstr.find(".");
                    std::string vernum = verstr.substr(0, pos);
                    std::istringstream verstrm(vernum);
                    verstrm >> version[i];
                    
                    verstr.erase(0, pos + 1);
                }
                std::istringstream verstrm1(std::string(RGAPI_MAJOR_VERSION));
                std::istringstream verstrm2(std::string(RGAPI_MINOR_VERSION));
                std::istringstream verstrm3(std::string(RGAPI_FIX_VERSION));
                verstrm1 >> localversion[0];
                verstrm2 >> localversion[1];
                verstrm3 >> localversion[2];
                
            	int localvernum = (100 * localversion[0]) + (10 * localversion[1]) + localversion[2];
        		int latestvernum = (100 * version[0]) + (10 * version[1]) + version[2];

               	if(localvernum > latestvernum) {
                    if(dologging) {
                        std::cout << "you are using a beta api version, please report any bug you find.\n";
                        std::cout << "your version is: " << fullapiver << "\n";
                        std::cout << "latest version is: " << response_string << "\n";
                    }
                    return 1;
            	}
				else {
					if(dologging) {
						std::cout << "api version is outdated. if you are the developer please update the api.\n";
						std::cout << "your version is: " << fullapiver << "\n";
						std::cout << "latest version is: " << response_string << "\n";
					}
					return 0;
            	}
                
            }

        }
        else {
            std::cout << response_string << "\n";
            if(dologging) {
                std::cout << "api version is depricated. if you are the developer please update the api.\n";
                std::cout << "your version is: " << fullapiver << "\n";
                std::cout << "latest version is: " << response_string << "\n";
            }
        }
        
       
    }

    return -1;
}
int RGAPI_GetServerVersion(bool dologging) {

    curl_easy_setopt(curl, CURLOPT_URL, (url + "&r=getlatestapiver").c_str());

    response_string = "";
    header_string = "";
       
    CURLcode res = curl_easy_perform(curl);
    
    if(res != CURLE_OK) {
        std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }
    else {
        serverapiver = response_string;
        if(isdigit(response_string[0])) {
            RGAPI_LatestServerVer = response_string;
            if(fullapiver == response_string) {
                if(dologging) {
                    std::cout << "api is using the latest server api version (" << response_string << ")\n";
                }
                return 1;
            }
            else {
                int version[3];
                int localversion[3];
                std::string verstr = response_string;
                for(int i = 0; i < 3; i++) {
                    size_t pos = verstr.find(".");
                    std::string vernum = verstr.substr(0, pos);
                    std::istringstream verstrm(vernum);
                    verstrm >> version[i];
                    
                    verstr.erase(0, pos + 1);
                }
                std::istringstream verstrm1(std::string(RGAPI_SERVER_MAJOR_VERSION));
                std::istringstream verstrm2(std::string(RGAPI_SERVER_MINOR_VERSION));
                std::istringstream verstrm3(std::string(RGAPI_SERVER_FIX_VERSION));
                verstrm1 >> localversion[0];
                verstrm2 >> localversion[1];
                verstrm3 >> localversion[2];
				int localvernum = (100 * localversion[0]) + (10 * localversion[1]) + localversion[2];
        		int latestvernum = (100 * version[0]) + (10 * version[1]) + version[2];

               	if(localvernum > latestvernum) {
                    if(dologging) {
                        std::cout << "the api is relying on a beta api version, things may not work like expected\n";
                        std::cout << "your version is: " << fullserverver << "\n";
                        std::cout << "latest version is: " << response_string << "\n";
                    }
					return 1;
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
        else {
            std::cout << response_string << "\n";
            if(dologging) {
                std::cout << "your api library is using an depricated server api version\n";
                std::cout << "your version is: " << fullserverver << "\n";
                std::cout << "latest version on the server is: " << response_string << "\n";
            }
            
        }    
    }
    return -1;
}
int RGAPI_NameToID(const char* name) {
    return RGAPI_NameToID(std::string(name));
}
int RGAPI_NameToID(std::string name) {
    
   
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
std::string RGAPI_IDToName(int id) {
    
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
std::string RGAPI_GetName(int argc, char* argv[]) {
    for(int i = 0; i < argc - 1; i++) {
        if(std::string(argv[i]) == std::string("--name")) {
            if(std::string(argv[i + 1]) != std::string("--session")) {
                return argv[i + 1];
            }
        }
    }
    return "";
}
std::string RGAPI_GetSession(int argc, char* argv[]) {
    for(int i = 0; i < argc - 1; i++) {
        if(std::string(argv[i]) == std::string("--session")) {
            if(std::string(argv[i + 1]) != std::string("--name")) {
                return argv[i + 1];
            }
        }
    }
    return "";
}
int RGAPI_GetWRCount(int id) {
    
    
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
std::string RGAPI_NewSession(int id, std::string session) {
    
   
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
bool RGAPI_CheckSession(int id, std::string session) {
    
    
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