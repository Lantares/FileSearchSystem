#pragma once

#include "wordtable.h"
#include "welcome.h"

#include <ctime>
#include <iostream>     
#include <fstream>      
#include <string>


using namespace std;



class textfile
{
public:
	textfile();
	~textfile();
	void settextfile(string, string);
	void printtable();
	void printtable(vector<string>);
	void printcontent();
	void printcontent(vector<string>);
	void printfilemessage(string);
	string getfilename();
	double gettime();
	bool check(string);
	int count(string);
    string getcontent();\
    int getwordnum();
    string getfirst(int i);
    int getsecond(int i);
    int getAllnum();


private:
	wordtable table;
	string filename;
	clock_t time;
	string content;


	void highlight_output(string);
	bool isin(vector<string>, string);
	void output_oneword(vector<string>, string&);
};

