@echo off
setlocal

REM Set the path to your executable
set "EXECUTABLE_PATH=C:\dev\sheet.exe"

REM Set run count
set "RUN_COUNT=50"

REM Run cycle
for /L %%i in (1,1,%RUN_COUNT%) do (
    echo Start %%i from %RUN_COUNT%
    start "" "%EXECUTABLE_PATH%"
    timeout /T 1 /NOBREAK
)

endlocal
