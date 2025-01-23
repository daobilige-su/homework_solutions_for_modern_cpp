#!/usr/bin/env bash
mkdir build
c++ -c -I ./include src/subtract.cpp -o build/subtract.o
c++ -c -I ./include src/sum.cpp -o build/sum.o
ar rcs build/libipb_arithmetic.a build/sum.o build/subtract.o
c++ -c -I ./include src/main.cpp -o ./build/main.o
c++ ./build/main.o -L ./build -lipb_arithmetic -o ./build/test_ipb_arithmetic

cp ./build/test_ipb_arithmetic ./results/bin/test_ipb_arithmetic
cp ./build/libipb_arithmetic.a ./results/lib/libipb_arithmetic.a 

