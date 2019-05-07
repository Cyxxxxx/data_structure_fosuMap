#include "stdafx.h"

int visit[N];          //�������飬��ǵ��Ƿ��Ѿ�������
string path[N][N]; //������·��
int dist[N][N];  //����ڽӾ���
stack<int> s;  //ջ

void add_att_info();  //��Ӿ�����Ϣ
void att_info_show(Graph *g); //������ʾ
void att_info_search(Graph *g); //��������
void mod_att_info(Graph *g); //�޸�
void del_att_info(Graph *g); //ɾ��
void Floyd(Graph *g);  //�������·��
void find(Graph *g);//Ѱ�����ھ���

void att_show(Graph *g) {
	cout << "�������о����Ӧ��������£�" << endl;
	for (int l = 1; l < N + 1; ++l)
	{
		cout << l << " " << g->vexs[l - 1] << endl;
	}
}

//(2)��Ӿ�����Ϣ

void file_fout(int m) {
	ofstream fout;
	char info[1000];
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//�ַ�����̬д��
	string fileName = buffer;
	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "���ϲ�����" << endl;
	}
	cout << "������þ������Ϣ��" << endl;
	cin >> info;
	fout << info << endl;
	fout.close();
	cout << "������ϣ�" << endl;
	add_att_info();
}

void add_att_info() {
	int m;
	cout << "���������������Ϣ�ľ���ı��(����������0)��" << endl;
	cin >> m;
	if(m!=0)
		if(m>0&&m<=N)
			file_fout(m);
		else {
			cout << "���������������������Ϣ�ľ������ţ�" << endl;
			add_att_info();
		}
}

//(3)��ʾ������Ϣ

void file_fin(Graph *g,int m,int check) {
	ifstream fin;
	string line;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//�ַ�����̬д��
	string fileName = buffer;
	fin.open(fileName);
	if (g->vexs[m - 1] == "") {
		cout << "��δ���𾰵�" << endl;
	}
	else {
		if (!fin.is_open())
		{
			cout << "���ϲ�����" << endl;
		}
		cout << "�þ�����ϢΪ: " << endl;
		while (getline(fin, line)) {//�����������
			cout << line << endl;
		}
		fin.close();
/*		if (check == 5)//��check����ֵΪ5���˵�ѡ��5�������ṩ���ϲ�ѯ����
			att_info_search(g);*/
	}

}

void att_info_show(Graph *g) {//��������ĺ���
	cout << "�������о����Ӧ��������£�" << endl;
	for (int l = 1; l < N + 1; ++l)//����������������ϣ�forѭ��������L��
	{
		cout << l << " " << g->vexs[l - 1] << endl;
		file_fin(g, l, 3);
	}
}


//(4)�޸ľ�����Ϣ

void file_edit(Graph *g, int m) {
	char n;
	ofstream fout;
	ifstream fin;
	string line;
	char buffer[100];
	char info[1000];
	sprintf_s(buffer, "E:\\fosumap\\%d.txt", m);//�ַ�����̬д��
	string fileName = buffer;
	fin.open(fileName);
	if (!fin.is_open())
	{
		cout << "���ϲ�����" << endl;
	}
	cout << "��Ҫ�޸���Ϣ�ľ���ĵ�ǰ��ϢΪ: " << endl;
	while (getline(fin, line)) {
		cout << line << endl;
	}	
	fin.close();
	cout << " Ҫ���ĵ�ǰ��Ϣ�� ?  y / n : " ;
	cin >> n;
	switch (n) {
	case 'y':
		fout.open(fileName);
		cout << "�����������������Ϣ��";
		cin >> info;
		fout << info << endl;
		fout.close();
		fin.open(fileName);
		cout << "������ϣ�" << endl;
		cout << "��Ҫ�޸���Ϣ�ľ���ĵ�ǰ��ϢΪ: " << endl;
		while (getline(fin, line)) {
			cout << line << endl;
		}
		break;
	case 'n':break;
	default:cout << "������y����n��" << endl; break;
	}
//	mod_att_info(g);
}

void mod_att_info(Graph *g){
	ifstream fin;
	int m;
	string line;
	att_show(g);
	cout << "������Ҫ�޸���Ϣ�ľ������(����������0): " << endl;
	cin >> m;
	if (m == 0)
		return;
	file_edit(g, m);
	//��ָ�����ļ�����������ݣ������ַ����������е����� 
	system("pause");
} 

//(5)��ѯ������Ϣ
void att_info_search(Graph *g) {
	ifstream fin;
	int m;
	for (int i = 0; i < N; ++i) {
		//��ͼ������Ϊ�յģ���ʾ�û�����ֹѭ��
		if (g->vexs[i] == "") {
			cout << "���ȴ���У԰ͼ���ȡ�ļ����ݣ�" << endl;
			return;
		}
	}
	att_show(g);
	cout << "������������ʾ��Ϣ�ľ�������: " << endl;
	cin >> m;
	if (m != 0)
		if (m > 0 && m <= N)
			file_fin(g, m, 5);
	//������ʾ
		else {
			cout << "������������ʾ��Ϣ�ľ������ţ�" << endl;
			att_info_search(g);
		}
}

//(6)ɾ��������Ϣ
void file_fd(int m,Graph *g) {
	char fileName[100];
	sprintf_s(fileName, "E:\\fosumap\\%d.txt", m);//�ַ�����̬д��
	if(remove(fileName)==0)
		cout << "ɾ����ϣ�" << endl;
	else
		cout << "ɾ��ʧ�ܣ�" << endl;
}

void del_att_info(Graph *g){
	int m;
	att_show(g);
	cout<<"��������ϣ��ɾ����Ϣ�ľ��㣺"<<endl;
	cin>>m;
	file_fd(m,g);
	//�� n ����Ӧ���ĵ�ֱ��ɾ��
} 

//(7)��·:����������������·��

//��ӡջ����
void Print(Graph *g,stack<int> s, int start, int end)
{	
	int sum_lc=0;
	int stack_length = s.size();//���ջ��
	int *stack_back =new int[stack_length];    //��̬ջ������
/*	cout << stack_length <<"qq" << endl;  ������  */
	int i = stack_length-1;//��ʼ��i��ʹ0��i�ĳ��ȵ���ջ��
	while (!s.empty())
	{
		stack_back[i] = s.top();//��ջ������д������
/*		cout << stack_back[i] << "test" << endl;  ������ */
		--i;//��ջ��Ԫ�ر�д������ĵ�i��λ�ú󣬽�i�Լ�������ջ��Ԫ��
		s.pop();//����Խ�ջ��Ԫ��д����������һ��
	}
	for (int j = 0; j < stack_length; ++j) {
		//		cout << j << "," << stack_length << endl;
		if (j != (stack_length - 1))
			sum_lc += g->adjs[stack_back[j]][stack_back[j + 1]];
	}
//	cout << sum_lc<<endl;
	for (int j = 0; j < stack_length; ++j) {
//		cout << j << "," << stack_length << endl;
		if (sum_lc < (dist[0][stack_back[stack_length - 1]] + 2)) { //��·�̿��Ż�Ϊ�������Ż���ͬ���/�յ����ѡ���룬д��һ��������= =
			if (j == (stack_length - 1)) {
				cout << g->vexs[stack_back[j]]<<endl;
			}
			else {
				cout << g->vexs[stack_back[j]] << "->";
			}
		}
	}
	delete[] stack_back;//�ͷŶ�̬ջ������
//	cout << endl;
}

bool findval(stack<int> s, int val)
{
	while (!s.empty())//��ջ�ǿ�
	{
		if (s.top() == val)//��ջ��Ԫ�ص���һ����֮��ȵĽ�Ҫ��ջ��Ԫ��ʱ����������ջ
		{
			return true;
		}
		s.pop();//��ջ��Ԫ�س�ջ
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
	//��һ������Ҫ������start�ڵ�����������ӣ���������꣬��Ҫ��stack�е�start�ڵ�pop������������޵ݹ�
	s.pop();
}

void ask_w(Graph *g){
	int att1,att2;
	int count = 0;
	int choose;
	Floyd(g);//����һ��Floyd����ʼ������
	//�˵�
	cout << "�����������յ����ţ�" << endl << endl;
	cout << "��㣺"; cin >> att1;
	cout << "�յ㣺"; cin >> att2;
	cout << endl;
	cout << "                    ��·������Ҫ:             " << endl;
	cout << "                      1. ����·��" << endl;
	cout << "                      2. ���·��" << endl;
	cout << "             ����������Ҫ�õ��Ĺ��ܵ����: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		s.push(att1-1);
		while (!s.empty()) {//��ջ�ǿ�
			cout << "Ϊ����ѡ·��Ϊ"<< dist[att1-1][att2-1]+2<<"����" <<endl <<g->vexs[att1-1] << "��" << g->vexs[att2-1] << "������·����" << endl;
			all_way(g, att1 - 1, att2 - 1); //�������·��
		}
		break;
	case 2:
		cout << g->vexs[att1 - 1] << "��" << g->vexs[att2 - 1] << "�����·��Ϊ��";
		cout << path[att1 - 1][att2 - 1] << endl << endl;//���path�����ŵ����·��
		break;
	default:break;
	}
}

//Floyd�㷨�������������̾��벢��·������path������
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
				if (dist[i][k]+dist[k][j] < dist[i][j]) {//����i��j��;�о���k�Ҿ����ֱ�Ӵ�i��jС�������
					dist[i][j] = dist[i][k] + dist[k][j];//����k��·��
					path[i][j] = path[i][k] + "->" + g->vexs[j];//����·��
//					cout << path[i][j] << "b" << endl;
				}
			}

		}
	}
}

//(8)Ѱ�����ھ���
void find(Graph *g) {
	int att;
	cout << "                    ���ھ�����ң�����0���أ���" << endl;
	cout << "������Ҫ���ҵ�һ���������ţ������г������������ڵľ��㣺" << endl;
	cin >> att;
	cout << "           ��" << g->vexs[att-1] << "���ڵľ����У�" << endl;
	cout << "     ";
	for (int j = 0; j < N; ++j)//���α���i������ڽӵ�
	{
		if ((g->adjs[att-1][j] != INF) && (visit[j] == 0))//��i������δ�����ʹ�
		{
//			cout<<g->adjs[0][0];  ������
			cout << g->vexs[j] << "  ";
			visit[j] = 1;
		}
	}
	cout << endl << endl;
}

