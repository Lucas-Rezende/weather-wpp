#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "include/weatherdatafetcher.hpp"
#include "include/getcoordinates.hpp"
#include "include/gettime.hpp"
#include "include/hourlydatafilter.hpp"

int main()
{
    getCoordinates getcoord;
    weatherdatafetcher weatherFetcher;
    getTime gettime;

    getcoord.Coordinates();

    float lat = getcoord.getLatitude();
    float lon = getcoord.getLongitude();

    std::string todaydate = gettime.Date();

    weatherFetcher.fetchData(lat, lon, 0, todaydate, todaydate);

    getTime gt;
    std::string date = gt.Date();
    std::string hour = gt.CompleteHour();

    hourlyDataFilter hdf;
    float max = hdf.getMaxTemperature();
    float min = hdf.getMinTemperature();
    std::string sunset = hdf.getSunsetTime();
    std::string sunrise = hdf.getSunriseTime();

    std::string temptest = date + "T" + std::to_string(gt.Hour()) + ":00";

    std::cout << "Temperatura nesse momento: " << hdf.getTemperatureDataAtTime(temptest) << std::endl;
    std::cout << "Umidade nesse momento: " << hdf.getRelativeHumidityDataAtTime(temptest) << std::endl;
    std::cout << "Chance de precipitação nesse momento: " << hdf.getPrecipitationProbailityDataAtTime(temptest) << std::endl;
    std::cout << "Weathercode nesse momento: " << hdf.getWeatherCodeDataAtTime(temptest) << std::endl;

    return 0;
}