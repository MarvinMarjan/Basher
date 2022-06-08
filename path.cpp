// c++ modules
#include <string>

// program modules
#include "path.hpp"

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

void PATH::operator=(string path)
{
	this->set_path(path);
}