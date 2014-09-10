#include "textfile.h"


textfile::textfile()
{
}

string textfile::getcontent()
{
    return content;
}

int textfile::getwordnum()
{
    return table.getwordnum();
}

string textfile::getfirst(int i)
{
    return table.getfirst(i);
}

int textfile::getsecond(int i)
{
    return table.getsecond(i);
}

void textfile::settextfile(string url, string _filename)
{
	url = url + '/' + _filename;

	clock_t t;
	t = clock();

	ifstream file(url.c_str(), std::ifstream::binary);

	file.seekg(0, file.end);
	const int file_size = file.tellg();
	char* file_buf = new char[file_size + 1];
	//make sure the end tag \0 of string.

	memset(file_buf, 0, file_size + 1);

	// Read the entire file into the buffer.
	file.seekg(0, ios::beg);
	file.read(file_buf, file_size);


	if (file)
	{
		content.append(file_buf);
	}
	else
	{
		cout << "error: only " << file.gcount() << " could be read" << endl;
		content.append(file_buf);
	}
	file.close();
	delete[]file_buf;
	table.setwordtable(content);
	time = clock() - t;
	filename = _filename;

}

string textfile::getfilename()
{
	return filename;
}

double textfile::gettime()
{
	return (double)time / 1000;
}

void textfile::printtable()
{
	table.printtable();
}

void textfile::printtable(vector<string> s)
{
	table.printtable(s);
}

void textfile::printcontent()
{
	printstar();
	cout << content << endl;
	printstar();
	
}

void textfile::printcontent(vector<string> keyword)
{
	printstar();
	string bufword = "";
	for (unsigned int j = 0; j < content.size(); j++)
	{
		if (content[j] == ' ')
			output_oneword(keyword, bufword);
		else if (content[j] == '\n')
			continue;
		else if (content[j] == '(')
		{
			output_oneword(keyword, bufword);
			vector<string>::iterator s = find(keyword.begin(), keyword.end(), "(");
			if (s == keyword.end())
				cout << "(";
			else
				highlight_output("(");
		}
		else if (content[j] == ')')
		{
			output_oneword(keyword, bufword);
			vector<string>::iterator s = find(keyword.begin(), keyword.end(), ")");
			if (s == keyword.end())
				cout << ")";
			else
				highlight_output(")");
		}
		else if (content[j] == ',')
		{
			output_oneword(keyword, bufword);
			vector<string>::iterator s = find(keyword.begin(), keyword.end(), ",");
			if (s == keyword.end())
				cout << ",";
			else
				highlight_output(",");
		}
		else if (content[j] == '.')
		{
			output_oneword(keyword, bufword);
			vector<string>::iterator s = find(keyword.begin(), keyword.end(), ".");
			if (s == keyword.end())
				cout << ".";
			else
				highlight_output(".");
		}
		else if (content[j] == '/')
		{
			output_oneword(keyword, bufword);
			vector<string>::iterator s = find(keyword.begin(), keyword.end(), "/");
			if (s == keyword.end())
				cout << "/";
			else
				highlight_output("/");
		}
		else if ((content[j] >= 'a' && content[j] <= 'z') || (content[j] >= '0' && content[j] <= '9') || content[j] == '\'' || content[j] == '-' || content[j] == '+')
			bufword = bufword + content[j];
	}
	cout << endl;
	printstar();
}

bool textfile::check(string s)
{
	return table.check(s);
}

int textfile::count(string s)
{
	return table.count(s);
}

void textfile::printfilemessage(string fileAddress)
{

	cout << setw(15) << filename;
	cout << setw(25) << fileAddress + "/" + filename;
	cout << setw(10) << gettime() << endl;

}

textfile::~textfile()
{
}


//void main(void)
//{
//	textfile file("D:/DS", "document001");
//	file.printtable();
//	cout << file.getfilename() << endl;
//	cout << file.gettime() << endl;
//	file.printcontent();
//	vector<string> s;
//	s.push_back("at");
//	s.push_back("and");
//	s.push_back(".");
//	file.printtable(s);
//	file.printcontent(s);
//}

void textfile::highlight_output(string s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
		FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	cout << s;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int textfile::getAllnum()
{
    return table.getAllnum();
}

bool textfile::isin(vector<string> keyword, string str)
{
	vector<string>::iterator s = find(keyword.begin(), keyword.end(), str);
	if (s == keyword.end())
		return 0;
	return 1;
}

void textfile::output_oneword(vector<string> keyword, string& bufword)
{
	if (bufword == "")
		return;
	if (!isin(keyword, bufword))
		cout << " " << bufword;
	else
	{
		cout << " ";
		highlight_output(bufword);
	}

	bufword = "";
}
