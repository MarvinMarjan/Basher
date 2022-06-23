#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "flags_arg.hpp"
#include "utilities.hpp"
#include "file.hpp"
#include "cli.hpp"

using namespace std;

FLAG_ARG::FLAG_ARG()
{

}

vector<string> FLAG_ARG::get_rf_commands(string path, int iterator, map<string, string> clr)
{
	UTILS utils;
	FILE_HAND file;

	return utils.split_string(file.read_file_line(path, iterator, clr));
}

vector<vector<string>> FLAG_ARG::get_inline_commands(vector<string> program_args)
{
	vector<vector<string>> cmds;
	UTILS utils;

	string aux = "";

	int index = utils.find_item(program_args, "-c") + 1; // commands index

	for (int i = 0; i < program_args[index].size(); i++)
	{
		char ch = program_args[index][i];

		if (ch != ';')
			aux += ch;

		if (ch == ';' || i + 1 >= program_args[index].size())
		{
			cmds.push_back(utils.split_string(aux));
			aux = "";
		}
	}

	return cmds;
}