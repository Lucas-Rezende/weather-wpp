#ifndef CLIMA_HPP
#define CLIMA_HPP

#include <iostream>
#include <string>

class Clima
{
private:
    float _temperature;
    float _relative_humidity;
    float _apparent_temperature;
    float _precipitation_probability;
    float _maximum_temperature;
    float _minimum_temperature;
    std::string _sunrise;
    std::string _sunset;
    std::string _date;

public:
    Clima(float temperature,
          float relative_humidity,
          float apparent_temperature,
          float precipitation_probability,
          float maximum_temperature,
          float minimum_temperature,
          std::string sunrise,
          std::string sunset,
          std::string date
    );

    /*TODO Adicionar GETS*/
};

#endif