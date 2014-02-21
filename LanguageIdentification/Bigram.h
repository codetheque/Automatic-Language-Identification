#ifndef BIGRAM_H
#define BIGRAM_H

#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

class Bigram
{
public:

	Bigram(string name) :myName(name) {}
	~Bigram(void){}

	vector<string> tableOfBigrams();
	void buildLanguageMap(const vector<string>& vec);
	double match(string bigam);
	string getName() ;	

private:

	map<string,double> tokens;
	map<string,double> probablilityTable;
	//number of bigrams in the training corpus
	int n;
	string myName;

};
#endif