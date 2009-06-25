#!/bin/bash
gcc main.cpp -o main.o `sdl-config --cflags --libs` -lGL -lGLU