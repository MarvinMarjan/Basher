#include "cd.hpp"

CD::CD(std::string path)
{
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
		{
			path[i] = '/';
		}

		this->path = path;
	}
}

void CD::cd_dir(std::string path)
{
	if (this->path[this->path.size() - 1] == '/')
	{
		this->path += path;
	}

	else
	{
		this->path += "/" + path;
	}
}

void CD::cd_b_dir()
{
	for (int i = this->path.size() - 1; i >= 0; i--)
	{
		if (this->path[i] == '/')
		{
			this->path = this->path.substr(0, i);
		}
	}
}

std::string CD::get_path()
{
	return this->path;
}