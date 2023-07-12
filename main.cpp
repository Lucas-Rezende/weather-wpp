#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "include/weatherdatafetcher.hpp"

std::string command = "python processdata.py";

int main() {
    weatherdatafetcher weatherFetcher;

    weatherFetcher.fetchData(-19.9208, -43.9378, 2, "2023-07-12", "2023-07-14");

    std::ifstream file("data/datapy.txt");
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 4) == "Data") {
            std::cout << line << std::endl;
        } else if (line.substr(0, 3) == "Max") {
            std::cout << "Temperatura Máxima: " << line.substr(line.find(":") + 2) << std::endl;
        } else if (line.substr(0, 3) == "Min") {
            std::cout << "Temperatura Mínima: " << line.substr(line.find(":") + 2) << std::endl;
        } else if (line.substr(0, 7) == "Sunrise") {
            std::cout << "Nascer do Sol: " << line.substr(line.find(":") + 2) << std::endl;
        } else if (line.substr(0, 6) == "Sunset") {
            std::cout << "Pôr do Sol: " << line.substr(line.find(":") + 2) << std::endl;
        } else if (line.substr(0, 4) == "2023") {
            std::cout << line << std::endl;
        }
    }

    file.close();
    int result = std::system(command.c_str());

    // Verificar o resultado da execução
    if (result == 0) {
        std::cout << "Arquivo .txt processado com sucesso!" << std::endl;
    } else {
        std::cout << "Ocorreu um erro ao processar o arquivo .txt." << std::endl;
    }

     std::cout << "Pesquisar localizacao..." << std::endl;

    // Comando para chamar o interpretador Python e executar o script
    std::string command = "python setcoordinates.py";
    
    // Criar pipes para a comunicação
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cout << "Erro ao executar o script Python." << std::endl;
        return -1;
    }

    // Ler a saída do script Python
    char buffer[128];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        output += buffer;
    }

    // Fechar o pipe
    pclose(pipe);

    // Extrair os valores de latitude e longitude da saída
    double latitude, longitude;
    sscanf(output.c_str(), "%lf %lf", &latitude, &longitude);

    // Exibir os valores no C++
    std::cout << "Latitude: " << latitude << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;

    return 0;
}
