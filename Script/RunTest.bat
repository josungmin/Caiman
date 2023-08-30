@echo off
setlocal
call "%~dp0_SetEnv.bat"
%UE_CMD_EXE% "%UPROJECT_PATH%" -Execcmds="Automation RunTest Now %PROJECT_NAME%+Functional Tests; Quit" -log -stdout -NullRHI -NoSplash -LogCmds="global none, LogAutomationCommandLine Display, LogAutomationController Display" %*