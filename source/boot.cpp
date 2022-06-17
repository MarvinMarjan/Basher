#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <iostream>

#include "file.hpp"
#include "boot.hpp"
#include "cli.hpp"

using namespace std;

map<string, bool> BOOT::set_program_modes(vector<string> flags)
{
	map<string, bool> modes = {
		{"read_file_mode", false},
		{"no_clr_mode", false},
		{"inline_cmd_mode", false},
		{"stay_mode", false}
	};

	for (int i = 0; i < flags.size(); i++)
	{
		if (flags[i] == "-rf")
			modes["read_file_mode"] = true;

		else if (flags[i] == "-dc")
			modes["no_clr_mode"] = true;

		else if (flags[i] == "-c")
			modes["inline_cmd_mode"] = true;

		else if (flags[i] == "-s")
			modes["stay_mode"] = true;
	}

	return modes;
}

string BOOT::check_app_path()
{
	if (getenv("BSH_APP_LOCAL"))
		return getenv("BSH_APP_LOCAL");

	else
		return "NULL";
}