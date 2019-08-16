用C++来编写五子棋的环境，用python来编写五子棋的算法。
使用ctypes和.so文件来进行两个程序之间的通讯。（练习中）
这是一次尝试。

相关细节：

在棋盘中，0为空，1为黑子，2为白子。15 × 15的棋盘。
算法主体使用alpha-beta剪枝。Python算法处使用深度学习进行优化。
参照alphago，计划使用两个网络（value-net和policy-net）。

封装命令：g++ -fPIC -shared gobang.cpp -o libgobang.so
