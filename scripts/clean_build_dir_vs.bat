@echo off
echo lsx 清除所有Debug.win32、Debug、Release文件夹，请稍等......
pause

::ipch文件夹：用来保存预编译的头文件和Intellisense用的，删除这些文件对于工程的开发完全没有影响

for /f "delims=" %%i in ('dir /s/b/ad Debug.win32') do (
rd /s/q "%%~i"
)

for /f "delims=" %%i in ('dir /s/b/ad Debug') do (
rd /s/q "%%~i"
)

for /f "delims=" %%i in ('dir /s/b/ad Release') do (
rd /s/q "%%~i"
)

echo 清除文件完成！
echo. & pause