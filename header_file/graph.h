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
#define N 17 //ͼ�Ķ�����
#define E 26//ͼ�ı��� ȱʡ 
#define X 3//Ŀ¼����
#define INF 100//û�����ڵĶ����Ȩֵ
typedef string vextype; //�������������
typedef int adjtype; //�ߵ�Ȩֵ��������

class Graph{
public:
	vextype vexs[N];
	adjtype adjs[N][N];
	//��ʼ���ڽӾ���
};

