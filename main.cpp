#include "include/weatherdatafetcher.hpp"
#include "include/clima.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{
    // Criar uma instância do WeatherDataFetcher
    weatherdatafetcher dataFetcher;

    // Chamar o método fetchData() para buscar os dados
    float latitude = 52.52;
    float longitude = 13.41;
    unsigned int diasdeprevisao = 3;
    std::string datainicial = "2023-06-23";
    std::string datafinal = "2023-06-26";
    dataFetcher.fetchData(latitude, longitude, diasdeprevisao, datainicial, datafinal);

    // Carregar os dados do arquivo
    const std::string dataPath = "data/";

    std::string filePath = dataPath + "data.txt";
    std::string loadedData = dataFetcher.loadDataFromFile(filePath);

    // Imprimir os dados carregados
    std::cout << "Dados carregados do arquivo:" << std::endl;
    std::cout << loadedData << std::endl;

    return 0;
}
