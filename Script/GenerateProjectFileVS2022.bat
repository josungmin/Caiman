@echo off
setlocal
call "%~dp0_SetEnv.bat"
call "%UE_ENGINE_DIR%/Build/BatchFiles/Build.bat" -Project="%UPROJECT_PATH%" -projectfiles -game -2022 %*