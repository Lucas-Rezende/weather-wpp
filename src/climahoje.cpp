#include "../include/climahoje.hpp"

Climahoje::Climahoje(float temperature,
                     float relative_humidity,
                     float apparent_temperature,
                     float precipitation_probability,
                     float maximum_temperature,
                     float minimum_temperatude,
                     std::string sunrise,
                     std::string sunset,
                     std::string date) : Clima(temperature, relative_humidity, apparent_temperature, precipitation_probability, maximum_temperature, minimum_temperatude, sunrise, sunset, date) {}