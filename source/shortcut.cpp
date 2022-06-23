#include <iostream>
#include <string>
#include <vector>
#include <map>

//#include "libs/rapidjson/include/rapidjson/document.h"
#include "warning_msgs.hpp"
#include "utilities.hpp"
#include "shortcut.hpp"
#include "data.hpp"
#include "file.hpp"
#include "cd.hpp"

using namespace std;

SHORTCUT::SHORTCUT(const string app_path, map<string, string> clr)
{
	WARN warn;
	CD cd;

	this->max_ADD_args = 3;
	this->max_EDIT_args = 3;
	this->max_LIST_args = 1;
	this->max_RMV_args = 2;

	this->app_path = (app_path != "") ? app_path + "/" : "";

	if (!cd.file_exist(this->app_path + "_system/shortcuts.txt"))
	{
		this->can_run = false;

		warn._system_depedency_file_not_found("_system/shortcuts.txt", clr);
	}

	else
		this->can_run = true;
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
	DATA data(this->app_path);
	UTILS utils;
	FILE_HAND file;

	if (mode == "read")
		for (auto itr : data.get_data(this->app_path + "_system/shortcuts.txt"))
			this->add_shortcut({
				itr.first,
				itr.second
				});

	else if (mode == "write")
		data.set_data(this->app_path + "_system/shortcuts.txt", this->shortcuts);
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