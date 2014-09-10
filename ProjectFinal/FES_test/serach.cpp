#include "serach.h"


serach::serach()
{
}


serach::~serach()
{
}

void serach::printresult()
{
	printstar();
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << endl;
	printstar();
}

vector<string> serach::getkeyword()
{
	return keyword;
}

vector<string> serach::exp(vector<textfile> table, string input)
{
	pretreatmentStr(input);

    vector<vector<string> > bufvs;
	vector<char> symbol;
	while (!input.empty())
	{
		int i = 0;
		if (input[0] == '"')
		{
			for (i = 1; input[i] != '"'; i++);
			keyword.push_back(input.substr(1, i - 1));
			bufvs.push_back(searchresult(table, input.substr(1, i - 1)));
			input = input.substr(i + 1, input.size() - 1);
		}
		else if (input[0] == '+')
		{
			symbol.push_back('+');
			input = input.substr(1, input.size() - 1);
		}
		else if (input[0] == '*')
		{
			symbol.push_back('*');
			input = input.substr(1, input.size() - 1);
		}
		else if (input[0] == 'C')
		{
            int is = 1;
            for(; input[is] != '"'; is++);
            is++;

			string key;
			char symbol;
			int intbuf;
            for (i = is; input[i] != '"'; i++);
            keyword.push_back(input.substr(is, i - is));
            key = input.substr(is, i - is);
			input = input.substr(i + 1, input.size() - 1);
			//cout << input << endl;
            for (i = 0; input[i] != '>' && input[i] != '<' && input[i] != '='; i++);
            symbol = input[i];
			//cout << symbol;
            input = input.substr(i + 1, input.size() - 1);
            for (i = 0; input[i] <= '9' && input[i] >= '0' && i < input.size(); i++);
			intbuf = atoi(input.substr(0, i + 1).c_str());
			//cout  << "intbuf :"<< intbuf << endl;
			input = input.substr(i, input.size() - 1);
            //cout << input << endl;
			bufvs.push_back(searchresult(table, key, symbol, intbuf));
		}
		else if (input[0] == 'N')
        {
            int is = 1;
            for(; input[is] != '"'; is++);
            is++;
            for (i = is; input[i] != '"'; i++);
            keyword.push_back(input.substr(is, i - is));
            bufvs.push_back(searchresultN(table, input.substr(is, i - is)));
			input = input.substr(i + 1, input.size() - 1);
		}
		else if (input[0] == '(')
		{
			for (i = 1; input[i] != ')'; i++);
			bufvs.push_back(exp(table, input.substr(1, i - 1)));
			input = input.substr(i + 1, input.size() - 1);
		}
	}

	vector<string> searchBUF = bufvs[0];
	for (int i = 0; i < symbol.size(); i++)
	{
			if (symbol[i] == '*')
				searchBUF = checkTableOR(searchBUF, bufvs[i + 1]);

			else if (symbol[i] == '+')
				searchBUF = checkTableAND(searchBUF, bufvs[i + 1]);
	}
	return searchBUF;

}
void serach::exp(vector<textfile> table)
{
	string input;

	cout << "please input the keyword" << endl;
	cin.sync();
	getline(cin, input);

	result = exp(table, input);


}

bool serach::isinset(string s)
{
    for (int i = 0; i < keyword.size(); i++)
        if(keyword[i]== s)
            return 1;
    return 0;
}



string&   serach::replace(string&   str, const   string&   old_value, const   string&   new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())   {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else   break;
	}
	return   str;
}

void serach::pretreatmentStr(string &str)
{
	replace(str, " ", "");
	replace(str, "AND", "*");
	replace(str, "OR", "+");
	replace(str, "NOT", "N");
	replace(str, "COUNT", "C");
}


vector<string>  serach::searchresult(vector<textfile> table, string keyword)
{
	vector<string> result;
	for (unsigned int i = 0; i < table.size(); i++)
	{
		if (table[i].check(keyword) == 1)
			result.push_back(table[i].getfilename());
	}
	return result;
}

vector<string>  serach::searchresultN(vector<textfile> table, string keyword)
{
	vector<string> result;
	for (unsigned int i = 0; i < table.size(); i++)
	{
		if (table[i].check(keyword) == 0)
			result.push_back(table[i].getfilename());
	}
	return result;
}

vector<string>  serach::searchresult(vector<textfile> table, string keyword, char symbol, int num)
{
	vector<string> result;
	if (symbol == '>')
	{
		for (unsigned int i = 0; i < table.size(); i++)
		{
			if (table[i].count(keyword) > num)
				result.push_back(table[i].getfilename());
		}
	}
	else if (symbol == '=')
	{
		for (unsigned int i = 0; i < table.size(); i++)
		{
			if (table[i].count(keyword) == num)
				result.push_back(table[i].getfilename());
		}
	}
	else if (symbol == '<')
	{
		for (unsigned int i = 0; i < table.size(); i++)
		{
			if (table[i].count(keyword) < num)
				result.push_back(table[i].getfilename());
		}
	}
	return result;
}

vector<string> serach::checkTableAND(vector<string> keyWord1, vector<string> keyWord2)
{
	vector<string> answer;
	for (unsigned int i = 0; i < keyWord2.size(); i++)
		keyWord1.push_back(keyWord2[i]);
	//let it together
	sort(keyWord1.begin(), keyWord1.end());
	//sort it
	//P.S. may i can use set?
	answer.push_back(keyWord1[0]);
	//pushback the first one
	for (unsigned int i = 1; i < keyWord1.size(); i++)
	if (keyWord1[i] != keyWord1[i - 1])
		answer.push_back(keyWord1[i]);
	return answer;
}

vector<string> serach::checkTableOR(vector<string> keyWord1, vector<string> keyWord2)
{
	vector<string> answer;
	for (unsigned int i = 0; i < keyWord1.size(); i++)
	for (unsigned int j = 0; j < keyWord2.size(); j++)
	if (keyWord1[i] == keyWord2[j])
		answer.push_back(keyWord2[j]);
	return answer;
}


