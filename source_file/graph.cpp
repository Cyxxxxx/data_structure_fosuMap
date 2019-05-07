
#include "stdafx.h"

int w;

void Creat_SchoolMap(Graph *g);
void schoolMap_link(Graph *g);
void link2(Graph *g);
void readGraph_File(Graph *g);

void menu_list1() {
	cout << "             创建校园图，你需要做:             " << endl;
	cout << "                  1. 写入景点名称" << endl;
	cout << "                  2. 景点相邻关系" << endl;
	cout << "                  0. 返回" << endl;
	cout << "             请输入你需要用到的功能的序号: ";
}

void main1(Graph *g) {
	int choose;
	menu_list1();
	cin >> choose;
	switch (choose) {
	case 0:break;
	case 1:	Creat_SchoolMap(g);
		main1(g);//创建校园图
		break;
	case 2:schoolMap_link(g); main1(g); break; //添加景点信息
	default:cout << "请输入序号！" << endl;
	}

}

void gout(int m, Graph *g) {
	ofstream fout;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\Graph\\%d.txt", m+1);//字符串动态写入
	string fileName = buffer;
	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "目录创建失败" << endl;
	}
	fout << g->vexs[m] << endl;
	fout.close();
	cout << "该景点已存档完毕！" << endl;
}

void glink(int vex1,int vex2, Graph *g,int w) {
	ofstream fout;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\link\\%d→%d.txt",vex1,vex2);//字符串动态写入
	string fileName = buffer;

	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "目录创建失败" << endl;
	}
	fout << w;
	fout.close();
	g->adjs[vex1 - 1][vex2 - 1] = w;
	cout << "g->adjs[" << vex1 - 1 << "][" << vex2 - 1 << "]=" << w << endl;
//	g->adjs[vex1 - 1][vex2 - 1] = 1;
}

// (1)创建校园图
void Creat_SchoolMap(Graph *g){
	//输入顶点信息
    //char temp_char;
	for(int i=0;i<N;++i){
		cout<<"创建校园网："<<endl;
		cout<<"输入一个学校景点"<<endl;
		cin>>g->vexs[i];
//		cout << g->vexs[i] << endl;
		gout(i,g);
		//cin>>temp_char;
		//g->vexs[i]=temp_char;
	}


}
void schoolMap_link(Graph *g) {
	//写入邻接矩阵
	int vex1, vex2; //边的顶点
	char a;
	cout << "现在所有景点对应的序号如下：" << endl;
	for (int l = 1; l < N + 1; ++l)
	{
		cout << l << " " << g->vexs[l - 1] << endl;
	}
	cout << "请输入两个景点的序号：" << endl;
	cin >> vex1 >> vex2;
	cout << "它们相邻吗? y/n : ";
	cin >> a;
	switch (a) {
	case 'y':
		cout << "请输入它们的距离：" << endl;
		cin >> w;
		glink(vex1, vex2, g, w);//无向图两点之间距离相等
		glink(vex2, vex1, g, w);
		break;
	case 'n':
		g->adjs[vex1 - 1][vex2 - 1] = INF;
		g->adjs[vex2 - 1][vex1 - 1] = INF;
		cout << "这两个景点的关系已确认完毕！" << endl;
		break;
	default:
		cout << "请输入y或者n" << endl;
	}
	link2(g);
	cout << "这两个景点的关系已确认完毕！" << endl;
}
//将邻接矩阵对称（无向图）
void link2(Graph *g) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (g->adjs[i][j] != INF)
				g->adjs[j][i] = g->adjs[i][j];
			else
				g->adjs[i][j] = g->adjs[j][i];
		}
	}
}

void del_all(Graph *g) {
	readGraph_File(g);
	char fileName[100];
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (g->adjs[i - 1][j - 1] != INF && i!=j) {
				sprintf_s(fileName, "E:\\fosumap\\link\\%d→%d.txt", i, j);//字符串动态写入
				if (remove(fileName) != 0) {
					cout << "ERROR: 文件 " << fileName << " 删除失败" << endl;
				}
			}
			else
				continue;
		}
	}
	if (system("rd E:\\fosumap\\link") != 0)
		cout << "ERROR: 目录  E:\\fosumap\\link 删除失败" << endl;
	for (int i = 1; i <= N; ++i) {
		sprintf_s(fileName, "E:\\fosumap\\graph\\%d.txt", i);//字符串动态写入
		if (remove(fileName) != 0) {
			cout << "ERROR: 文件 " << fileName << " 删除失败" << endl;
		}
	}
	if (system("rd E:\\fosumap\\graph") != 0)
		cout << "ERROR: 目录  E:\\fosumap\\graph 删除失败" << endl;
	for (int i = 1; i <= N; ++i) {
		sprintf_s(fileName, "E:\\fosumap\\%d.txt", i);//字符串动态写入
		if (remove(fileName) != 0) {
			cout << "ERROR: 文件 " << fileName << " 删除失败" << endl;
		}
	}
	if (system("rd E:\\fosumap") == 0) {
		cout << "删除成功！" << endl;
	}
	else {
		cout << "删除失败！" << endl;
	}
}

void readGraph_File(Graph *g) {
	ifstream check;
	string line;
	int w;
	char buffer[100];
	//获取图顶点数据
	for (int i = 1; i < N + 1; ++i) {
		sprintf_s(buffer, "E:\\fosumap\\Graph\\%d.txt", i);//字符串动态写入
		string fileName = buffer;
		check.open(fileName);
		if (!check.is_open())//如果文件不存在
			cout << "景点序号"<<i<<"资料缺失"<< endl;
		else {
			getline(check, line);
			g->vexs[i - 1] = line;
		}
		check.close();
	}
	//获取邻接矩阵
	for (int x = 1; x < N+1; ++x) {
		for (int y = 1; y < N + 1; ++y) {
			if (y == x)
				continue;
			sprintf_s(buffer, "E:\\fosumap\\link\\%d→%d.txt", x,y);//字符串动态写入
//			cout << buffer << endl;
			string fileName = buffer;
//			cout << fileName<<endl;
			check.open(fileName);
			if (!check.is_open()) {//如果文件不存在
				g->adjs[x - 1][y - 1] = INF;
//				cout << x - 1 << "," << y - 1 << "," << g->adjs[x - 1][y - 1] << endl;
			}
			else {
				while (!check.eof())            // 若未到文件结束一直循环 
				{
					check >> w;
/*					cout << w << endl;  测试用*/
					g->adjs[x - 1][y - 1] = w;

				}
			}
			check.close();//每循环完一次，将文件输入流对象关闭，以更新数据
		}
		check.close();//每循环完一次，将文件输入流对象关闭，以更新数据
	}
	link2(g);
}