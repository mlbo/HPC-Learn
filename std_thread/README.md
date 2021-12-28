# C++11并发学习

## 参考教程

[创建线程](https://blog.csdn.net/caoshangpa/article/details/52829747)

[线程管理 join && detach](https://blog.csdn.net/caoshangpa/article/details/52831290)

[线程同步 mutex](https://blog.csdn.net/caoshangpa/article/details/52842618)

[线程同步 condition variable && future && promise && packaged_task](https://blog.csdn.net/caoshangpa/article/details/52878122)

## 运行

```bash
# 运行某一cpp文件
./build.sh xxx_xx.cpp
# 运行某一cpp文件并将结果保存到result.txt
./build.sh xxx_xx.cpp > result.txt
# 运行某一cpp文件并将结果保存到result.txt，同时在终端上显示执行结果
./build.sh xxx_xx.cpp  | tee -a result.txt
```