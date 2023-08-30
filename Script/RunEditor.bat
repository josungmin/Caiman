@echo off
setlocal
call "%~dp0_SetEnv.bat"
start "" %UE_EXE% "%UPROJECT_PATH%" %*