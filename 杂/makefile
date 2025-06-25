

使用于 linux 环境下

makefile

% : 
	g++ -std=c++20 -Wall $@.cpp -o $@.exe
	./$@.exe < $@.in > $@.out 2> $@.err

dir_% :
	touch $*.cpp
	cp test.cpp $*.cpp
	touch $*.in

使用于 windows 环境下

make.bat :
@echo off
mingw32-make %*

use cmd

del x.*

makefile

% : 
	g++ -std=c++20 -Wall $@.cpp -o $@.exe
	./$@.exe < $@.in > $@.out 2> $@.err

dir_% :
	cp "test.cpp" "$*.cpp"
	echo > $*.in

