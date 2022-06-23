#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utilities.hpp"
#include "data.hpp"
#include "file.hpp"

using namespace std;

DATA::DATA(string app_path)
{
	this->app_path = (app_path != "" && app_path[app_path.size() - 1] != '/') ? app_path + "/" : app_path;
}

map<string, string> DATA::get_data(string source)
{
	FILE_HAND file;
	UTILS utils;

	vector<string> content = file.read_file(source);

	map<string, string> data;
	vector<string> vec_data;

	for (string i : content)
	{
		// ["name", "desktop", "path", "C:/Users/Usuario/Desktop"] 
		vector<string> split = utils.split_string(i);

		for (int o = 0; o < split.size(); o++)
		{
			if (split[o] == "__name__:")
			{
				o++;

				vec_data.push_back(split[o]);
			}

			else if (split[o] == "__path__:")
			{
				o++;

				vector<string> aux;

				for (int p = o; p < split.size(); p++)
					aux.push_back(split[p]);

				vec_data.push_back(utils.concat_string(aux));
			}
		}
	}

	for (int i = 0; i < vec_data.size(); i++)
	{
		data.insert({ vec_data[i], vec_data[i + 1] });
		i++;
	}

	return data;
}

void DATA::set_data(string source, map<string, string> data)
{
	FILE_HAND file;

	file.write_file(source, "", true);

	for (auto itr : data)
		file.write_file(source, "__name__: " + itr.first + " __path__: " + itr.second, false);
}