@echo off
echo �������obj pch idb pdb ncb opt plg res sbr ilk suo�ļ������Ե�......
pause
::obj ������Ŀ���ļ�
::pch Ԥ�ȱ���õ�ͷ�ļ�
::idb �ļ��������Ϣ,ʹ�����������±����ʱ��ֻ�ر������¸Ķ����ĺ�����ֻ�������ඨ��Ķ�����Դ�ļ������ر��룬����߱����ٶ�
::pdb �������ݿ��ļ���������¼������Ϣ
::ncb ����˹�ClassView��WizardBar��Component Galleryʹ�õ���Ϣ
::opt �����ļ�����¼ϵͳ����������Ϣ
::plg ��һ�����ı��ļ���������Internet Explorer�򿪣���¼��Build�Ĺ���
::sdf ���̵���Ϣ����������ݿ��ļ�
::sbr VC������Ϊÿ��OBJ�ļ����ɵ�ԭʼ�����Ϣ�ļ�
::ilk ������Ϣ�ļ�
::aps ��Դ�ļ��Ķ����ư汾
::ipch��������Ԥ�����ͷ�ļ� ��Intellisense �õ�

del /f /s /q .\*.obj
del /f /s /q .\*.pch
del /f /s /q .\*.idb
del /f /s /q .\*.pdb
del /f /s /q .\*.ncb 
del /f /s /q .\*.opt 
del /f /s /q .\*.plg
del /f /s /q .\*.sdf
del /f /s /q .\*.sbr
del /f /s /q .\*.ilk
del /f /s /q .\*.aps
del /f /s /q .\*.ipch


echo ����ļ���ɣ�
echo. & pause