#include "queryManager.h"
#include <iostream>
#include <fstream>


queryManager::queryManager(void)
{
}

queryManager::~queryManager(void)
{
}

void queryManager::addBigam(vector<string> referenceText, std::string languageName)
{
	Bigram m(languageName);
	m.buildLanguageMap(referenceText);

	bigramList.push_back(m);
}

void queryManager::query(string referenceText)
{
	vector<string> strings;

	const char* ptr = referenceText.c_str();
	string str;

	for (unsigned int i = 0; i < referenceText.size(); ++i)
	{
		//Query tokenization.
		if (ptr[i] != ' ' && ptr[i] != '?' && ptr[i] != ','&& ptr[i] != '!' && ptr[i] != '-' && ptr[i] != '.')
		{
			str += ptr[i];
		}
		else
		{
			if (str.size() > 0)
			{
				strings.push_back(str);
				str = "";
			}
		}
	}

	if (str.size() > 0)
	{
		strings.push_back(str);
	}

	query(strings);
}

void queryManager::query(vector<string> referenceText)
{
	ofstream out ("queryresult.txt");

	unsigned int longestLangName = 0;
	std::vector<double> matchResult; //One for each language.
	for (unsigned  int i = 0; i < bigramList.size(); ++i)
	{
		matchResult.push_back(0);

		if (bigramList[i].getName().size() > longestLangName)
		{
			longestLangName = bigramList[i].getName().size();
		}
	}

	for (unsigned int rtCount  = 0 ; rtCount < referenceText.size(); ++rtCount)
	{
		for (unsigned int i = 0; i < referenceText[rtCount].size() - 1; ++ i)
		{
			string bigram = referenceText[rtCount].substr(i, 2);

			cout << bigram << endl;

			for (unsigned int i = 0; i < bigramList.size(); ++i)
			{
				double matchValue = bigramList[i].match(bigram);
				matchResult[i] = matchResult[i] + matchValue; 

				string outputName =  bigramList[i].getName();
				for (unsigned int nameSize = outputName.size(); nameSize < longestLangName; ++nameSize)
				{
					outputName += " ";
				}

				std::cout << "Language " << outputName << " - checking bigram '" << bigram << "' value " << ((double)matchValue) << "\n";
				out << "Language " << outputName << " - checking bigram '" << bigram << "' value " << ((double)matchValue) << "\n";

			}
			out << " \n";
		}
	}

	int highestScore = 0;

	for (unsigned int i = 1; i < bigramList.size(); ++i)
	{
		if (matchResult[i] > matchResult[highestScore])
		{
			highestScore = i;
		}
	}

	std::cout << "\nMost probable language is " << bigramList[highestScore].getName() << "\n";
	out  << "\nMost probable language is " << bigramList[highestScore].getName() << "\n";
	out.close();
}