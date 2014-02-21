#include "Bigram.h"


/*
	Language model training.
*/
vector<string> Bigram::tableOfBigrams()
{
	vector<string> bigram;
	char first = 'a';
	char end = 'z' + 1;

	do
	{
		char second = 'a';

		do
		{
			string key = "";
			key = key + first + second;
			bigram.push_back(key);
			second++;

		} while (second != end);

		first++;
	}
	while (first != end);

	return bigram;

}

void Bigram::buildLanguageMap(const vector<string>& vec)
{
	for (vector<string>::const_iterator it = vec.begin() ; it < vec.end(); ++it)
	{
		string word = *it;
		if (word.size() == 0)
		{
			continue;
		}

		for (string::size_type i = 0; i != word.size() - 1; ++i)
		{
			string bigram = it->substr(i, 2);
			tokens[bigram]++;
		}
	}

	vector<string> bigram = tableOfBigrams();
	//Number of bigrams in the training corpus.
	n = tokens.size();

	double smoothingfactor = 0.5;
	int b = 26*26;
	double freq_bigram = 0;

	for (string::size_type i = 0; i < bigram.size(); ++i)
	{
		map<string, double>::iterator found = tokens.find(bigram[i]);

		if (found != tokens.end())
		{
			freq_bigram = found->second;
		}
		else //Not in the training corpus.
		{
			double freq_bigram = 0;
		}
		pair<string, double> freq;
		freq.first = bigram[i];
		freq.second = log10((freq_bigram + smoothingfactor)/ (n + smoothingfactor*b));
		probablilityTable.insert(freq);
	}
}

double Bigram::match(string bigam)
{
	map<string,double>::iterator found = probablilityTable.find(bigam);

	double freq;

	if (found != probablilityTable.end())
	{
		freq = found->second;
	}
	else//Not in the training corpus.
	{
		freq = log10((0 + 0.5)/ (n + 0.5*26*26));

	}
	return freq;
}

string Bigram::getName() { return myName; }