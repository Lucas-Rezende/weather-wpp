#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "include/weatherdatafetcher.hpp"
#include "include/getcoordinates.hpp"
#include "include/gettime.hpp"

int main()
{
    getCoordinates getcoord;

    getcoord.Coordinates();

    float lat = getcoord.getLatitude();
    float lon = getcoord.getLongitude();

    std::cout << "Latitude: " << lat << std::endl;
    std::cout << "Longitude: " << lon << std::endl;

    weatherdatafetcher weatherFetcher;
    getTime gettime;

    std::string todaydate = gettime.Date();

    weatherFetcher.fetchData(lat, lon, 0, todaydate, todaydate);

    std::ifstream file("data/datapy.txt");
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string line;
    std::string currentDate;
    while (std::getline(file, line))
    {
        if (line.substr(0, 4) == "Data")
        {
            if (!currentDate.empty())
                std::cout << std::endl; // Separar os dados de cada dia

            currentDate = line.substr(line.find(":") + 2);
            std::cout << line << std::endl;
        }
        else if (line.substr(0, 3) == "Sunrise")
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
