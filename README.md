# WHEELS ON TIME

Данный проект представляет собой приложение для аренды автомобиля, написанное на C++. В проекте
помимо STL библиотек используются библиотеки QT 6-ой версии для интерфейса и SQLite3 для работы
с базами данных. Так же для сборки проекта используется CMake.
## Установка библиотек
### Windows
Скачайте msys2.

Далее откройте консоль MSYS2:
1. Установите mingw64
```shell
pacman -S mingw-w64-x86_64-gcc
```
2. Установите SQLite3
``` shell
pacman -S mingw-w64-x86_64-sqlite3
```
3. Установите QT
``` shell
pacman -S mingw-w64-x86_64-qt6
```
### MacOS
Установите Homebrew.
``` shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Затем:
1. Установите SQLite3
``` shell
brew install sqlite
```
2. Установите QT
``` shell
brew install qt
```