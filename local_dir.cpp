#include <iostream>
#include <direct.h>

#include "local_dir.hpp"

std::string get_local_dir()
{
	char buf[1024];

	return _getcwd(buf, 1024);
}