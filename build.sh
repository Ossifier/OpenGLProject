#!/bin/bash

# GENERAL COMPILE STRING FOR BUILDING & RUNNING #
g++ -std=c++20 ./src/*.cpp ./thirdpartysrc/*.cpp                                \
                                                                                \
    -o ./bin/prog                                                               \
                                                                                \
    -I ./include                                                                \
    -I ./thirdpartyinclude                                                      \
    -I ./thirdpartyinclude/glad                                                 \
    -I ./thirdpartyinclude/glm-master                                           \
                                                                                \
    -lSDL2 -ldl

sh run.sh
