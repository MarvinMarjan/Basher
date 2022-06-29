// c++ modules
#include <iostream>
#include <string>

// program modules
#include "path.hpp"
#include "cd.hpp"

using namespace std;

PATH::PATH(string path)
{
	this->path = path;
}

string PATH::get_path()
{
	return this->path;
}

void PATH::set_path(string path)
{
	this->path = path;
}

bool PATH::is_absolute_path(string path)
{
	CD cd;
	string aux = "";

	for (char ch : path)
	{
		aux += ch;

		if (aux == "C:/" || aux == "D:/")	
			return true;
	}

	return false;
}

bool PATH::is_same_path(string path)
{
	bool same = false;

	for (int i = 0; i < path.size(); i++)
	{
		if (i + 1 < path.size())
		{
			if (path[i] == '/' || path[i] == '\\' || path[i] == '.')
				same = true;

			else
				same = false;
		}
	}

	return same;
}

string PATH::check(string path, string abs_path)
{
	CD cd;

	if (is_absolute_path(path))
		return path;

	else
		return cd.format_path(abs_path) + remove_esc_chars(path);
}

string PATH::remove_esc_chars(string path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '/' || path[i] == '\\' || path[i] == '.')
		{
			path.erase(i, 1);
			i--;
		}

		else if (i == 0)
			break;
	}

	return path;
}

void PATH::operator=(string path)
{
	this->set_path(path);
}