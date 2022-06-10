#define CACHE_PATH "./__bsh_cache__.txt"

#include <string>
#include <vector>

#include "func.hpp"
#include "file.hpp"

using namespace std;

FUNC::FUNC()
{
	this->repeat_max_args = 1;
}

void FUNC::repeat(int count, vector<string> cmds)
{
	for (int i = 0; i < count; i++)
		this->run(cmds);
}

void FUNC::run(vector<string> cmds)
{
	FILE_HAND file;

	file.m_file(CACHE_PATH);

	for (string i : cmds)
		file.write_file(CACHE_PATH, i);

	string aux = "a -rf " + (string)CACHE_PATH;

	system(aux.c_str());

	file.rm_file(CACHE_PATH);
}

int FUNC::get_REPEAT_max_args()
{
	return this->repeat_max_args;
}