#include <chrono>

#include "../include/gettime.hpp"

getTime::getTime() {}

std::string getTime::Date() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900; 

    std::string processdate = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);

    return processdate;
}

unsigned int getTime::Hour() {
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);

    std::tm* localTime = std::localtime(&nowTime);

    unsigned int hour = localTime->tm_hour;

    return hour;
}