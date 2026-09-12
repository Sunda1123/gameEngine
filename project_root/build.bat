@echo off
REM ============================================
REM  gameEngine one-click build script
REM  Usage: double-click build.bat or type build.bat
REM  NOTE: keep every comment in this file ENGLISH -- cmd reads .bat as GBK,
REM        so UTF-8 Chinese becomes garbage and gets executed as commands.
REM
REM  Source list below is EXPLICIT and hand-maintained ON PURPOSE:
REM    an auto-scan / glob would silently pull in files you did not mean to
REM    compile (extra main(), experiments, third-party code) --
REM    "uncontrolled" is worse than "slightly annoying".
REM  => When you add a new .cpp, add it to the g++ line below.
REM ============================================

REM Go to script dir (gameEngine root) so relative paths work
cd /d "%~dp0"

echo.
echo === Building gameEngine ... ===
echo.

g++ -std=c++17 ^
 ..\main.cpp ^
 ..\engine\GameApp.cpp ..\engine\Scene.cpp ..\engine\SceneRegistry.cpp ^
 ..\engine\UI\Button.cpp ..\engine\UI\TextRenderer.cpp ..\engine\UI\HealthBar.cpp ^
 ..\game\TowerDefenseApp.cpp ..\game\UI\MainMenuScene.cpp ..\game\UI\GameScene.cpp ^
 ..\game\UI\ResultScene.cpp ..\game\UI\HUD.cpp ^
 ..\game\gameplay\Map\Map.cpp ..\game\gameplay\World\World.cpp ..\game\gameplay\Player\Player.cpp ^
 ..\game\gameplay\Bullet\Bullet.cpp ..\game\gameplay\Command\PlaceTowerCommand.cpp ^
 ..\game\gameplay\Tower\Tower.cpp ..\game\gameplay\Tower\ArrowTower.cpp ^
 ..\game\gameplay\Tower\CannonTower.cpp ..\game\gameplay\Tower\MagicTower.cpp ^
 ..\game\gameplay\Tower\IceTower.cpp ..\game\gameplay\Tower\TarTower.cpp ^
 ..\game\gameplay\Tower\GoldTower.cpp ..\game\gameplay\Tower\TowerFactory.cpp ^
 ..\game\gameplay\Monster\Monster.cpp ..\game\gameplay\Monster\OrdinaryMonster.cpp ^
 ..\game\gameplay\Monster\TankMonster.cpp ..\game\gameplay\Monster\FastMonster.cpp ^
 ..\game\gameplay\Monster\SplitMonster.cpp ..\game\gameplay\Monster\BomMonster.cpp ^
 ..\game\gameplay\Monster\PoisonMonster.cpp ^
 -I "..\..\novelEngine\SDL3-3.4.14\x86_64-w64-mingw32\include" -L "..\..\novelEngine\SDL3-3.4.14\x86_64-w64-mingw32\lib" -lSDL3 -lgdi32 -luser32 -o game.exe

if %errorlevel% == 0 (
    echo.
    echo [OK] Build success! Run: game.exe
) else (
    echo.
    echo [X] Build failed. Check errors above.
)

pause
