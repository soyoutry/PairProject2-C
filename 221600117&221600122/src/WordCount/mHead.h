#pragma once
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;

int countChar(char * fn);
int countWord(char * fn);
void sortWord(char *fn, char ct, int sn);
int countLine(char *fn);
bool cmp(pair<int, string> a, pair<int, string> b);
void MapSortOfValue(vector<pair<int, string> >& vec, map<string, int>& m);
void sortWordGroup(char *fn, int m, int n);