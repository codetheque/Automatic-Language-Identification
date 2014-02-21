#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <vector>
#include "Bigram.h"
#include <string>

using namespace std;

class queryManager
{
public:
	queryManager(void);
	~queryManager(void);

	void addBigam(vector<string> referenceText, std::string languageName);

	void query(vector<string> referenceText);

	void query(string referenceText);

private:
	std::vector<Bigram> bigramList;

};
#endif