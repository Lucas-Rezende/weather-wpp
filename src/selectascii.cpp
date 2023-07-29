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

/*
0	Clear sky OK
1, 2, 3	Mainly clear, partly cloudy, and overcast OK
45, 48	Fog and depositing rime fog OK
51, 53, 55	Drizzle: Light, moderate, and dense intensity OK
56, 57	Freezing Drizzle: Light and dense intensity OK
61, 63, 65	Rain: Slight, moderate and heavy intensity OK
66, 67	Freezing Rain: Light and heavy intensity OK
71, 73, 75	Snow fall: Slight, moderate, and heavy intensity OK
77	Snow grains OK
80, 81, 82	Rain showers: Slight, moderate, and violent OK
85, 86	Snow showers slight and heavy
95 *	Thunderstorm: Slight or moderate 
96, 99 *	Thunderstorm with slight and heavy hail
*/

// 0, 1
ftxui::Element mainlyclear() {
    return ftxui::vbox({
        ftxui::text("      \\   /     ") | color(Color::RGB(255, 191, 0)),
        ftxui::text("       .-.      ") | color(Color::RGB(255, 191, 0)),
        ftxui::text("    ― (   ) ―   ") | color(Color::RGB(255, 191, 0)),
        ftxui::text("       `-’      ") | color(Color::RGB(255, 191, 0)),
        ftxui::text("      /   \\     ") | color(Color::RGB(255, 191, 0)),
    });
}

// 2
ftxui::Element partlycloudy () {
    return vbox({
        text(L"   \\  /      ") | color(Color::RGB(255, 191, 0)),
        hbox({
            text(L" _ /\"\"") | color(Color::RGB(255, 191, 0)),
            text(L".-.    ") | color(Color::RGB(250, 250, 250)),
        }),
        hbox({
            text(L"   \\_") | color(Color::RGB(255, 191, 0)),
            text(L"(   ).  ") | color(Color::RGB(250, 250, 250)),
        }),
        hbox({
            text(L"   /") | color(Color::RGB(255, 191, 0)),
            text(L"(___(__)      ") | color(Color::RGB(250, 250, 250)),
        }),
    });
}

// 3
ftxui::Element overcast () {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
    });
}

//
ftxui::Element fog () {
    return ftxui::vbox({
        ftxui::text("             ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" _ - _ - _ - ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  _ - _ - _  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" _ - _ - _ - ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("             ") | color(Color::RGB(250, 250, 250)),
    });
}

// 51, 61, 80
ftxui::Element weakraindrizzle() {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("   ‚ ‚ ‚ ‚   ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("    ’ ’ ’ ’  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 53, 63, 81
ftxui::Element midraindrizzle() {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("   ‚‘‚ ‚‘‚   ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("    ’  ‚’ ’  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 55, 65, 71, 82
ftxui::Element strongraindrizzle() {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("   ‚‘‚‘‚‘‚‘  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   ‚’‚’‚’‚’  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 56, 661 73
ftxui::Element weakfreezing () {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  *     *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   *   *  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 67, 75, 85
ftxui::Element midfreezing () {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  *  *   *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   * *  *  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 57, 86
ftxui::Element strongfreezing () {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  * * * * *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   * * * * *  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 77
ftxui::Element snowgrains () {
    return ftxui::vbox({
        ftxui::text("  *  *   *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   * *  *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("  *  *   *  ") | color(Color::RGB(0, 0, 139)),
        ftxui::text("   * *  *  ") | color(Color::RGB(0, 0, 139)),
    });
}

// 95, 96, 99
ftxui::Element thunderstorm () {
    return ftxui::vbox({
        ftxui::text("     .--.    ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("  .-(    ).  ") | color(Color::RGB(250, 250, 250)),
        ftxui::text(" (___.__)__) ") | color(Color::RGB(250, 250, 250)),
        ftxui::text("    ⚡⚡") | color(Color::RGB(0, 0, 139)),
        ftxui::text("  ⚡       ") | color(Color::RGB(0, 0, 139)),
    });
}

ftxui::Element getWeatherSymbol(int weatherCode) {
    if (weatherCode == 0 || weatherCode == 1) {
        return mainlyclear();
    } else if (weatherCode == 2) {
        return partlycloudy();
    } else if (weatherCode == 3) {
        return overcast();
    } else if (weatherCode == 45 || weatherCode == 48) {
        return fog();
    } else if (weatherCode == 51 || weatherCode == 61 || weatherCode == 80) {
        return weakraindrizzle();
    } else if (weatherCode == 53 || weatherCode == 63 || weatherCode == 81) {
        return midraindrizzle();
    } else if (weatherCode == 55 || weatherCode == 65 || weatherCode == 71 || weatherCode == 82) {
        return strongraindrizzle();
    } else if (weatherCode == 56 || weatherCode == 66 || weatherCode == 73) {
        return weakfreezing();
    } else if (weatherCode == 67 || weatherCode == 75 || weatherCode == 85) {
        return midfreezing();
    } else if (weatherCode == 57 || weatherCode == 86) {
        return strongfreezing();
    } else if (weatherCode == 77) {
        return snowgrains();
    } else if (weatherCode == 95 || weatherCode == 96 || weatherCode == 99) {
        return thunderstorm();
    } else {
        return ftxui::text("Weather code error");
    }
}