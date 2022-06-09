// c++ modules
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

bool PATH::is_absoulute_path(string path)
{
	CD cd;
	string aux = "";

	for (char ch : path)
	{
		aux += ch;

		if (aux == "C:/" || aux == "D:/")
		{
			if (cd.path_exist(path))
				return true;
		}
	}

	return false;
}

void PATH::operator=(string path)
{
	this->set_path(path);
}