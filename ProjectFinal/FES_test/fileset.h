#pragma once
#undef UNICODE

#include <iostream>
#include <vector>
#include <windows.h>
#include <direct.h>
#include <sstream>

#include "textfile.h"
#include "welcome.h"

class fileset
{
public:
	fileset();
	~fileset();

	void setTIF();
	void seturl();
    void seturl(string);
	void printfilemessage();
	void printall(vector<string>);
	bool printfile(string filename, vector<string> key);
	void printfile(vector<string>);
	bool printtable(string filename, vector<string> key);
	void printtable(vector<string>);
	vector<textfile> getfileset();
    string getfile(string filename);
    void clear();


	void setfilenum(int i);
	int getfilenum();
    string getfilename(int i);
    string geturl(int i);
    string gettime(int i);
    string getfile(int i);
    int getwordnum(int i);
    int getwordnum(string filename);
    string gettablefirst(string filename, int i);
    int gettablesecond(string filename, int i);
    int getAllnum(int i);

private:
	vector<textfile> file;
	string url;
	int filenum;

};

