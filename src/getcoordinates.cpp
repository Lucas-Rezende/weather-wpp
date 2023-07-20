#include "../include/getcoordinates.hpp"
#include <iostream>
#include <cstdlib>

getCoordinates::getCoordinates() {}

void getCoordinates::Coordinates(std::string local) const {
    std::string command = "python3 setcoordinates.py \"" + local + "\"";

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cout << "Erro ao executar o script Python." << std::endl;
        return;
    }

    char buffer[128];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        output += buffer;
    }

    pclose(pipe);

    double la, lo;
    sscanf(output.c_str(), "%lf %lf", &la, &lo);

    // Atribuir os valores de latitude e longitude às variáveis de membro
    this->latitude = static_cast<float>(la);
    this->longitude = static_cast<float>(lo);
}

float getCoordinates::getLongitude() {
    return longitude;
}

float getCoordinates::getLatitude() {
    return latitude;
}