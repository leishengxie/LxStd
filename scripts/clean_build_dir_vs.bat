@echo off
echo lsx �������Debug.win32��Debug��Release�ļ��У����Ե�......
pause

::ipch�ļ��У���������Ԥ�����ͷ�ļ���Intellisense�õģ�ɾ����Щ�ļ����ڹ��̵Ŀ�����ȫû��Ӱ��

for /f "delims=" %%i in ('dir /s/b/ad Debug.win32') do (
rd /s/q "%%~i"
)

for /f "delims=" %%i in ('dir /s/b/ad Debug') do (
rd /s/q "%%~i"
)

for /f "delims=" %%i in ('dir /s/b/ad Release') do (
rd /s/q "%%~i"
)

echo ����ļ���ɣ�
echo. & pause