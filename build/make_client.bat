cls
g++ -g ../src/client.cpp -o ../broom -std=c++17 -I "C:/msys64/ucrt64/include" -I ".." -L "C:/msys64/ucrt64/lib" -L "../lib" -lPackage -lboost_system-mt -lboost_serialization-mt -lpthread -lws2_32