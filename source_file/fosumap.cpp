// fosumap.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
 
//��Ҫ����Ϊȫ�ֱ���
void main1(Graph *g);//У԰ͼ����
void att_info_show(Graph *g);//��ʾ���о�����Ϣ
void add_att_info();//��Ӿ�����Ϣ
void mod_att_info(Graph *g);//�޸�ĳһ������Ϣ
void att_info_search(Graph *g);//����ĳһ������Ϣ
void del_att_info(Graph *g);//ɾ��ĳһ������Ϣ
void ask_w(Graph *g);//��·
void find(Graph *g);//Ѱ�����ھ���
void del_all(Graph *g);//ɾ���浵
void readGraph_File(Graph *g);//��ȡ�浵
//��������
Graph *g = new Graph();

//��ʼ���ڽӾ���
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
	cout << "                  1. ����У԰ͼ" << endl;                 
	cout << "                  2. ��Ӿ�����Ϣ" << endl;
	cout << "                  3. ��ʾ������Ϣ" << endl;
	cout << "                  4. �޸ľ�����Ϣ" << endl;
	cout << "                  5. ��ѯ������Ϣ" << endl;
	cout << "                  6. ɾ��������Ϣ" << endl;
	cout << "                  7. ��·" << endl;
	cout << "                  8. Ѱ�����ھ���" << endl;
	cout << "                  9. ɾ���浵" << endl;
	cout << "                 10. ��ȡ" << endl;
	cout << "                 11. �˳�" << endl;
	cout << "             ����������Ҫ�õ��Ĺ��ܵ����: ";
}
//Ŀ¼����
void mlbl() {
	string muluName[X] = { "E:\\fosumap","E:\\fosumap\\graph","E:\\fosumap\\link" };//Ŀ¼�������ʼ��
	char mulu[20];
	for (int i = 0; i < X; ++i) {
		sprintf_s(mulu, "md %s", muluName[i].c_str());//��Ŀ¼��������Ԫ�����δ�ӡΪmulu,��stringת��Ϊchar
//		if (_access(mulu, 0) == -1) //����һ��Ļ�����Ŀ¼�Ѵ��ڣ�����ʾ
		if (_access(muluName[i].c_str(), 0) == -1) {//��Ŀ¼�����ڣ�����Ŀ¼
			system(mulu);
		}
		else
			continue;
	}
}

void menu(Graph *g) {
	int choose;
	mlbl();//������Ŀ¼ҳ�����ڣ�����Ŀ¼
	menu_list();
	cin >> choose;
	switch (choose) {
	case 1:	main1(g);
		menu(g);//����У԰ͼ
		break;
	case 2:add_att_info(); menu(g); break; //��Ӿ�����Ϣ
	case 3:att_info_show(g); menu(g); break; //��ʾ������Ϣ
	case 4:mod_att_info(g); menu(g); break;//�޸ľ�����Ϣ
	case 5:att_info_search(g); menu(g); break;//��ѯ������Ϣ
	case 6:del_att_info(g); menu(g); break;//ɾ��������Ϣ
	case 7:ask_w(g); menu(g); break;//��·
	case 8:find(g); menu(g); break;//Ѱ�����ھ���
	case 9:del_all(g); break;//ɾ���浵
	case 10:readGraph_File(g);
		cout << "��ȡ�ɹ�!" << endl;
		menu(g); break;//��ȡ�浵
	case 11:  break; //�˳�
	default:cout << "��������ţ�" << endl;
	}
}

int main(){
	cout << "#############��ӭʹ�÷��У԰���β�ѯ#############" << endl;
	cout << "##################������Զ�����##################" << endl;
	adjs_init(g);
	menu(g);
	delete(g);//�ͷ��ڴ�
	system("pause");
	return 0;
}
