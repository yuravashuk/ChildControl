
@echo off

rem Sc create Service binPath= "D:\ChildControl\Service\Bin\Win\Release_x64\Service.exe" DisplayName= "Service" type= own start= auto
 sc start "Service"
rem sc stop "Service"
rem sc delete "Service"

@pause