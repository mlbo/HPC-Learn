#!/bin/bash
echo "执行的文件名：$1";
gcc -pthread  $1 -lm && ./a.out;
