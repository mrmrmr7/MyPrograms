@echo off
call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:C:/C++/baseCMake/a.exe
cl.exe %compilerflags% C:/C++/baseCMake/main.cpp /link %linkerflags%
call "C:/C++/baseCMake/a.exe"