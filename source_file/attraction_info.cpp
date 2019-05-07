#include "stdafx.h"

int visit[N];          //辅助数组，标记点是否已经被访问
string path[N][N]; //存放最短路径
int dist[N][N];  //存放邻接矩阵
stack<int> s;  //栈

void add_att_info();  //添加景点信息
void att_info_show(Graph *g); //资料显示
void att_info_search(Graph *g); //资料搜索
void mod_att_info(Graph *g); //修改
void del_att_info(Graph *g); //删除
void Floyd(Graph *g);  //生成最短路径
void find(Graph *g);//寻找相邻景点

void att_show(Graph *g) {
	cout << "现在所有景点对应的序号如下：" << endl;
	for (int l = 1; l < N + 1; ++l)
	{
		cout << l << " " << g->vexs[l - 1] << endl;
	}
}

//(2)添加景点信息

void file_fout(int m) {
	ofstream fout;
	char info[1000];
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//字符串动态写入
	string fileName = buffer;
	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "资料不存在" << endl;
	}
	cout << "请输入该景点的信息：" << endl;
	cin >> info;
	fout << info << endl;
	fout.close();
	cout << "输入完毕！" << endl;
	add_att_info();
}

void add_att_info() {
	int m;
	cout << "请输入你想添加信息的景点的编号(返回请输入0)：" << endl;
	cin >> m;
	if(m!=0)
		if(m>0&&m<=N)
			file_fout(m);
		else {
			cout << "请输入请输入你想添加信息的景点的序号！" << endl;
			add_att_info();
		}
}

//(3)显示景点信息

void file_fin(Graph *g,int m,int check) {
	ifstream fin;
	string line;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//字符串动态写入
	string fileName = buffer;
	fin.open(fileName);
	if (g->vexs[m - 1] == "") {
		cout << "还未部署景点" << endl;
	}
	else {
		if (!fin.is_open())
		{
			cout << "资料不存在" << endl;
		}
		cout << "该景点信息为: " << endl;
		while (getline(fin, line)) {//输出景点资料
			cout << line << endl;
		}
		fin.close();
/*		if (check == 5)//若check输入值为5（菜单选项5），则提供资料查询功能
			att_info_search(g);*/
	}

}

void att_info_show(Graph *g) {//调用上面的函数
	cout << "现在所有景点对应的序号如下：" << endl;
	for (int l = 1; l < N + 1; ++l)//逐行输出各景点资料（for循环变量是L）
	{
		cout << l << " " << g->vexs[l - 1] << endl;
		file_fin(g, l, 3);
	}
}


//(4)修改景点信息

void file_edit(Graph *g, int m) {
	char n;
	ofstream fout;
	ifstream fin;
	string line;
	char buffer[100];
	char info[1000];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//字符串动态写入
	string fileName = buffer;
	fin.open(fileName);
	if (!fin.is_open())
	{
		cout << "资料不存在" << endl;
	}
	cout << "你要修改信息的景点的当前信息为: " << endl;
	while (getline(fin, line)) {
		cout << line << endl;
	}	
	fin.close();
	cout << " 要更改当前信息吗 ?  y / n : " ;
	cin >> n;
	switch (n) {
	case 'y':
		fout.open(fileName);
		cout << "请输入你想输入的信息：";
		cin >> info;
		fout << info << endl;
		fout.close();
		fin.open(fileName);
		cout << "输入完毕！" << endl;
		cout << "你要修改信息的景点的当前信息为: " << endl;
		while (getline(fin, line)) {
			cout << line << endl;
		}
		break;
	case 'n':break;
	default:cout << "请输入y或者n！" << endl; break;
	}
//	mod_att_info(g);
}

void mod_att_info(Graph *g){
	ifstream fin;
	int m;
	string line;
	att_show(g);
	cout << "请输入要修改信息的景点序号(返回请输入0): " << endl;
	cin >> m;
	if (m == 0)
		return;
	file_edit(g, m);
	//打开指定的文件，输出其内容，输入字符串覆盖其中的内容 
	system("pause");
} 

//(5)查询景点信息
void att_info_search(Graph *g) {
	ifstream fin;
	int m;
	for (int i = 0; i < N; ++i) {
		//若图顶点有为空的，提示用户并终止循环
		if (g->vexs[i] == "") {
			cout << "请先创建校园图或读取文件数据！" << endl;
			return;
		}
	}
	att_show(g);
	cout << "请输入你想显示信息的景点的序号: " << endl;
	cin >> m;
	if (m != 0)
		if (m > 0 && m <= N)
			file_fin(g, m, 5);
	//错误提示
		else {
			cout << "请输入你想显示信息的景点的序号！" << endl;
			att_info_search(g);
		}
}

//(6)删除景点信息
void file_fd(int m,Graph *g) {
	char fileName[100];
	sprintf_s(fileName, "E:\\fosumap\\%d.txt", m);//字符串动态写入
	if(remove(fileName)==0)
		cout << "删除完毕！" << endl;
	else
		cout << "删除失败！" << endl;
}

void del_att_info(Graph *g){
	int m;
	att_show(g);
	cout<<"请输入你希望删除信息的景点："<<endl;
	cin>>m;
	file_fd(m,g);
	//将 n 所对应的文档直接删除
} 

//(7)问路:输出两个景点的所有路径

//打印栈函数
void Print(Graph *g,stack<int> s, int start, int end)
{	
	int sum_lc=0;
	int stack_length = s.size();//存放栈长
	int *stack_back =new int[stack_length];    //动态栈底数组
/*	cout << stack_length <<"qq" << endl;  测试用  */
	int i = stack_length-1;//初始化i，使0到i的长度等于栈长
	while (!s.empty())
	{
		stack_back[i] = s.top();//将栈顶反向写入数组
/*		cout << stack_back[i] << "test" << endl;  测试用 */
		--i;//当栈顶元素被写入数组的第i个位置后，将i自减并弹出栈顶元素
		s.pop();//这可以将栈顶元素写在数组的最后一个
	}
	for (int j = 0; j < stack_length; ++j) {
		//		cout << j << "," << stack_length << endl;
		if (j != (stack_length - 1))
			sum_lc += g->adjs[stack_back[j]][stack_back[j + 1]];
	}
//	cout << sum_lc<<endl;
	for (int j = 0; j < stack_length; ++j) {
//		cout << j << "," << stack_length << endl;
		if (sum_lc < (dist[0][stack_back[stack_length - 1]] + 2)) { //总路程可优化为变量，优化不同起点/终点的优选距离，写多一个函数吧= =
			if (j == (stack_length - 1)) {
				cout << g->vexs[stack_back[j]]<<endl;
			}
			else {
				cout << g->vexs[stack_back[j]] << "->";
			}
		}
	}
	delete[] stack_back;//释放动态栈底数组
//	cout << endl;
}

bool findval(stack<int> s, int val)
{
	while (!s.empty())//当栈非空
	{
		if (s.top() == val)//当栈顶元素等于一个与之相等的将要入栈的元素时，不让其入栈
		{
			return true;
		}
		s.pop();//将栈顶元素出栈
	}
	return false;
}

void all_way(Graph *g,int start, int end)
{
	//	cout << start << " " << end << endl;
	if (start == end)
	{
		//		cout << "test" ;
		Print(g, s, start, end);
		s.pop();
		return;
	}
	for (int i = 0; i < N; i++)
	{
		if (g->adjs[start][i] != INF && start != i && findval(s, i) == false)
		{
			s.push(i);
			all_way(g, i, end);
		}
	}
	//这一步很重要！对于start节点遍历所有连接，如果遍历完，就要把stack中的start节点pop掉，否则会无限递归
	s.pop();
}

void ask_w(Graph *g){
	int att1,att2;
	int count = 0;
	int choose;
	Floyd(g);//先跑一遍Floyd，初始化数据
	//菜单
	cout << "请输入起点和终点的序号：" << endl << endl;
	cout << "起点："; cin >> att1;
	cout << "终点："; cin >> att2;
	cout << endl;
	cout << "                    问路，你需要:             " << endl;
	cout << "                      1. 所有路径" << endl;
	cout << "                      2. 最短路径" << endl;
	cout << "             请输入你需要用到的功能的序号: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		s.push(att1-1);
		while (!s.empty()) {//当栈非空
			cout << "为你优选路程为"<< dist[att1-1][att2-1]+2<<"以内" <<endl <<g->vexs[att1-1] << "到" << g->vexs[att2-1] << "的所有路径：" << endl;
			all_way(g, att1 - 1, att2 - 1); //输出所有路径
		}
		break;
	case 2:
		cout << g->vexs[att1 - 1] << "到" << g->vexs[att2 - 1] << "的最短路径为：";
		cout << path[att1 - 1][att2 - 1] << endl << endl;//输出path数组存放的最短路径
		break;
	default:break;
	}
}

//Floyd算法，求出两点间的最短距离并将路径存在path数组中
void Floyd(Graph *g) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			dist[i][j] = g->adjs[i][j];
//			cout << g->adjs[0][3] << "test" << endl;
//			cout << dist[i][j] << "a" << endl;
			if (dist[i][j] != INF) {
				path[i][j] = g->vexs[i] + "->" + g->vexs[j];
//				cout << path[i][j] << "p" << endl;
			}
			else {
				path[i][j] = "";
			}

		}
	}
//TEST
/*	cout << dist[0][3]<<"!333"<<endl;
	cout << path[0][3] << "!@" << endl;
	cout << g->adjs[0][4] << "!333" << endl;
	cout << dist[3][4] << "!333" << endl;
	cout << path[3][4] << "!@" << endl;    */
	for (int k = 0; k < N; ++k) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (dist[i][k]+dist[k][j] < dist[i][j]) {//若从i到j的途中经过k且距离比直接从i到j小，则采用
					dist[i][j] = dist[i][k] + dist[k][j];//经过k的路径
					path[i][j] = path[i][k] + "->" + g->vexs[j];//保存路径
//					cout << path[i][j] << "b" << endl;
				}
			}

		}
	}
}

//(8)寻找相邻景点
void find(Graph *g) {
	int att;
	cout << "                    相邻景点查找（输入0返回）：" << endl;
	cout << "输入你要查找的一个景点的序号，程序将列出所有与其相邻的景点：" << endl;
	cin >> att;
	cout << "           与" << g->vexs[att-1] << "相邻的景点有：" << endl;
	cout << "     ";
	for (int j = 0; j < N; ++j)//依次遍历i顶点的邻接点
	{
		if ((g->adjs[att-1][j] != INF) && (visit[j] == 0))//与i相连且未被访问过
		{
//			cout<<g->adjs[0][0];  测试用
			cout << g->vexs[j] << "  ";
			visit[j] = 1;
		}
	}
	cout << endl << endl;
}

