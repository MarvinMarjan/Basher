#include <string>
#include <vector>

#include "flags_arg.hpp"
#include "file.hpp"
#include "cli.hpp"
#include "utilities.hpp"

using namespace std;

FLAG_ARG::FLAG_ARG()
{

}

vector<string> FLAG_ARG::get_rf_commands(string path, int iterator)
{
	FILE_HAND file;

	return split_string(file.read_file_line(path, iterator));
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
			cmds.push_back(split_string(aux));
			aux = "";
		}
	}

	return cmds;
}