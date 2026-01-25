@echo off
echo ===============================
echo  Compilando Rasterizador 3D
echo ===============================

REM ---- CONFIGURACAO ----
set COMPILER=g++
set OUTPUT=bin\app.exe

REM Caminho da SDL2 (ajuste se necessario)
set SDL2_PATH=C:\libs\SDL2\x86_64-w64-mingw32

REM ---- FLAGS ----
set INCLUDE_FLAGS=-I include -I third_party\SDL2\include
set LIB_FLAGS=-L third_party\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -mconsole

set CFLAGS=-std=c++17 -Wall

REM ---- LIMPA BUILD ANTIGO ----
if exist %OUTPUT% del %OUTPUT%

REM ---- COMPILACAO ----
%COMPILER% ^
src\main.cpp ^
src\math\vector.cpp ^
src\math\matrix.cpp ^
src\render\render.cpp ^
src\render\VertexRender.cpp ^
src\scene\cube.cpp ^
%INCLUDE_FLAGS% ^
%LIB_FLAGS% ^
%CFLAGS% ^
-o %OUTPUT%

REM ---- RESULTADO ----
if %ERRORLEVEL% neq 0 (
    echo.
    echo ❌ ERRO NA COMPILACAO
    pause
    exit /b 1
)

echo.
echo ✅ Build concluido com sucesso!
echo Executavel: %OUTPUT%
%OUTPUT%
pause


REM g++ src\main.cpp -I third_party\SDL2\include -L third_party\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -mconsole -o %OUT%





