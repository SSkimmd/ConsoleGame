@echo off

if exist .\build\Debug\ (
	goto build
) else (
	echo Build Folder Doesn't Exist For Some Reason
	mkdir ".\build\Debug\"
	goto build
)


:build
echo Building Game
g++ -g3 -O0 *.cpp -o .\build\Debug\game.exe 
if errorlevel 0 goto build_success 
goto build_fail


:build_fail
echo Failed To Build .exe
set /p in="Press Enter To Close The Window"

:build_success
echo Successfully Built game.exe
echo[
echo Game Location: /build/debug/game.exe
echo[
echo Copying Level Folder
mkdir ".\build\Debug\levels"
copy ".\levels\*.*"  ".\build\Debug\levels\"
echo[
set /p in="Press Enter To Close The Window"