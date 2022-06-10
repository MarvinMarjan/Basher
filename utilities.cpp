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