
@echo off

rem Sc create Service binPath= "D:\ChildControl\Service\Bin\Win\Debug_x64\Service.exe" DisplayName= "KEK" type= own start= auto
rem sc start "Service"
rem sc stop "Service"
 sc delete "Service"

@pause