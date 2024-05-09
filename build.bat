@echo off

REM Parse command-line arguments
:parse_args
if "%~1" == "-d" (
    set "BUILD_TYPE=Debug"
    shift
    goto :parse_args
) else if "%~1" == "--debug" (
    set "BUILD_TYPE=Debug"
    shift
    goto :parse_args
) else if "%~1" == "-r" (
    set "BUILD_TYPE=Release"
    shift
    goto :parse_args
) else if "%~1" == "--release" (
    set "BUILD_TYPE=Release"
    shift
    goto :parse_args
) else if "%~1" == "" (
    goto :set_default_build_type
) else (
    echo Unknown parameter: %~1
    exit /b 1
)

:set_default_build_type
if "%BUILD_TYPE%" == "" (
    set "BUILD_TYPE=Release"
)

REM Run CMake with the specified build type
cmake -S . -G "MinGW Makefiles" -B build/ -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

REM Build using cmake
cmake --build build/

