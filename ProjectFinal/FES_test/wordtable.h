#pragma once

#include "welcome.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include <windows.h>


using namespace std;

class wordtable
{
public:
	wordtable();
	void setwordtable(string);
	~wordtable();
	bool check(string);
	int count(string);
	void printtable();
	void printtable(vector<string>);
    int getwordnum();
    string getfirst(int s);
    int getsecond(int s);
    int getAllnum();

private:
	map<string, int> table;
    int Allnum;

};

