#pragma once

class WARN
{
public:
	void _file_already_exists(std::string file_name, std::map<std::string, std::string> clr);
	void _shortcut_already_exists(std::pair<std::string, std::string> shortcut, std::map<std::string, std::string> clr);
};