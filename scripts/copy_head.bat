@echo off
echo lsx 保证当前文件与pro文件同级，拷贝头文件，请稍等......
echo %CD%
::pause
set ShellPath = %CD%
if not exist include md include
cd src
::if not exist %resulePath% md %resulePath%;
::set resulePath=F:\work\qt\qt5\LQtTool\include
::cd src

::for /f "delims=" %%i in ('dir /s/b *.h') do (
::xcopy %%i ..\include\
::echo %%i
::)

::先拷贝整个文件夹再删除cpp文件

:: 我操 功能也太强大了吧
::/s复制非空的目录和子目录。如果省略“/s”，则“xcopy”将在单个目录中工作
::/e复制所有子目录，包括空目录。将“/e”与“/s”和“/t”命令行选项一起使用。
::/y 覆盖
xcopy *.h ..\include\ /s /y

echo 拷贝完成！
::echo. & pause