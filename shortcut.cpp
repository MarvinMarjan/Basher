#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "shortcut.hpp"
#include "file.hpp"
#include "utilities.hpp"

using namespace std;

SHORTCUT::SHORTCUT()
{
	this->max_ADD_args = 3;
	this->max_EDIT_args = 3;
	this->max_LIST_args = 1;
	this->max_RMV_args = 2;
}

bool SHORTCUT::exist(string key)
{
	if (this->shortcuts.find(key) == this->shortcuts.end())
		return false;

	else
		return true;
}

void SHORTCUT::add_shortcut(pair<string, string> shortcut)
{
	this->shortcuts.insert(shortcut);
}

void SHORTCUT::rmv_shortcut(string shortcut_name)
{
	this->shortcuts.erase(shortcut_name);
}

void SHORTCUT::edit_shortcut(string shortcut_name, string new_value)
{
	this->shortcuts[shortcut_name] = new_value;
}

void SHORTCUT::update(string mode)
{
	UTILS utils;
	FILE_HAND file;

	if (mode == "read")
	{
		vector<string> content = file.read_file("_system/shortcuts.txt");

		for (string i : content)
		{
			// ["name", "desktop", "path", "C:/Users/Usuario/Desktop"] 
			vector<string> split = utils.split_string(i);
			vector<string> data;

			for (int o = 0; o < split.size(); o++)
			{
				if (split[o] == "__name__:")
				{
					o++;

					data.push_back(split[o]);
				}

				else if (split[o] == "__path__:")
				{
					o++;

					vector<string> aux;

					for (int p = o; p < split.size(); p++)
						aux.push_back(split[p]);

					data.push_back(utils.concat_string(aux));
				}
			}

			this->add_shortcut({
				data[0],
				data[1]
			});
		}
	}

	else if (mode == "write")
	{
		file.write_file("_system/shortcuts.txt", "", true);
		
		for (auto i : this->shortcuts)
		{
			string buff = "__name__: " + i.first + " __path__: " + i.second;
			cout << "called.." << endl;

			file.write_file("_system/shortcuts.txt", buff, false);
		}
	}
}

map<string, string> SHORTCUT::get_shortcuts()
{
	return this->shortcuts;
}

int SHORTCUT::get_max_ADD_args()
{
	return this->max_ADD_args;
}

int SHORTCUT::get_max_RMV_args()
{
	return this->max_RMV_args;
}

int SHORTCUT::get_max_EDIT_args()
{
	return this->max_EDIT_args;
}

int SHORTCUT::get_max_LIST_args()
{
	return this->max_LIST_args;
}