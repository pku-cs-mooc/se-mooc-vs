rem @echo off
set mypath=%~dp0
set srcpath=%mypath%..
if "%1"=="" goto :print_help
set targetpath=%mypath%SEH\%1
cd %mypath%
7z.exe x %1.tar.gz
7z.exe x %1.tar
del %1.tar
xcopy /E /Y %srcpath%\analysis %targetpath%\analysis
xcopy /E /Y %srcpath%\index %targetpath%\index
xcopy /E /Y %srcpath%\query %targetpath%\query
xcopy /E /Y %srcpath%\scorer %targetpath%\scorer
xcopy /E /Y %srcpath%\util %targetpath%\util
cd SEH\%1
..\..\7z.exe a -ttar ..\..\%1.output.tar analysis
..\..\7z.exe a -ttar ..\..\%1.output.tar index
..\..\7z.exe a -ttar ..\..\%1.output.tar query
..\..\7z.exe a -ttar ..\..\%1.output.tar scorer
..\..\7z.exe a -ttar ..\..\%1.output.tar util
cd ..\..
rmdir SEH /s /q
7z.exe a -tgzip %1.output.tar.gz %1.output.tar
del %1.output.tar
move %1.output.tar.gz ..\%1.tar.gz
cscript MessageBox.vbs "%1.tar.gz has been created!"
cd ..
goto :eof

:print_help
  echo "CreateHomeworkPackage.bat {ex_number}"
  echo "  ex_number: ex1, ex2, ..., ex7"