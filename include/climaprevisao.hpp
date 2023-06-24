#ifndef CLIMA_PREVISAO_HPP
#define CLIMA_PREVISAO_HPP

#include "clima.hpp"

class Climaprevisao : public Clima
{
private:
public:
    Climaprevisao(float temperature,
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