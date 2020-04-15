#pragma once
#ifndef _GETPEDTH  
#define _GETPEDTH _declspec(dllexport)  
#else  
#define _GETPEDTH _declspec(dllimport)  
#endif
#include <iostream> 
#include <string>

using namespace std;
_GETPEDTH int getDepth(int Rows, int Cols, int &x, int &y,  const char* inputDepth_mat, double&laser_depth, bool flag);

/*
关于参数：

Rol、Cols深度图的行和列
x,y生成参考面的x，y的值

inputDepth_mat深度图文件depthBottom01.txt或depthTop01.txt
laser_depth传出来的深度值
flag 1表示上表面
flag 0表示下表面


return
0 成功
1 上表面与下表面重合
2 flag的值既不是0也不是1


*/
