@echo off

set cwd=%cd%

cd DabsFramework

taskkill /f /im "workbenchApp.exe"

for /f "tokens=2,*" %%a in ('reg query "HKCU\SOFTWARE\Bohemia Interactive\Dayz Tools" /v "path" 2^>nul') do set "dayz_tools=%%b"

"%dayz_tools%\Bin\Workbench\workbenchApp.exe" "-mod=P:\DabsFramework -profiles=%cd%\..\Profiles\Workbench -repository=%cwd%"