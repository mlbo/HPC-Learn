#!/bin/bash
echo "执行的文件名：$1";
nvcc -arch=sm_75  $1 -run
