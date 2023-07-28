#include <stddef.h>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <algorithm>
#include <codecvt>
#include <cstdint>
#include <locale>
#include <sstream>
#include <iomanip>

#include "include/getcoordinates.hpp"
#include "include/gettime.hpp"
#include "include/hourlydatafilter.hpp"
#include "include/weatherdatafetcher.hpp"

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/flexbox_config.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/screen/color_info.hpp"
#include "ftxui/screen/terminal.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/util/ref.hpp"

using namespace ftxui;
using namespace std::chrono_literals;

ftxui::Element imprimeascii() {
    return ftxui::vbox({
        ftxui::text("      \\   /     "),
        ftxui::text("       .-.      "),
        ftxui::text("    ― (   ) ―   "),
        ftxui::text("       `-’      "),
        ftxui::text("      /   \\     "),
    });
}

class Graph
{
public:
    Graph(getCoordinates &getcoords, getTime &gettime, hourlyDataFilter &hourlyfilter)
        : getcoordinates(getcoords), gettime(gettime), hourlydatafilter(hourlyfilter)
    {
    }

    std::vector<int> operator()(int width, int height) const
    {
        std::vector<int> output(23);
        float max_value = 0.0f;

        // Encontra o valor máximo do gráfico em todas as colunas.
        for (unsigned int i = 0; i < 23; ++i)
        {
            unsigned int hour = i;
            std::string correcthour;
            if (hour < 10)
            {
                correcthour = "0" + std::to_string(hour) + ":00";
            }
            else
            {
                correcthour = std::to_string(hour) + ":00";
            }
            std::string date = gettime.Date();
            std::string completedatewoutmin = date + "T" + correcthour;
            std::string now = hourlydatafilter.getTemperatureDataAtTime(completedatewoutmin);
            float now_value = std::stof(now);
            max_value = std::max(max_value, now_value);

            float v = now_value * (height / 40.0f);
            output[i] = static_cast<int>(v);
        }
        return output;
    }

private:
    getCoordinates &getcoordinates;
    getTime &gettime;
    hourlyDataFilter &hourlydatafilter;
    int shift;
};

Element create_weather_element(const Graph &my_graph)
{
    auto document = hbox({
        vbox({
            graph(my_graph),
        }) | flex,
    });

    document |= border;

    const int min_width = 23;
    document |= size(HEIGHT, GREATER_THAN, min_width);

    return document;
}

int main()
{
    auto screen = ScreenInteractive::Fullscreen();
    getCoordinates getcoordinates;
    getTime gettime;
    hourlyDataFilter hourlydatafilter;
    weatherdatafetcher weatherdatafetcher;
    Graph my_graph(getcoordinates, gettime, hourlydatafilter);

    int shift = 0;

    std::wstring emoji = L"⛅";

    std::string local;
    bool input_confirmed = false;

    Component yourlocal = Input(&local, "Your local");

    Component button = Button("Confirm", [&]
                              {  input_confirmed = true; getcoordinates.Coordinates(local);
                                                float latitude = getcoordinates.getLatitude();
                                                float longitude = getcoordinates.getLongitude();

                                                std::string date = gettime.Date();
                                                std::string hour = gettime.CompleteHour();

                                                std::string completedate = date + "T" + hour;

                                                weatherdatafetcher.fetchData(latitude, longitude, 2, date, date); });

    auto component = Container::Vertical({
        yourlocal,
        button,
    });

    auto weather_renderer = Renderer(component, [&]
                                     { 
        // Verifica o estado do aplicativo para alternar entre os layouts.
        if (!input_confirmed)
        {
            return vbox({
                text("WELCOME TO THE WEATHER-WPP") | center | color(Color::White) | bold,
                text(emoji) | hcenter,
                separator(),
                hbox(text(" Insert your local : "), yourlocal->Render()),
                hbox(center, button->Render()) | center,
            }) | center | bgcolor(Color::RGB(109, 76, 182));
        }
        else
        {
            std::string date = gettime.Date();
            std::string hour = gettime.CompleteHour();
            unsigned int justhour = gettime.Hour();
            std::string correcthour;
            if (justhour < 10)
            {
                std::string justhour_str = std::to_string(justhour);
                correcthour = "0" + justhour_str + ":00";
            } else
            {
                std::string justhour_str = std::to_string(justhour);
                correcthour = justhour_str + ":00";
            }

            std::string completedatewmin = date + "T" + hour;
            std::string completedatewoutmin = date + "T" + correcthour;

            float maxTemperature = hourlydatafilter.getMaxTemperature();
            float minTemperature = hourlydatafilter.getMinTemperature();

            std::ostringstream ssMax, ssMin;
            ssMax << std::fixed << std::setprecision(1) << maxTemperature;
            ssMin << std::fixed << std::setprecision(1) << minTemperature;

            std::string max = ssMax.str();
            std::string min = ssMin.str();
            std::string maxmin = min + " - " + max + " °C";
            std::string now = hourlydatafilter.getTemperatureDataAtTime(completedatewoutmin);

            Element weather_element = create_weather_element(my_graph);
            return vbox({
                hbox({
                    /*vbox({
                        text("Frequency [Mhz]") | hcenter,
                        hbox({
                            vbox({
                                text("2400 "),
                                filler(),
                                text("1200 "),
                                filler(),
                                text("0 "),
                            }),
                             graph(std::ref(my_graph)) | size(WIDTH, GREATER_THAN, 80) | size(HEIGHT, EQUAL, 20),
                        }) | flex,
                    }),*/
                    vbox({
                        imprimeascii() | ftxui::center | ftxui::flex,
                    }) | center | flex,
                    separator(),
                    vbox({
                        text(maxmin),
                        text(now),
                    }) | center | flex,
                }),
            }) | center | bgcolor(Color::RGB(109, 76, 182));
        } });

    // CONFIGURATION

    int tab_index = 0;
    std::vector<std::string> tab_entries = {
        "Weather",
    };
    auto tab_selection =
        Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
    auto tab_content = Container::Tab(
        {
            weather_renderer,
        },
        &tab_index);

    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
    });

    auto main_renderer = Renderer(main_container, [&]
                                  { return vbox({
                                        text("Weather WPP") | bold | hcenter,
                                        tab_selection->Render(),
                                        tab_content->Render() | flex,
                                    }); });

    std::atomic<bool> refresh_ui_continue = true;
    std::thread refresh_ui([&]
                           {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      screen.Post([&] { shift++; });
      screen.Post(Event::Custom);
    } });

    screen.Loop(main_renderer);
    refresh_ui_continue = false;
    refresh_ui.join();

    if (input_confirmed)
    {
        getcoordinates.Coordinates(local);

        float latitude = getcoordinates.getLatitude();
        float longitude = getcoordinates.getLongitude();

        std::string date = gettime.Date();

        weatherdatafetcher.fetchData(latitude, longitude, 2, date, date);
    }
    else
    {
        std::wcout << L"Input error" << std::endl;
    }

    return 0;
}