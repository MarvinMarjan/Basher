#pragma once

#include <vector>
#define SRC_PATH "Maiky\\maik.exe"

class MAIKY_SYSTEM
{
public:
	MAIKY_SYSTEM(std::string app_path);

	std::map<std::string, std::string> get_all_funcs();
	std::map<std::string, std::string>::iterator get_func_itr(std::string func_name);

	void add_func(std::pair<std::string, std::string> func);
	void rmv_func(std::string func_name);
	void run_func(std::string func_name, std::vector<std::string> args, std::map<std::string, std::string> clr);

	bool exist(std::string func_name);

	int get_ADD_MAX_ARGS();
	int get_RMV_MAX_ARGS();

	void update();

private:
	std::map<std::string, std::string> funcs;
	std::string app_path;

	int add_MAX_ARGS;
	int rmv_MAX_ARGS;
};