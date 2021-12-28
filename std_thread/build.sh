#!/bin/bash
echo "执行的文件名：$1";
g++ -pthread  $1 -lm && ./a.out;
