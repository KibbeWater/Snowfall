@echo off
setlocal

REM Set up Visual Studio 2022 environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

REM Define paths
set PROJECT_ROOT=%~dp0
set LUAJIT_ROOT=%PROJECT_ROOT%Thirdparty\luajit
set LUAJIT_BUILD_DIR=%LUAJIT_ROOT%\src
set SOL_ROOT=%PROJECT_ROOT%Thirdparty\sol
set BUILD_DIR=%PROJECT_ROOT%build

REM Create build directory if it doesn't exist
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

REM Build LuaJIT
echo Building LuaJIT...
cd %LUAJIT_ROOT%\src
call msvcbuild.bat static

REM Verify if LuaJIT build was successful
if %errorlevel% neq 0 (
    echo Failed to build LuaJIT
    exit /b %errorlevel%
)

REM Ensure LUAJIT_BUILD_DIR is available in CMAKE_MODULE_PATH
set CMAKE_MODULE_PATH=C:\Users\kibbe\source\repos\CrackGame\CrackGame;%CMAKE_MODULE_PATH%
echo %CMAKE_MODULE_PATH%

set LUA_LIBRARIES=%LUAJIT_BUILD_DIR%\luajit.lib
set LUA_INCLUDE_DIR=%LUAJIT_BUILD_DIR%
echo %LUA_LIBRARIES%
echo %LUA_INCLUDE_DIR%

REM Build sol
echo Building sol...
cd %SOL_ROOT%
if not exist build (
    mkdir build
)
cd build
cmake -DSOL2_BUILD_LUA=OFF -DSOL2_LUA_VERSION=luajit -DLUA_INCLUDE_DIR=%LUA_INCLUDE_DIR% -DLUA_LIBRARIES=%LUA_LIBRARIES% -DCMAKE_MODULE_PATH=%CMAKE_MODULE_PATH% ..
cmake --build .

REM Verify if sol build was successful
if %errorlevel% neq 0 (
    echo Failed to build sol
    exit /b %errorlevel%
)

echo Build completed successfully
endlocal
