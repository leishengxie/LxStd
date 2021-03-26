@echo off
echo lsx 清除所有-build-desktop文件夹，请稍等......
pause

for /f "delims=" %%i in ('dir /s/b/ad build*') do (
rd /s/q "%%~i"
)

echo 清除文件完成！
echo. & pause