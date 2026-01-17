@echo off

set SRC=main.cpp
set OUT=bin\main.exe
set SDL_PATH=libs\SDL2

g++ src\main.cpp -I third_party\SDL2\include -L third_party\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -mconsole -o %OUT%



if %errorlevel% neq 0 (
    echo.
    echo Erro na compilacao!
    echo %SRC%
    echo %SDL_PATH%
    pause
    exit /b %errorlevel%
)

%OUT%

cls

