#pragma once

#include <vector>
#include <string>
#include <map>

class FLAG_ARG
{
public:
	FLAG_ARG();

	std::vector<std::string> get_rf_commands(std::string path, int iterator, std::map<std::string, std::string> clr);
	std::vector<std::vector<std::string>> get_inline_commands(std::vector<std::string> program_args);
};