#include "fileset.h"


fileset::fileset()
{
}


fileset::~fileset()
{
}

void fileset::clear()
{
    file.clear();
    filenum = 0;
}

string fileset::gettablefirst(string filename,int s)
{
    for (unsigned int i = 0; i < file.size(); i++)
    if (file[i].getfilename() == filename)
        return file[i].getfirst(s);
    return "error";
}

int fileset::gettablesecond(string filename,int s)
{
    for (unsigned int i = 0; i < file.size(); i++)
    if (file[i].getfilename() == filename)
        return file[i].getsecond(s);
    return -1;
}

int fileset::getwordnum(string filename)
{
    for (unsigned int i = 0; i < file.size(); i++)
    if (file[i].getfilename() == filename)
        return file[i].getwordnum();
    return -1;

}

int fileset::getwordnum(int i)
{
    return file[i].getwordnum();
}

int fileset::getAllnum(int i)
{
    return file[i].getAllnum();
}

void fileset::seturl()
{
	int check = 0;
	while (check == 0)
	{
		cout << endl;
		cout << "please input the address" << endl;


		cin >> url;



		//cout << fileAddress << endl;
		if (_chdir(url.data()) == 0)
			check = 1;
		else
			cout << "error." << endl;
	}
}

string fileset::getfilename(int i)
{
    return file[i].getfilename();
}

string fileset::geturl(int i)
{
    return url + "/" + file[i].getfilename();
}

string fileset::gettime(int i)
{
    ostringstream as ;
    as << file[i].gettime();
    string as1 = as.str();
    return as1;
}

void fileset::seturl(string _url)
{
    url = _url;
    _chdir(url.data());
}

void fileset::printfile(vector<string> key)
{
	string filename;
	int check = 0;
	while (check == 0)
	{
		cout << endl;
		cout << "please input the filename" << endl;
		cin >> filename;
		//cout << fileAddress << endl;
		if (printfile(filename, key) == 1)
			check = 1;
		else
			cout << "error." << endl;
	}
}

bool fileset::printtable(string filename, vector<string> key)
{
    for (unsigned int i = 0; i < file.size(); i++)
	if (file[i].getfilename() == filename)
	{
		file[i].printtable(key);
		return 1;
	}
	return 0;
}

void fileset::printtable(vector<string> key)
{
	string filename;
	int check = 0;
	while (check == 0)
	{
		cout << endl;
		cout << "please input the filename" << endl;
		cin >> filename;
		//cout << fileAddress << endl;
		if (printtable(filename, key) == 1)
			check = 1;
		else
			cout << "error." << endl;
	}
}

bool fileset::printfile(string filename, vector<string> key)
{
    for (unsigned int i = 0; i < file.size(); i++)
	if (file[i].getfilename() == filename)
	{
		file[i].printcontent(key);
		return 1;
	}
	return 0;
}

void fileset::printall(vector<string> key)
{
	string filename;
	int check = 0;
	while (check == 0)
	{
		cout << endl;
		cout << "please input the filename" << endl;
		cin >> filename;
		//cout << fileAddress << endl;
		if (printtable(filename, key) == 1)
			check = 1;
		else
			cout << "error." << endl;
		if (printfile(filename, key) == 1)
			check = 1;
		else
			cout << "error." << endl;
	}
}

void fileset::printfilemessage()
{
	printstar();
    for (unsigned int i = 0; i < file.size(); i++)
		file[i].printfilemessage(url);
	printstar();
}

vector<textfile> fileset::getfileset()
{
	return file;
}

void fileset::setTIF()
{
	WIN32_FIND_DATA fd;
	HANDLE h;
	//for serach all the file 
	string name = "*";
	//set the file 
	//"*" means open all no extension
	//"*.txt" means open all txt
	//"*.*" means all 

	h = FindFirstFile(name.data(), &fd);
	//Handle
	int i = 0;
	do {
		if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
			continue;
		textfile buff;
		buff.settextfile(url, (string)fd.cFileName);
		file.push_back(buff);
		i++;
	} while (FindNextFile(h, &fd));
	setfilenum(i);
}
void fileset::setfilenum(int i)
{
	filenum = i;
}

int fileset::getfilenum()
{
	return filenum;
}

string fileset::getfile(int i)
{
    return file[i].getcontent();
}

string fileset::getfile(string filename)
{
    for (unsigned int i = 0; i < file.size(); i++)
    if (file[i].getfilename() == filename)
        return file[i].getcontent();
    return "error";
}
