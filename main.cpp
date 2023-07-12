#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "include/weatherdatafetcher.hpp"
#include "include/getcoordinates.hpp"

int main()
{
    getCoordinates getcoord;

    getcoord.Coordinates();

    float lat = getcoord.getLatitude();
    float lon = getcoord.getLongitude();

    std::cout << "Latitude: " << lat << std::endl;
    std::cout << "Longitude: " << lon << std::endl;

    weatherdatafetcher weatherFetcher;

    weatherFetcher.fetchData(lat, lon, 2, "2023-07-12", "2023-07-14");

    std::ifstream file("data/datapy.txt");
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.substr(0, 4) == "Data")
        {
            std::cout << line << std::endl;
        }
        else if (line.substr(0, 3) == "Max")
        {
            std::cout << "Temperatura Máxima: " << line.substr(line.find(":") + 2) << std::endl;
        }
        else if (line.substr(0, 3) == "Min")
        {
            std::cout << "Temperatura Mínima: " << line.substr(line.find(":") + 2) << std::endl;
        }
        else if (line.substr(0, 7) == "Sunrise")
        {
            std::cout << "Nascer do Sol: " << line.substr(line.find(":") + 2) << std::endl;
        }
        else if (line.substr(0, 6) == "Sunset")
        {
            std::cout << "Pôr do Sol: " << line.substr(line.find(":") + 2) << std::endl;
        }
        else if (line.substr(0, 4) == "2023")
        {
            std::cout << line << std::endl;
        }
    }

    file.close();

    return 0;
}
