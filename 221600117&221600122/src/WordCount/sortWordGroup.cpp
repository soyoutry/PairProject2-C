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
	//显示的个数，默认10个
	int sortNum = 10;
	if (n != 0)
		sortNum = n;

	//词组的长度
	const int Len = m;
	vector<string> que;//向量模拟队列，最大长度为Len

	fopen_s(&file, fn, "r");
	if (file == NULL)
	{
		printf("文件不存在!");
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
			if (f >= 0)//单词前四位是字母
			{
				f++;
				temp += ch;
			}
			else//单词前字母不足四位，后面字母不记录
				f = -1;
		}
		else if (ch >= '0' && ch <= '9')//开头不足四位字母，不算单词
		{
			if (f < 4)
				f = -1;
			else
				temp += ch;
		}
		else//读到分隔符
		{
			//当遇上title或者abstract时，模拟队列清空
			if (temp == "title" && temp == "abstract")
				que.clear();

			if (f >= 4 && temp != "title" && temp != "abstract")
			{
				que.push_back(temp);
				//维持词组的规定长度
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
		//维持词组的规定长度
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

