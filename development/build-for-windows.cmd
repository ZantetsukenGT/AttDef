@echo off
setlocal

rem Resolve paths relative to this script, so it also works when double-clicked.
set "devDirectory=%~dp0"
set "devDirectory=%devDirectory:~0,-1%"

set "compilerDirectory=%devDirectory%\compiler-v3.10.11\windows"
for %%I in ("%devDirectory%\..\runtime_windows") do set "runtimeDirectory=%%~fI"
set "amxOutputDirectory=%runtimeDirectory%\gamemodes"

cd /d "%compilerDirectory%"

pawncc.exe ^
	"%devDirectory%\gamemodes\attdef.pwn" ^
	"-D%devDirectory%\gamemodes" ^
	"-o%amxOutputDirectory%\attdef.amx" ^
	-d3 ^
	-O1 ^
	-;+ ^
	-(+ ^
	-\+ ^
	-Z+ ^
	"-i%devDirectory%\legacy" ^
	"-i%devDirectory%\modules" ^
	"-i%devDirectory%" ^
	"-i%devDirectory%\dependencies\omp-stdlib" ^
	"-i%devDirectory%\dependencies\samp-stdlib" ^
	"-i%devDirectory%\dependencies\pawn-stdlib" ^
	"-i%devDirectory%\dependencies\Pawn.RakNet\src" ^
	"-i%devDirectory%\dependencies\YSI-Includes" ^
	"-i%devDirectory%\dependencies\md-sort" ^
	"-i%devDirectory%\dependencies\code-parse.inc" ^
	"-i%devDirectory%\dependencies\indirection" ^
	"-i%devDirectory%\dependencies\amx_assembly" ^
	"-i%devDirectory%\dependencies\samp-bcrypt\include" ^
	"-i%devDirectory%\dependencies\gBugFix" ^
	"-i%devDirectory%\dependencies\MapFix" ^
	"-i%devDirectory%\dependencies\progress2" ^
	"-i%devDirectory%\dependencies\samp-dyn-dialog-pages" ^
	"-i%devDirectory%\dependencies\samp-geoip" ^
	"-i%devDirectory%\dependencies\samp-weapon-config" ^
	"-i%devDirectory%\dependencies\sscanf" ^
	"-i%devDirectory%\dependencies\crashdetect"

set "compileResult=%ERRORLEVEL%"

echo.
echo =======================
echo.
echo Compile script finished: check the '%amxOutputDirectory%' folder.
echo The next step is to start the server: '%runtimeDirectory%\omp-server.exe'

endlocal & exit /b %compileResult%
