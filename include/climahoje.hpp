#ifndef CLIMA_HOJE_HPP
#define CLIMA_HOJE_HPP

#include "clima.hpp"

class Climahoje : public Clima
{
private:
public:
        Climahoje(float temperature,
                float relative_humidity,
                float apparent_temperature,
                float precipitation_probability,
                float maximum_temperature,
                float minimum_temperatude,
                std::string sunrise,
                std::string sunset,
                std::string date);
};

#endif