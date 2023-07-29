# weather-wpp

:partly_sunny: Terminal weather application.

![image](https://github.com/Lucas-Rezende/weather-wpp/assets/66080424/c5a68b8a-320a-43de-9b61-90ec38e44305)

## Requirements
To fully use this code, your terminal must support UTF-8 and be configured with a font that includes emoji glyphs, in addition to being in a recent version.

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
