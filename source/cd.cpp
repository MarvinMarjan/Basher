// c++ modules
#include <dirent.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// program modules
#include "file.hpp"
#include "path.hpp"
#include "cd.hpp"

using namespace std;

CD::CD(string path)
{
	for (int i = 0; i < path.size(); i++)
		if (path[i] == '\\')
			path[i] = '/';
	
	this->path = path;
	this->max_args = 1;
}

CD::CD()
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
			path[i] = '/';

		this->max_args = 1;
	}
}

void CD::cd_dir(string path)
{
	this->path = this->format_path(this->path);
	
	if (PATH::is_absolute_path(path))
		this->path = this->format_path(path);

	else
		this->path += this->format_path(path);
}

void CD::cd_b_dir()
{
	if (this->path != "C:/")
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
}

void CD::cd_rt_dir()
{
	this->path = "C:/";
}

void CD::operator=(string path)
{

}

string CD::format_path(string path)
{
	if (this->path[this->path.size() - 1] == '/')
		return path;

	else 
		return path + "/";
}

int CD::get_max_args()
{
	return this->max_args;
}

/*
cout << "path: " << str.c_str() << endl;
	cout << "format: " << (PATH::is_absolute_path(path) ? path.c_str() : this->format_path(this->path) + path) << endl;*/

bool CD::path_exist(string path)
{
	string aux = ((PATH::is_absolute_path(path)) ? path : this->format_path(this->path) + path);

	DIR* dir = opendir(aux.c_str());

	if (!dir)
		return false;

	else
		return true; 
}

bool CD::file_exist(string path)
{
	fstream file;
	file.open(path, ios::in);

	if (file.fail())
		return false;

	else
		return true;
}

string CD::get_path()
{
	return this->path;
}