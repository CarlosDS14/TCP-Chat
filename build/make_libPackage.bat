cls
g++ -c ../Package.cpp -o ../Package.o -std=c++17 -I "C:/msys64/ucrt64/include"
ar rcs ../lib/libPackage.a ../Package.o