@echo off
@set cpu=i386

call "C:\Program Files (x86)\Microsoft Platform SDK\SetEnv.cmd" /XP32 /RETAIL
call "%DXSDK_DIR%\Utilities\bin\Dx_Setenv.cmd"
echo.
call "%VCToolkitInstallDir%\vcvars32.bat"
