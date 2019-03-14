#include "mHead.h"

int countChar(char * fn)
{
	char ch;
	int f = 0;//符合条件单词的英文字母数
	int cnt = 0;//字符数
	int cntTitle = 0; //标题数
	string temp = "";
	FILE *file;
	fopen_s(&file, fn, "r");
	if (file == NULL)
	{
		printf("文件不存在!");
		exit(1);
	}
	while ((ch = fgetc(file)) != EOF)
	{

		cnt++;
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
		{
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
			if (f >= 4 && temp == "Title")
			{
				cnt -= 6;
				cntTitle++;
			}
			if (f >= 4 && temp == "Abstract")
				cnt -= 9;
			f = 0;
			temp = "";
		}
		if (ch >= 0 && ch <= 32 || ch == 123)
			cnt--;
	}
	//去除序号
	int sub = 0;
	for (int i = 0; i < cntTitle; i++)
		sub += i / 10 + 1;
	cnt -= sub;
	fclose(file);
	return cnt;
}

int countWord(char * fn)
{
	char ch;
	int f = 0;//符合条件单词的英文字母数
	int cnt = 0;//单词数
	string temp = "";
	FILE *file;
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
			if (f >= 4 && temp != "Title" && temp != "Abstract")
				cnt++;
			f = 0;
			temp = "";
		}
	}
	//若最后一个单词符合条件且到文件末尾
	if (f >= 4 && temp != "Title" && temp != "Abstract")
		cnt++;
	fclose(file);
	return cnt;
}

int countLine(char *fn)
{
	int cnt = 0;
	int f = 0;//每一行的非空字符数
	char ch;
	FILE *file;
	fopen_s(&file, fn, "r");
	if (file == NULL)
	{
		printf("文件不存在!");
		exit(1);
	}
	while ((ch = fgetc(file)) != EOF)
	{
		//遇到换行符
		if (ch == '\n')
		{
			//本行内容为非空字符
			if (f > 0)
				cnt++;
			f = 0;
		}
		//遇到非空字符
		else if (ch != ' ' && ch != '\t')
			f++;
	}
	//最后一行不含回车符，特殊判断
	if (f > 0)
		cnt++;
	fclose(file);
	return cnt;
}

bool cmp(pair<int, string> a, pair<int, string> b)
{
	return (a.first != b.first) ? a.first > b.first:a.second < b.second;
}
void MapSortOfValue(vector<pair<int, string> >& vec, map<string, int>& m)
{
	for (map<string, int>::iterator it = m.begin(); it != m.end(); it++)
		vec.push_back(make_pair(it->second, it->first));
	sort(vec.begin(), vec.end(), cmp);
}

void sortWord(char *fn, char ct, int sn)
{
	char ch;
	vector<pair<int, string> > vec;
	int f = 0, cnt = 0;
	string temp = "";
	int w[2];
	map<string, int> wmap;
	FILE *file;
	map<string, int>::iterator it;
	int sortNum = 10;
	w[0] = ct - '0';
	w[1] = 1;

	if (sn != 0)
		sortNum = sn;

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

			if (temp == "title")
			{
				if (w[0] == 0)
					w[1] = 1;
				else
				{
					w[1] = 10;
					//cout << "!!!!!" << "更改权重" << endl;
				}
			}
			if (temp == "abstract")
				w[1] = 1;


			if (f >= 4 && temp != "title" && temp != "abstract")
			{
				cnt++;
				wmap[temp] += w[1];
			}
			f = 0;
			temp = "";
		}
	}
	if (f >= 4 && temp != "title" && temp != "abstract")
	{
		cnt++;
		wmap[temp] += w[1];
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
