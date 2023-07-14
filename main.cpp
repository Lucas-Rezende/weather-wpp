#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "include/weatherdatafetcher.hpp"
#include "include/getcoordinates.hpp"
#include "include/gettime.hpp"
#include "include/hourlydatafilter.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

int main()
{
    getCoordinates getcoord;
    weatherdatafetcher weatherFetcher;
    getTime gettime;

    getcoord.Coordinates();

    float lat = getcoord.getLatitude();
    float lon = getcoord.getLongitude();

    std::string todaydate = gettime.Date();

    weatherFetcher.fetchData(lat, lon, 0, todaydate, todaydate);

    getTime gt;
    std::string date = gt.Date();
    std::string hour = gt.CompleteHour();

    hourlyDataFilter hdf;
    float max = hdf.getMaxTemperature();
    float min = hdf.getMinTemperature();
    std::string sunset = hdf.getSunsetTime();
    std::string sunrise = hdf.getSunriseTime();

    std::string temptest;
    if (gt.Hour() >= 10)
    {
        temptest = date + "T" + std::to_string(gt.Hour()) + ":00";
    }
    else
    {
        temptest = date + "T0" + std::to_string(gt.Hour()) + ":00";
    }

    std::string tn = hdf.getTemperatureDataAtTime("2023-07-14T09:00");
    std::cout << "Umidade nesse momento: " << hdf.getRelativeHumidityDataAtTime(temptest) << std::endl;
    std::cout << "Chance de precipitação nesse momento: " << hdf.getPrecipitationProbabilityDataAtTime(temptest) << std::endl;
    std::cout << "Weathercode nesse momento: " << hdf.getWeatherCodeDataAtTime(temptest) << std::endl;

    using namespace ftxui;
    // Define some variables to display.
    int x = 42;
    std::string y = "Hello";
    double z = 3.14;

    // Convert the variables into elements.
    Element x_element = text(tn + "°C");
    Element y_element = text(temptest);
    Element z_element = text("Weather");

    // Create boxes with borders around the elements.
    Element x_box = border(x_element);
    Element y_box = border(y_element);
    Element z_box = border(z_element);

    // Arrange the boxes horizontally with some space between them.
    Element boxes = hbox({
        x_box | flex,
        separator(),
        y_box | flex,
        separator(),
        z_box | flex,
    });

    // Change the background color of the terminal to cyan.
    Element colored = bgcolor(Color::Magenta, boxes);

    // Render the element into a screen.
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(colored));
    Render(screen, colored);

    // Print the screen to the standard output.
    std::cout << screen.ToString() << std::endl;

    return 0;
}