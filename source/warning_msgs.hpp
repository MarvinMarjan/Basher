#pragma once

#include <vector>
#include <string>
#include <map>

class WARN
{
public:
	void _file_already_exists(std::string file_name, std::map<std::string, std::string> clr);
	void _shortcut_already_exists(std::pair<std::string, std::string> shortcut, std::map<std::string, std::string> clr);
	void _system_depedency_file_not_found(std::string file_path, std::map<std::string, std::string> clr);
	void _command_disabled(std::string cmd_name, std::string reason, std::map<std::string, std::string> clr);
	void _not_empty_dir(std::string d_name, std::map<std::string, std::string> clr);
};