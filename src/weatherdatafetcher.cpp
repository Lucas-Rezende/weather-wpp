#include "../include/weatherdatafetcher.hpp"

#include <cstdlib>
#include <curl/curl.h>
#include <fstream>
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

void weatherdatafetcher::fetchData(float latitude, float longitude, unsigned int diasdeprevisao, std::string datainicial, std::string datafinal) {
    std::string url;
    if (datainicial == datafinal)
    {
        url = "https://api.open-meteo.com/v1/forecast?latitude=" + std::to_string(latitude) + "&longitude=" + std::to_string(longitude) + "&hourly=temperature_2m,relativehumidity_2m,precipitation_probability,weathercode&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset&current_weather=true&timezone=America%2FSao_Paulo&start_date=" + datainicial + "&end_date=" + datafinal;
    }
    
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

    std::string command = "python3 processdata.py";
    int exitCode = system(command.c_str());
    if (exitCode != 0) {
        std::cout << "Erro ao executar o script Python." << std::endl;
        return;
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
    std::ifstream inputFile(filename);
    std::string data;

    if (inputFile.is_open()) {
        std::getline(inputFile, data);
        inputFile.close();
    } else {
        std::cerr << "Error: Failed to open the file." << std::endl;
    }

    return data;
}