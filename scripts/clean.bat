@echo off
echo 清除所有obj pch idb pdb ncb opt plg res sbr ilk suo文件，请稍等......
pause
::obj 二进制目标文件
::pch 预先编译好的头文件
::idb 文件保存的信息,使编译器在重新编译的时候只重编译最新改动过的函数和只对最新类定义改动过的源文件进行重编译，以提高编译速度
::pdb 程序数据库文件，用来记录调试信息
::ncb 存放了供ClassView、WizardBar和Component Gallery使用的信息
::opt 配置文件，记录系统工作环境信息
::plg 是一个超文本文件，可以用Internet Explorer打开，记录了Build的过程
::sdf 工程的信息保存成了数据库文件
::sbr VC编译器为每个OBJ文件生成的原始浏览信息文件
::ilk 连接信息文件
::aps 资源文件的二进制版本
::ipch用来保存预编译的头文件 和Intellisense 用的

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


echo 清除文件完成！
echo. & pause