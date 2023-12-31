# weather-wpp

:partly_sunny: Terminal weather application.

![image](https://github.com/Lucas-Rezende/weather-wpp/assets/66080424/c5a68b8a-320a-43de-9b61-90ec38e44305)

<p align="center">
  <a href="#"><img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"></img></a>
  <a href="#"><img src="https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white"></img></a>
  <br>
  <a href="#"><img src="https://img.shields.io/badge/Tested%20on%20Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"></img></a>
  <a href="#"><img src="https://img.shields.io/badge/Tested%20on%20Linux-87CEEB?style=for-the-badge&logo=linux&logoColor=black"></img></a>
  <a href="#"><img src="https://img.shields.io/badge/Developed%20in%20Arch-1793D1?style=for-the-badge&logo=arch-linux&logoColor=white"></img></a>
</p>

## Introduction
Weather-wpp is a terminal GUI weather information program based on the [FTXUI library](https://github.com/ArthurSonzogni/FTXUI) and use data from [Open-Meteo API](https://open-meteo.com/).

## Requirements
To fully use this code, your terminal must support UTF-8 and be configured with a font that includes emoji glyphs, in addition to being in a recent version. In addition, it is necessary that you have pre-installed GNU Make and Make, in order to carry out all the commands.

## Devices
When using the program, you will have access to weather information in your location using the [Open-Meteo API](https://open-meteo.com/) as a reference.

The program has hourly (given every hour) and daily (fixed for the whole day) information. You will have access to information such as:
<ul>
  <li>Temperature based on your operating system time</li>
  <li>Maximum and minimum temperature</li>
  <li>Precipitation Probability with more than 0.1 mm of the preceding hour</li>
  <li>Humidity</li>
  <li>Weather Code</li>
</ul>

## Usage
Initially, it is necessary that you clone this project on your machine, with the installation location being something that can be quickly accessed via a terminal. To do so, issue the following command in your terminal with the chosen installation folder:

```shell
git clone https://github.com/Lucas-Rezende/weather-wpp
```

After that, create a folder named "build" at the root of the project, then, in the terminal, still at the root of the folder, run the command:

```shell
cmake -B build
```

Completing the previous steps, enter the build folder via terminal and issue the command:

```shell
make
```

After the complete compilation of the project, you can return to the root of the project and finally run the program by typing:

```shell
./build/app
```

That way, you'll have access to the program's interface, where you can enter your location and access its weather information.
