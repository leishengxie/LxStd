@echo off

::设置变量
set PRO_DIR=%cd%
set EXE_NAME=""

if not exist release md release
cd release
copy ..\bin\* .

::for循环格式: for %%I in (command1) do command2
for %%A in (*.dll) do set EXE_NAME=%%A
windeployqt %EXE_NAME%
cd %PRO_DIR%

::echo.是为了实现换行
::&是命令连接符，用来连接echo.和pause
::pause是为了实现暂停
echo. & pause
