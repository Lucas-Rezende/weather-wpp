#ifndef WEATHER_DATA_FETCHER
#define WEATHER_DATA_FETCHER

#include <string>

class weatherdatafetcher
{
private:
public:
    void fetchData(float latitude,
    float longitude,
    unsigned int diasdeprevisao,
    std::string datainicial,
    std::string datafinal);

    void saveDataToFile(const std::string& data);
    std::string loadDataFromFile(const std::string& filename);
    /* TODO Adicionar os métodos pra cada variável */
};

#endif