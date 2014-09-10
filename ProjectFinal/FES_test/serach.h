#pragma once
#include "textfile.h"
#include "welcome.h"

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;



class serach
{
public:
	serach();
	void exp(vector<textfile>);
	vector<string> getkeyword();
	void printresult();
	vector<string> exp(vector<textfile>, string);
    bool isinset(string s);
	~serach();
private:
	vector<char> symbol;
	vector<string> keyword;
	vector<string> result;

	string&   replace(string&   str, const   string&   old_value, const   string&   new_value);
	void pretreatmentStr(string &str);
	vector<string>  searchresult(vector<textfile> table, string keyword);
	vector<string>  searchresult(vector<textfile> table, string keyword, char symbol, int num);
	vector<string>  searchresultN(vector<textfile> table, string keyword);
	vector<string> checkTableAND(vector<string> keyWord1, vector<string> keyWord2);
	vector<string> checkTableOR(vector<string> keyWord1, vector<string> keyWord2);
};

