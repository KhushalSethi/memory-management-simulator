@echo off
echo Building Memory Management Simulator...

REM Create build directory
if not exist build mkdir build
cd build

REM Run CMake
cmake ..

REM Build the project
cmake --build .

echo.
echo Build complete! 
echo To run the simulator, use: .\build\Debug\memsim.exe
pause
