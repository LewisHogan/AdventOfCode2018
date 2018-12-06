#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <set>

using namespace std;

bool isInteger(const string &text)
{
	for (unsigned int i = 0; i < text.length(); i++)
	{
		if (i == 0 && text[i] == '-') continue;

		if (!isdigit(text[i])) false;
	}

	return true;
}

string filterString(const string &str)
{
	string result;
	for (const char &c : str)
	{
		if (isalnum(c) || c == '-' || c == ' ')
			result += c;
	}

	return result;
}

string loadInputFromFile(ifstream &file)
{
	string output;
	string line;

	while (!file.eof())
	{
		getline(file, line);
		output += " " + filterString(line);
	}

	return output;
}

int exercise1(istringstream &iss)
{
	int frequency = 0;
	string data;
	while (!iss.eof())
	{
		iss >> data;
		if (isInteger(data))
		{
			int value = stoi(data);

			frequency += value;
		}
		else
		{
			cerr << "Invalid integer in file!" << endl;
		}
	}

	iss.seekg(0, ios::beg);

	return frequency;
}

int exercise2(istringstream &iss)
{
	set<int> foundFrequencies;
	int frequency = 0;
	string data;

	// All input files are guaranteed to overlap eventually.
	while (true)
	{
		while (!iss.eof())
		{
			iss >> data;
			if (isInteger(data))
			{
				int value = stoi(data);

				frequency += value;

				if (foundFrequencies.count(frequency) != 0)
					return frequency;

				foundFrequencies.insert(frequency);
			}
			else
			{
				cerr << "Invalid integer in file!" << endl;
			}
		}

		iss.seekg(0, ios::beg);
	}
}

int main(int argc, char* argv[])
{
	string inputFileName;

	cout << "Enter situation data file: ";
	cin >> inputFileName;

	ifstream inputFile(inputFileName);

	if (!inputFile)
	{
		cerr << "Unable to open situation data file: " << inputFileName << endl;
		return 1;
	}

	string input = loadInputFromFile(inputFile);

	inputFile.close();

	istringstream iss(input);

	cout << "Exercise 1 Answer: " << exercise1(iss) << endl;
	cout << "Exercise 2 Answer: " << exercise2(iss) << endl;
	return 0;
}