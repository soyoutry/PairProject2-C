#include "mHead.h"


void sortWordGroup(char *fn,int m, int n)
{
	char ch;
	vector<pair<int, string> > vec;
	int f = 0, cnt = 0, k;
	string temp = "";
	string tt = "";
	map<string, int> wmap;
	FILE *file;
	map<string, int>::iterator it;
	vector<string>::iterator vt;
	//��ʾ�ĸ�����Ĭ��10��
	int sortNum = 10;
	if (n != 0)
		sortNum = n;

	//����ĳ���
	const int Len = m;
	vector<string> que;//����ģ����У���󳤶�ΪLen

	fopen_s(&file, fn, "r");
	if (file == NULL)
	{
		printf("�ļ�������!");
		exit(1);
	}

	while ((ch = fgetc(file)) != EOF)
	{
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		{
			if (ch >= 'A' && ch <= 'Z')
			{
				ch += ('a' - 'A');
			}
			if (f >= 0)//����ǰ��λ����ĸ
			{
				f++;
				temp += ch;
			}
			else//����ǰ��ĸ������λ��������ĸ����¼
				f = -1;
		}
		else if (ch >= '0' && ch <= '9')//��ͷ������λ��ĸ�����㵥��
		{
			if (f < 4)
				f = -1;
			else
				temp += ch;
		}
		else//�����ָ���
		{
			//������title����abstractʱ��ģ��������
			if (temp == "title" && temp == "abstract")
				que.clear();

			if (f >= 4 && temp != "title" && temp != "abstract")
			{
				que.push_back(temp);
				//ά�ִ���Ĺ涨����
				if (que.size() > Len)
					que.erase(que.begin());
				if (que.size() == Len)
				{
					tt = "";
					k = 0;
					for (vt = que.begin(); vt != que.end(); vt++)
					{
						k++;
						tt += *vt;
						if (k < Len)
							tt += " ";
					}
					wmap[tt]++;
				}
			}
			f = 0;
			temp = "";
		}
	}
	if (f >= 4 && temp != "title" && temp != "abstract")
	{
		que.push_back(temp);
		//ά�ִ���Ĺ涨����
		if (que.size() > Len)
			que.erase(que.begin());
		if (que.size() == Len)
		{
			tt = "";
			k = 0;
			for (vt = que.begin(); vt != que.end(); vt++)
			{
				k++;
				tt += *vt;
				if (k < Len)
					tt += " ";
			}
			wmap[tt]++;
		}
	}


	MapSortOfValue(vec, wmap);
	if (vec.size() < sortNum)
	{
		for (int i = 0; i < vec.size(); i++)
			cout << '<' << vec[i].second.c_str() << ">: " << vec[i].first << endl;
	}
	else {
		for (int i = 0; i < sortNum; i++)
			cout << '<' << vec[i].second.c_str() << ">: " << vec[i].first << endl;
	}
}

