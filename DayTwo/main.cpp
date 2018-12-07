#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

string loadInputFromFile(ifstream &file)
{
	string output;
	string line;

	while (!file.eof())
	{
		getline(file, line);
		output += " " + line;
	}

	return output;
}

bool hasMatchingLetters(const int count, const string &word)
{
	map<char, int> charFrequency;

	for (char c : word)
	{
		if (charFrequency.count(c) != 0)
			++charFrequency[c];
		else
			charFrequency[c] = 1;
	}

	for (auto it = charFrequency.begin(); it != charFrequency.end(); ++it)
	{
		if (it->second == count)
			return true;
	}

	return false;
}

int exercise1(istringstream &iss)
{
	string word;

	int twoMatchingCount = 0;
	int threeMatchingCount = 0;

	while (!iss.eof())
	{
		iss >> word;

		if (hasMatchingLetters(2, word))
			twoMatchingCount++;

		if (hasMatchingLetters(3, word))
			threeMatchingCount++;
	}

	iss.seekg(0, ios::beg);

	return twoMatchingCount * threeMatchingCount;
}

int calculateDistance(const string &word1, const string &word2)
{
	// All words are confirmed to be the same length

	int distance = 0;
	for (unsigned int i = 0; i < word1.length(); ++i)
	{
		if (word1[i] != word2[i])
			++distance;
	}

	return distance;
}

string findCommonLetters(const string &word1, const string &word2)
{
	string commonLetters;

	for (unsigned int i = 0; i < word1.length(); ++i)
	{
		// Don't add the char that is different
		if (word1[i] != word2[i])
			continue;

		commonLetters += word1[i];
	}

	return commonLetters;
}

string exercise2(istringstream &iss)
{
	vector<string> words;

	string word;

	while (!iss.eof())
	{
		iss >> word;
		words.push_back(word);
	}

	for (unsigned int i = 0; i < words.size(); ++i)
	{
		// more efficient to start j at i+1 as we've already checked the all the ones behind j with j while it was i
		for (unsigned int j = i + 1; j < words.size(); ++j)
		{
			if (calculateDistance(words[i], words[j]) == 1)
			{
				return findCommonLetters(words[i], words[j]);
			}
		}
	}

	return "";
}

int main(int argc, char* argv[])
{
	cout << "Enter box id file: ";
	string filename;
	cin >> filename;

	ifstream file(filename);
	if (!file)
	{
		cerr << "Unable to open box id file: " << filename << endl;
		return 1;
	}

	istringstream iss(loadInputFromFile(file));

	cout << "Exercise 1 Answer: " << exercise1(iss) << endl;
	cout << "Exercise 2 Answer: " << exercise2(iss) << endl;

	return 0;
}