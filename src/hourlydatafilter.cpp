#include "../include/hourlydatafilter.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

hourlyDataFilter::hourlyDataFilter() {}

float hourlyDataFilter::getMaxTemperature()
{
    std::string filename = "data/datapy.txt";
    std::ifstream file(filename);

    // Verificar se o arquivo foi aberto corretamente
    if (!file.is_open())
    {
        std::cout << "Erro ao abrir o arquivo " << filename << std::endl;
        return -1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    for (long unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("Max Temp:") != std::string::npos)
        {
            float maxTemp = stof(lines[i].substr(10));
            return maxTemp;
        }
    }

    return -1;
}

float hourlyDataFilter::getMinTemperature() {
    
    std::string filename = "data/datapy.txt";
    std::ifstream file(filename);

    // Verificar se o arquivo foi aberto corretamente
    if (!file.is_open())
    {
        std::cout << "Erro ao abrir o arquivo " << filename << std::endl;
        return -1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    for (long unsigned int i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("Min Temp:") != std::string::npos)
        {
            float minTemp = stof(lines[i].substr(10));
            return minTemp;
        }
    }

    return -1;
}

std::string hourlyDataFilter::getSunsetTime() {
    std::string filename = "data/datapy.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << filename << std::endl;
        return "";
    }

    std::string line;
    while (getline(file, line)) {
        if (line.find("Sunset:") != std::string::npos) {
            std::string sunset = line.substr(19);
            return sunset;
        }
    }

    return "";
}

std::string hourlyDataFilter::getSunriseTime() {
    std::string filename = "data/datapy.txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << filename << std::endl;
        return "";
    }

    std::string line;
    while (getline(file, line)) {
        if (line.find("Sunrise:") != std::string::npos) {
            std::string sunrise = line.substr(20);
            return sunrise;
        }
    }

    return "";
}

std::string hourlyDataFilter::getHourlyDataAtTime(std::string datetime) {
    std::ifstream file("data/datapy.txt");
    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo" << std::endl;
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(datetime) != std::string::npos) {
            return line;
        }
    }
    return "";
}

std::string hourlyDataFilter::getTemperatureDataAtTime(std::string hourlydata) {
    std::string temp = getHourlyDataAtTime(hourlydata);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = temp.find(delimiter)) != std::string::npos) {
        token = temp.substr(0, pos);
        temp.erase(0, pos + delimiter.length());
        count++;
        if (count == 3) {
            return token;
        }
    }
    return "Erro";
}

std::string hourlyDataFilter::getRelativeHumidityDataAtTime(std::string hourlyData) {
    std::string line = getHourlyDataAtTime(hourlyData);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        count++;
        if (count == 4) {
            return token;
        }
    }
    return "Erro";
}

std::string hourlyDataFilter::getPrecipitationProbabilityDataAtTime(std::string hourlyData) {
    std::string line = getHourlyDataAtTime(hourlyData);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        count++;
        if (count == 5) {
            return token;
        }
    }
    return "Erro";
}

std::string hourlyDataFilter::getWeatherCodeDataAtTime(std::string hourlyData) {
    std::string line = getHourlyDataAtTime(hourlyData);
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int count = 0;
    while ((pos = line.find(delimiter)) != std::string::npos || count < 6) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        count++;
        if (count == 6) {
            return token;
        }
    }
    return "Erro";
}