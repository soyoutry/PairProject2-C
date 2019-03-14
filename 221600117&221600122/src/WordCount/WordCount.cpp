#include "mHead.h"

int main(int argc, char *argv[])
{
	char *inputFile = nullptr, *outputFile = nullptr, *fWeg = nullptr;
	int sortNum = 0;
	int m = -1;
	for (int i = 1; i < argc; i += 2)
	{
		switch (argv[i][1])
		{
		case 'i':
			inputFile = argv[i + 1];
			break;
		case 'o':
			outputFile = argv[i + 1];
			break;
		case 'w':
			fWeg = argv[i + 1];
			break;
		case 'n':
				sortNum = atoi(argv[i + 1]);
				break;
		case 'm':
			m = atoi(argv[i + 1]);
		}
	}	
	ofstream of(outputFile);
	streambuf *coutbackup;
	coutbackup = cout.rdbuf(of.rdbuf());//重定向输出到resul.txt文件中
	

	int charTotal = countChar(inputFile);
	int wordTotal = countWord(inputFile);
	int lineTotal = countLine(inputFile);

	cout << "characters: " << charTotal << endl;
	cout << "words: " << wordTotal << endl;
	cout << "lines: " << lineTotal << endl;

	if (m == -1)
		sortWord(inputFile, fWeg[0], sortNum);
	else
		sortWordGroup(inputFile, m, sortNum);
	return 0;
}