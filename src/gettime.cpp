#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "../include/gettime.hpp"

getTime::getTime() {}

std::string getTime::Date() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d");
    std::string processdate = oss.str();

    return processdate;
}

std::string getTime::CompleteHour() {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&nowTime);

    // Obtenha a hora e minuto formatados
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":" << std::setfill('0') << std::setw(2) << localTime->tm_min;

    return oss.str();
}

unsigned int getTime::Hour() {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&nowTime);

    unsigned int hour = localTime->tm_hour;

    return hour;
}