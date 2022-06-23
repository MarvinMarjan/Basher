#include <stdio.h>
#include <string>
#include <vector>

#include "utilities.hpp"

using namespace std;

int UTILS::find_item(vector<string> target_array, string target_string)
{
	for (int i = 0; i < target_array.size(); i++)
		if (target_array[i] == target_string)
			return i;
}

vector<string> UTILS::split_string(string str)
{
	vector<string> split_str;
	string aux_str = "";

	for (int i = 0; i < str.size(); i++)
	{
		aux_str = "";

		while (str[i] != ' ')
		{
			aux_str += str[i];
			i++;

			if (i >= str.size())
				break;
		}

		split_str.push_back(aux_str);
	}

	if (split_str.size() < 1)
		split_str.push_back("__NULL__");

	return split_str;
}

string UTILS::to_lower_case(string source)
{
	string lowc_str = "";

	for (char ch : source)
		lowc_str += tolower(ch);

	return lowc_str;
}

string UTILS::concat_string(vector<string> source)
{
	string full_str = "";
		
	for (int o = 0; o < source.size(); o++)
		full_str += source[o] + ((o + 1 == source.size()) ? "" : " ");
	
	return full_str;
}

string UTILS::remove_last_char(string source)
{
	source.erase(source.size() - 1);

	return source;
}