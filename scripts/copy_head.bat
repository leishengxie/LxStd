@echo off
echo lsx ��֤��ǰ�ļ���pro�ļ�ͬ��������ͷ�ļ������Ե�......
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

::�ȿ��������ļ�����ɾ��cpp�ļ�

:: �Ҳ� ����Ҳ̫ǿ���˰�
::/s���Ʒǿյ�Ŀ¼����Ŀ¼�����ʡ�ԡ�/s������xcopy�����ڵ���Ŀ¼�й���
::/e����������Ŀ¼��������Ŀ¼������/e���롰/s���͡�/t��������ѡ��һ��ʹ�á�
::/y ����
xcopy *.h ..\include\ /s /y

echo ������ɣ�
::echo. & pause