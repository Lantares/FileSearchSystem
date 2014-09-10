#include "wordtable.h"


wordtable::wordtable()
{
}

int wordtable::getwordnum()
{
    return table.size();
}

string wordtable::getfirst(int s)
{

    map<string, int>::iterator it = table.begin();
    for(int i = 0; i < s; *it++,i++);
    return it->first;
}

int wordtable::getsecond(int s)
{
    map<string, int>::iterator it = table.begin();
    for(int i = 0; i < s; *it++,i++);
    return it->second;
}

void wordtable::setwordtable(string content)
{
    Allnum = 0;
	string bufword = "";
	for (unsigned int j = 0; j < content.size(); j++)
	{
		if (content[j] == ' ')
		{
			table[bufword]++;
            Allnum++;

			bufword = "";
		}
		
		else if (content[j] == '\n')
			continue;
		else if (content[j] == '(')
			table["("]++;
		else if (content[j] == ')')
			table[")"]++;
		else if (content[j] == ',')
        {
            table[","]++;
                table[bufword]++;
                Allnum++;
                bufword = "";

        }
		else if (content[j] == '.')
        {
			table["."]++;

                table[bufword]++;
                Allnum++;
                bufword = "";

        }
		else if (content[j] == '/')
			table["/"]++;
        else if ((content[j] >= 'A' && content[j] <= 'Z') || (content[j] >= 'a' && content[j] <= 'z') || (content[j] >= '0' && content[j] <= '9') || content[j] == '\'' || content[j] == '#' || content[j] == '-' || content[j] == '+')
			bufword = bufword + content[j];
	}
	table[bufword]++;
    Allnum++;
    Allnum = Allnum - count("");

    table.erase("");


}

int wordtable::getAllnum()
{
    return Allnum;
}

void wordtable::printtable()
{
	//cout << "print table" << endl;
	string highest = table.rbegin()->first;     // key value of last element
	map<string, int>::key_compare mycomp = table.key_comp();

	map<string, int>::iterator it = table.begin();
	do 
	{
		cout << setw(20) << it->first << setw(5) << it->second << '\n';
	} while (mycomp((*it++).first, highest));
}

void wordtable::printtable(vector<string> keyword)
{
	//cout << "print table" << endl;
	printstar();
	string highest = table.rbegin()->first;     // key value of last element
	map<string, int>::key_compare mycomp = table.key_comp();

	map<string, int>::iterator it = table.begin();
	do
	{
		vector<string>::iterator s = find(keyword.begin(), keyword.end(), it->first);
		if (s == keyword.end())
			cout << setw(30) << it->first << setw(5) << it->second << '\n';
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			cout << setw(30) << it->first << setw(5) << it->second;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout << endl;
		}
	} while (mycomp((*it++).first, highest));
	printstar();
}

bool wordtable::check(string word)
{
	if (count(word) == 0)
		return false;
	return true;
}
int wordtable::count(string word)
{
	for (map<string, int>::iterator it = table.begin(); it != table.end(); it++)
	if (it->first == word)
		return it->second;
	return 0;
}



wordtable::~wordtable()
{

}


//void main(void)
//{
//	string content = "at higher education with applications in java and how it is modeled with uml (unified modeling language). functions, advantages, disadvantages and basic ideas";
//	wordtable table;
//	table.setwordtable(content);
//	table.printtable();
//	cout << table.check("and") << endl;
//	cout << table.check("at") << endl;
//	cout << table.check("antares") << endl;
//	cout << table.count("and") << endl;
//	cout << table.count("at") << endl;
//	cout << table.count("antares") << endl;
//	vector<string> s;
//	s.push_back("at");
//	s.push_back("and");
//	table.printtable(s);
//}

