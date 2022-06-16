#pragma once

class EXCP
{
public:
	void _isfct_args(int args_c, std::string targ_args, std::map<std::string, std::string> clr);
	void _max_args_overload(std::string cmd, int args_c, std::string targ_args, std::map<std::string, std::string> clr);

	void _cmd_not_found(std::string cmd, std::map<std::string, std::string> clr);
	void _path_not_found(std::string path, std::map<std::string, std::string> clr);
	void _file_not_found(std::string file_name, std::map<std::string, std::string> clr);
	void _shortcut_not_found(std::string shortcut_name, std::map<std::string, std::string> clr);
	
	void _incompatible_flags(std::vector<std::string> imcomp_flags, std::map<std::string, std::string> clr);
	
	void _dir_already_exists(std::string dir_name, std::map<std::string, std::string> clr);
	
};