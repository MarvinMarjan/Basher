#define CACHE_PATH "./__bsh_cache__.txt"

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "func.hpp"
#include "file.hpp"

using namespace std;

FUNC::FUNC()
{
	this->repeat_max_args = 1;
}

void FUNC::repeat(int count, vector<string> cmds, vector<string> flags)
{
	for (int i = 0; i < count; i++)
		this->run(cmds, flags);
}

void FUNC::run(vector<string> cmds, vector<string> flags)
{
	string aux = "\"";

	for (string i : cmds)
		aux += i + ";";

	aux += "\"";

	string buf = "a ";

	for (string i : flags)
		buf += (i == "-c") ? "" : i + " ";

	buf += "-c " + aux;

	system(buf.c_str());
}

int FUNC::get_REPEAT_max_args()
{
	return this->repeat_max_args;
}