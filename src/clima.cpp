#include "../include/clima.hpp"

Clima::Clima(float temperature,
             float relative_humidity,
             float apparent_temperature,
             float precipitation_probability,
             float maximum_temperature,
             float minimum_temperature,
             std::string sunrise,
             std::string sunset,
             std::string date) : _temperature(temperature), _relative_humidity(relative_humidity), _apparent_temperature(apparent_temperature), _precipitation_probability(precipitation_probability), _maximum_temperature(maximum_temperature), _minimum_temperature(minimum_temperature), _sunrise(sunrise), _sunset(sunset), _date(date) {}