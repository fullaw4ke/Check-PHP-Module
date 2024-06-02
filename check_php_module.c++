#include <iostream>
#include <string>
#include <curl/curl.h>

int main() {
    CURL *curl;
    CURLcode res;
    long http_code = 0;
    std::string url = "http://10.10.11.244/.php";
    
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        // curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L); // No manejar errores automáticamente
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "Error in curl_easy_perform(): " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Curl initialization failed!" << std::endl;
        return 1;
    }

    if(http_code == 403) {
        std::cout << "PHP module is present" << std::endl;
    } else {
        std::cout << "PHP module is not present" << std::endl;
    }
    return 0;
}
