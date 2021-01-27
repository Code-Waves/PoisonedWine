// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H
// 引入C++标准库
#include <memory>//智能指针需要
#include<vector>//容器
#include <algorithm>
#include <string>
#include <assert.h>
#include<list>
#include <random>

using namespace std;

#include <gdiplus.h> 						// 引入 GDIPlus,包含头文件
#include <gdipluseffects.h>
#pragma comment(lib, "Gdiplus.lib")		// 链接 GDIPlus库
using namespace Gdiplus;

extern float MAXpercent_memory;//内存使用率: 
extern double MAXcpu_memory;//cpu使用率
extern float Minpercent_memory;//内存使用率: 
extern double Mincpu_memory;//cpu使用率



#include <Vfw.h>
#pragma comment(lib, "VFW32.lib")

// 背景色透明中用到颜色
#define BACK_GROUND_LAYER RGB(0x00, 0x00, 0x00)
#define PI  3.1415926f 
#define Radian2Degree(r) ((180.0f * (r)) / PI(1.0f)) 	// 弧度->角度
#define Degree2Radian(a) ((a) * PI(1.0f) / 180.0f) 		// 角度->弧度
#include "CGame.h"
