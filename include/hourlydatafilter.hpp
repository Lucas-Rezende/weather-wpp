#ifndef HOURLY_DATA_FILTER
#define HOURLY_DATA_FILTER

#include <string>

class hourlyDataFilter
{
private:
public:
    hourlyDataFilter();

    float getMaxTemperature();
    float getMinTemperature();
    std::string getSunriseTime();
    std::string getSunsetTime();
    std::string getHourlyDataAtTime(std::string datetime);
    std::string getTemperatureDataAtTime(std::string hourlydata);
    std::string getRelativeHumidityDataAtTime(std::string hourlydata);
    std::string getPrecipitationProbailityDataAtTime(std::string hourlydata);
    std::string getWeatherCodeDataAtTime(std::string hourlydata);
};

#endif