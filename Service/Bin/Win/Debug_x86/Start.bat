
@echo off

// Sc create Service binPath= "C:\Users\Yura\Desktop\Service\Bin\Win\Debug_x86\Service.exe" DisplayName= "KEK" type= own start= auto
 //sc start "Service"
 sc stop "Service"
 sc delete "Service"

@pause