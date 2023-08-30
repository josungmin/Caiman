@echo off

set PROJECT_NAME=UE5_ActionGame
set ENGINE_VERSION=5.1

set PROJECT_DIR=%~dp0
set PROJECT_DIR=%PROJECT_DIR:~0,-8%
set UPROJECT_PATH=%PROJECT_DIR%\%PROJECT_NAME%.uproject

set UE_ENGINE_DIR=
if exist "C:\Program Files\Epic Games\UE_%ENGINE_VERSION%\Engine" (
	set UE_ENGINE_DIR=C:\Program Files\Epic Games\UE_%ENGINE_VERSION%\Engine
	goto Succeeded
)

if exist "D:\UE_%ENGINE_VERSION%\Engine" (
	set UE_ENGINE_DIR=D:\UE_%ENGINE_VERSION%\Engine
	goto Succeeded
)

if exist "E:\UE_%ENGINE_VERSION%\Engine" (
	set UE_ENGINE_DIR=E:\UE_%ENGINE_VERSION%\Engine
	goto Succeeded
)

exit /B 1

:Succeeded
echo Engine in %UE_ENGINE_DIR%

set UE_EXE="%UE_ENGINE_DIR%\Binaries\Win64\UnrealEditor.exe"
set UE_CMD_EXE="%UE_ENGINE_DIR%\Binaries\Win64\UnrealEditor-Cmd.exe"
set UE_UBT_EXE="%UE_ENGINE_DIR%\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
set UE_PYTHON_EXE="%UE_ENGINE_DIR%\Binaries\ThirdParty\Python3\Win64\python.exe"
exit /B 0