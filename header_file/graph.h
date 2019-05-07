#pragma once

#include "iostream"
#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <CString>
#include<direct.h>
#include<io.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
#define N 17 //图的顶点数
#define E 26//图的边数 缺省 
#define X 3//目录总数
#define INF 100//没有相邻的顶点的权值
typedef string vextype; //顶点的数据类型
typedef int adjtype; //边的权值数据类型

class Graph{
public:
	vextype vexs[N];
	adjtype adjs[N][N];
	//初始化邻接矩阵
};

