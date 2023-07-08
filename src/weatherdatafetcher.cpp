#include "../include/weatherdatafetcher.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void weatherdatafetcher::fetchData(float latitude, float longitude, unsigned int diasdeprevisao, std::string datainicial, std::string datafinal) {
    std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" + std::to_string(latitude) + "&longitude=" + std::to_string(longitude) + "&hourly=temperature_2m,relativehumidity_2m,apparent_temperature,precipitation_probability&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset&forecast_days=" + std::to_string(diasdeprevisao) + "&start_date=" + datainicial + "&end_date=" + datafinal + "&timezone=America%2FSao_Paulo";
    
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (result != CURLE_OK) {
            std::cerr << "Error: Failed to retrieve weather data." << std::endl;
            return;
        }

        saveDataToFile(response);
    }
}

void weatherdatafetcher::saveDataToFile(const std::string& data) {
    std::ofstream outputFile("data/data.txt");

    if (outputFile.is_open()) {
        outputFile << data;
        outputFile.close();
        std::cout << "Data saved to file." << std::endl;
    } else {
        std::cerr << "Error: Failed to open the file." << std::endl;
    }
}

std::string weatherdatafetcher::loadDataFromFile(const std::string& filename) {
    // O que fazer aqui?
}