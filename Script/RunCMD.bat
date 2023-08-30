@echo off
setlocal
call "%~dp0_SetEnv.bat"
%UE_CMD_EXE% "%UPROJECT_PATH%" %*