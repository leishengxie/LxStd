@echo off
echo lsx �������-build-desktop�ļ��У����Ե�......
pause

for /f "delims=" %%i in ('dir /s/b/ad build*') do (
rd /s/q "%%~i"
)

echo ����ļ���ɣ�
echo. & pause