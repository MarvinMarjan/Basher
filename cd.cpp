#include <fstream>
#include <direct.h>
#include <string>
#include <iostream>
#include <cstring>

#include "./cd.hpp"

using namespace std;

CD::CD(string path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
		{
			path[i] = '/';
		}

		this->path = this->format_path(path);

		this->max_args = 1;
	}
}

void CD::cd_dir(string path)
{
	this->path = this->format_path(this->path);
	this->path += path;
}

void CD::cd_b_dir()
{
	for (int i = this->path.size() - 1; i >= 0; i--)
	{
		if (this->path[i] == '/')
		{
			this->path = this->path.substr(0, i);
			break;
		}
	}
}

void CD::cd_rt_dir()
{
	this->path = "C:/";
}

string CD::format_path(string path)
{
	if (this->path[this->path.size() - 1] == '/') { return path; }

	else { return path + "/"; }
}

int CD::get_max_args()
{
	return this->max_args;
}

bool CD::path_exist(string path)
{
	string aux_path = this->format_path(this->path) + path;

	int stat = _mkdir(aux_path.c_str());

	auto _trash = _rmdir(aux_path.c_str()); // delete the directory

	if (stat == 0) { return false; } // stat == 0 because the folder could be created, then it does not exist
	else if (stat == -1) { return true; } // stat == -1 because the folder couldn't be created, then it exist
}

string CD::get_path()
{
	return this->path;
}