/* -------------------------------------------------------------------------------------------------
*
*   Concordia University
*	Aline Czarnobai 
*
*   Language Modeling for Automatic Language Identification
*	Introduction to AI - November 2012.
*---------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Bigram.h"
#include "queryManager.h"

using namespace std;


ifstream& readWords(ifstream& in, vector<string>& wd)
{
	string word;
	char c;

	bool ignore = false;
	while (in.get(c))
	{ 		 
		if (c < 0) //Ignore unicode 16.
			continue;

		if (isdigit(c) || isalpha(c))
		{ 	
			if (ignore)
				continue;

			//Converts uppercase to lowercase.
			c = tolower(c);
			word += c;
		}
		if (c == '<') 
			ignore = true;
		if (c == '>')
			ignore = false;

		if (isspace(c) || c == ';' || c == ',' || c == '.' || c == ':' || c == '...' || c == '?' || c == '!' || c == '-' || c == '&' )
		{
			wd.push_back(word);
			word.clear();
		}		
	}

	if (word.size() > 0)
	{
		wd.push_back(word);
	}

	return in;
}

void display(const vector<string>& v)
{
	cout << v.size() << " elements\n ";
	for (vector<string>::const_iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << ' ';
	cout << endl;
}

void display(const map<string, double>& v)
{
	cout << v.size() << " elements\n ";

	for (map<string, double>::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << it->first << " : "  << it->second <<endl ;
	}
}

int main()
{

	//cout <<"Please insert a file name: ";
	//cin >> filename;

	cout << "\nCharacter-Based Language Model for English, French and Portuguese.\n ";

	queryManager query;

	std::vector<string> langs;
	langs.push_back("french.txt");
	langs.push_back("english.txt");
	langs.push_back("portuguese.txt");


	for (unsigned int i = 0 ; i < langs.size(); ++i)
	{
		ifstream ifs;
		ifs.open(langs[i].c_str());
		string word;
		if (!ifs)
		{
			ifs.close();
			cout << " Failed to open " << endl;
			return 1;
		}

		vector<string> vecWords;
		readWords(ifs, vecWords);

		query.addBigam(vecWords, langs[i].substr(0, langs[i].size() - 4));
		ifs.close();	
	}


	//Please type your sentence here.
	query.query("Ils reviendront au final, peut-etre.");

	cout << "\nQuery result has been saved in a output file." <<endl;

	getchar();
	getchar();
	return 0;
}