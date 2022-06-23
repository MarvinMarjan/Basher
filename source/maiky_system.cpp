#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "maiky_system.hpp"
#include "utilities.hpp"
#include "data.hpp"
#include "file.hpp"

using namespace std;

MAIKY_SYSTEM::~MAIKY_SYSTEM()
{
	DATA data(this->app_path);

	data.set_data(this->app_path + "_system/maiky_funcs.txt", this->funcs);
}

MAIKY_SYSTEM::MAIKY_SYSTEM(string app_path)
{
	this->app_path = (app_path != "") ? app_path + "/" : "";

	this->add_MAX_ARGS = 3;
	this->rmv_MAX_ARGS = 2;

	FILE_HAND file;
	UTILS utils;
	DATA data(this->app_path);

	for (auto itr : data.get_data(this->app_path + "_system/maiky_funcs.txt"))
		this->add_func({
			itr.first,
			itr.second
		});
}

map<string, string>::iterator MAIKY_SYSTEM::get_func_itr(string func_name)
{
	return this->funcs.find(func_name);
}

void MAIKY_SYSTEM::add_func(pair<string, string> func)
{
	this->funcs.insert(func);
}

void MAIKY_SYSTEM::rmv_func(string func_name)
{
	this->funcs.erase(func_name);
}

void MAIKY_SYSTEM::run_func(string func_name, vector<string> args)
{
	UTILS utils;

	map<string, string>::iterator itr = this->get_func_itr(func_name);

	string path = SRC_PATH;

	path += " " + itr->second + " " + utils.concat_string(args);

	system(path.c_str());
}

bool MAIKY_SYSTEM::exist(string func_name)
{
	for (auto itr : this->funcs)
		if (func_name == itr.first)
			return true;

	return false;
}

int MAIKY_SYSTEM::get_ADD_MAX_ARGS()
{
	return this->add_MAX_ARGS;
}

int MAIKY_SYSTEM::get_RMV_MAX_ARGS()
{
	return this->rmv_MAX_ARGS;
}