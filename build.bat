@echo off
REM ============================================
REM  gameEngine one-click build script
REM  Usage: double-click build.bat or type build.bat
REM ============================================

REM Go to script dir (gameEngine root) so relative paths work
cd /d "%~dp0"

echo.
echo === Building gameEngine ... ===
echo.

g++ -std=c++17 main.cpp UI/gameUI.cpp Map/Map.cpp Tower/Tower.cpp Tower/ArrowTower.cpp Tower/CannonTower.cpp Tower/MagicTower.cpp Tower/IceTower.cpp Tower/TarTower.cpp Monster/Monster.cpp Monster/OrdinaryMonster.cpp Monster/TankMonster.cpp Monster/FastMonster.cpp Monster/SplitMonster.cpp Monster/BomMonster.cpp Monster/PoisonMonster.cpp Player/Player.cpp -I "..\novelEngine\SDL3-3.4.14\x86_64-w64-mingw32\include" -L "..\novelEngine\SDL3-3.4.14\x86_64-w64-mingw32\lib" -lSDL3 -o game.exe

if %errorlevel% == 0 (
    echo.
    echo [OK] Build success! Run: game.exe
) else (
    echo.
    echo [X] Build failed. Check errors above.
)

pause
