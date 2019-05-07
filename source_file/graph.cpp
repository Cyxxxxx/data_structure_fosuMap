
#include "stdafx.h"

int w;

void Creat_SchoolMap(Graph *g);
void schoolMap_link(Graph *g);
void link2(Graph *g);
void readGraph_File(Graph *g);

void menu_list1() {
	cout << "             ����У԰ͼ������Ҫ��:             " << endl;
	cout << "                  1. д�뾰������" << endl;
	cout << "                  2. �������ڹ�ϵ" << endl;
	cout << "                  0. ����" << endl;
	cout << "             ����������Ҫ�õ��Ĺ��ܵ����: ";
}

void main1(Graph *g) {
	int choose;
	menu_list1();
	cin >> choose;
	switch (choose) {
	case 0:break;
	case 1:	Creat_SchoolMap(g);
		main1(g);//����У԰ͼ
		break;
	case 2:schoolMap_link(g); main1(g); break; //��Ӿ�����Ϣ
	default:cout << "��������ţ�" << endl;
	}

}

void gout(int m, Graph *g) {
	ofstream fout;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\Graph\\%d.txt", m+1);//�ַ�����̬д��
	string fileName = buffer;
	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "Ŀ¼����ʧ��" << endl;
	}
	fout << g->vexs[m] << endl;
	fout.close();
	cout << "�þ����Ѵ浵��ϣ�" << endl;
}

void glink(int vex1,int vex2, Graph *g,int w) {
	ofstream fout;
	char buffer[100];
	sprintf_s(buffer, "E:\\fosumap\\link\\%d��%d.txt",vex1,vex2);//�ַ�����̬д��
	string fileName = buffer;

	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "Ŀ¼����ʧ��" << endl;
	}
	fout << w;
	fout.close();
	g->adjs[vex1 - 1][vex2 - 1] = w;
	cout << "g->adjs[" << vex1 - 1 << "][" << vex2 - 1 << "]=" << w << endl;
//	g->adjs[vex1 - 1][vex2 - 1] = 1;
}

// (1)����У԰ͼ
void Creat_SchoolMap(Graph *g){
	//���붥����Ϣ
    //char temp_char;
	for(int i=0;i<N;++i){
		cout<<"����У԰����"<<endl;
		cout<<"����һ��ѧУ����"<<endl;
		cin>>g->vexs[i];
//		cout << g->vexs[i] << endl;
		gout(i,g);
		//cin>>temp_char;
		//g->vexs[i]=temp_char;
	}


}
void schoolMap_link(Graph *g) {
	//д���ڽӾ���
	int vex1, vex2; //�ߵĶ���
	char a;
	cout << "�������о����Ӧ��������£�" << endl;
	for (int l = 1; l < N + 1; ++l)
	{
		cout << l << " " << g->vexs[l - 1] << endl;
	}
	cout << "�����������������ţ�" << endl;
	cin >> vex1 >> vex2;
	cout << "����������? y/n : ";
	cin >> a;
	switch (a) {
	case 'y':
		cout << "���������ǵľ��룺" << endl;
		cin >> w;
		glink(vex1, vex2, g, w);//����ͼ����֮��������
		glink(vex2, vex1, g, w);
		break;
	case 'n':
		g->adjs[vex1 - 1][vex2 - 1] = INF;
		g->adjs[vex2 - 1][vex1 - 1] = INF;
		cout << "����������Ĺ�ϵ��ȷ����ϣ�" << endl;
		break;
	default:
		cout << "������y����n" << endl;
	}
	link2(g);
	cout << "����������Ĺ�ϵ��ȷ����ϣ�" << endl;
}
//���ڽӾ���Գƣ�����ͼ��
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
				sprintf_s(fileName, "E:\\fosumap\\link\\%d��%d.txt", i, j);//�ַ�����̬д��
				if (remove(fileName) != 0) {
					cout << "ERROR: �ļ� " << fileName << " ɾ��ʧ��" << endl;
				}
			}
			else
				continue;
		}
	}
	if (system("rd E:\\fosumap\\link") != 0)
		cout << "ERROR: Ŀ¼  E:\\fosumap\\link ɾ��ʧ��" << endl;
	for (int i = 1; i <= N; ++i) {
		sprintf_s(fileName, "E:\\fosumap\\graph\\%d.txt", i);//�ַ�����̬д��
		if (remove(fileName) != 0) {
			cout << "ERROR: �ļ� " << fileName << " ɾ��ʧ��" << endl;
		}
	}
	if (system("rd E:\\fosumap\\graph") != 0)
		cout << "ERROR: Ŀ¼  E:\\fosumap\\graph ɾ��ʧ��" << endl;
	for (int i = 1; i <= N; ++i) {
		sprintf_s(fileName, "E:\\fosumap\\%d.txt", i);//�ַ�����̬д��
		if (remove(fileName) != 0) {
			cout << "ERROR: �ļ� " << fileName << " ɾ��ʧ��" << endl;
		}
	}
	if (system("rd E:\\fosumap") == 0) {
		cout << "ɾ���ɹ���" << endl;
	}
	else {
		cout << "ɾ��ʧ�ܣ�" << endl;
	}
}

void readGraph_File(Graph *g) {
	ifstream check;
	string line;
	int w;
	char buffer[100];
	//��ȡͼ��������
	for (int i = 1; i < N + 1; ++i) {
		sprintf_s(buffer, "E:\\fosumap\\Graph\\%d.txt", i);//�ַ�����̬д��
		string fileName = buffer;
		check.open(fileName);
		if (!check.is_open())//����ļ�������
			cout << "�������"<<i<<"����ȱʧ"<< endl;
		else {
			getline(check, line);
			g->vexs[i - 1] = line;
		}
		check.close();
	}
	//��ȡ�ڽӾ���
	for (int x = 1; x < N+1; ++x) {
		for (int y = 1; y < N + 1; ++y) {
			if (y == x)
				continue;
			sprintf_s(buffer, "E:\\fosumap\\link\\%d��%d.txt", x,y);//�ַ�����̬д��
//			cout << buffer << endl;
			string fileName = buffer;
//			cout << fileName<<endl;
			check.open(fileName);
			if (!check.is_open()) {//����ļ�������
				g->adjs[x - 1][y - 1] = INF;
//				cout << x - 1 << "," << y - 1 << "," << g->adjs[x - 1][y - 1] << endl;
			}
			else {
				while (!check.eof())            // ��δ���ļ�����һֱѭ�� 
				{
					check >> w;
/*					cout << w << endl;  ������*/
					g->adjs[x - 1][y - 1] = w;

				}
			}
			check.close();//ÿѭ����һ�Σ����ļ�����������رգ��Ը�������
		}
		check.close();//ÿѭ����һ�Σ����ļ�����������رգ��Ը�������
	}
	link2(g);
}