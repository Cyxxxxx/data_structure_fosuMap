// fosumap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
 
//需要定义为全局变量
void main1(Graph *g);//校园图构建
void att_info_show(Graph *g);//显示所有景点信息
void add_att_info();//添加景点信息
void mod_att_info(Graph *g);//修改某一景点信息
void att_info_search(Graph *g);//查找某一景点信息
void del_att_info(Graph *g);//删除某一景点信息
void ask_w(Graph *g);//问路
void find(Graph *g);//寻找相邻景点
void del_all(Graph *g);//删除存档
void readGraph_File(Graph *g);//读取存档
//函数声明
Graph *g = new Graph();

//初始化邻接矩阵
void adjs_init(Graph *g) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
		{
			g->adjs[i][j] = INF;
		}
	}
}

void menu_list() {
	cout << "##################################################" << endl;
	cout << "                  1. 创建校园图" << endl;                 
	cout << "                  2. 添加景点信息" << endl;
	cout << "                  3. 显示景点信息" << endl;
	cout << "                  4. 修改景点信息" << endl;
	cout << "                  5. 查询景点信息" << endl;
	cout << "                  6. 删除景点信息" << endl;
	cout << "                  7. 问路" << endl;
	cout << "                  8. 寻找相邻景点" << endl;
	cout << "                  9. 删除存档" << endl;
	cout << "                 10. 读取" << endl;
	cout << "                 11. 退出" << endl;
	cout << "             请输入你需要用到的功能的序号: ";
}
//目录遍历
void mlbl() {
	string muluName[X] = { "E:\\fosumap","E:\\fosumap\\graph","E:\\fosumap\\link" };//目录名数组初始化
	char mulu[20];
	for (int i = 0; i < X; ++i) {
		sprintf_s(mulu, "md %s", muluName[i].c_str());//将目录名数组中元素依次打印为mulu,将string转化为char
//		if (_access(mulu, 0) == -1) //用这一句的话，若目录已存在，会提示
		if (_access(muluName[i].c_str(), 0) == -1) {//若目录不存在，创建目录
			system(mulu);
		}
		else
			continue;
	}
}

void menu(Graph *g) {
	int choose;
	mlbl();//若工作目录页不存在，创建目录
	menu_list();
	cin >> choose;
	switch (choose) {
	case 1:	main1(g);
		menu(g);//创建校园图
		break;
	case 2:add_att_info(); menu(g); break; //添加景点信息
	case 3:att_info_show(g); menu(g); break; //显示景点信息
	case 4:mod_att_info(g); menu(g); break;//修改景点信息
	case 5:att_info_search(g); menu(g); break;//查询景点信息
	case 6:del_att_info(g); menu(g); break;//删除景点信息
	case 7:ask_w(g); menu(g); break;//问路
	case 8:find(g); menu(g); break;//寻找相邻景点
	case 9:del_all(g); break;//删除存档
	case 10:readGraph_File(g);
		cout << "读取成功!" << endl;
		menu(g); break;//读取存档
	case 11:  break; //退出
	default:cout << "请输入序号！" << endl;
	}
}

int main(){
	cout << "#############欢迎使用佛大校园导游查询#############" << endl;
	cout << "##################本软件自动保存##################" << endl;
	adjs_init(g);
	menu(g);
	delete(g);//释放内存
	system("pause");
	return 0;
}
