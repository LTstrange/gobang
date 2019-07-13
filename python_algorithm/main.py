import ctypes
import time


def func():
    res = 0
    for i in range(100):
        for j in range(100):
            res += 1
    return res


lib = ctypes.cdll.LoadLibrary("./libgobang.so")

lib.func.restype = ctypes.c_int

s_time = time.time()
lib.func()
e_time = time.time()

c_time = e_time - s_time

s_time = time.time()
func()
e_time = time.time()

p_time = e_time - s_time

print(c_time, p_time)
