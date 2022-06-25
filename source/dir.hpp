#pragma once

#include <vector>
#include <string>
#include <map>

class DIRS
{
public:
	// DIRS constructor
	DIRS();

	// returns a vector containing all bufs
	std::vector<std::vector<std::string>> get_dir_list(std::string path, bool get_size = false, bool save_path = false, bool debug_path = false, std::map<std::string, std::string> clr = {});

	// returns the buf type (FILE | DIRS)
	std::string get_buf_type(std::string path);

	float get_dir_size(std::string path, bool debug_path, std::map<std::string, std::string> clr);

	// creates a directory
	void m_dir(std::string d_name);

	//removes a directory
	void rm_dir(std::string d_name);
	void rm_all_dir(std::string d_name, bool debug_path = false, std::map<std::string, std::string> clr = {});

	void copy_dir(std::string d_name, std::string targ_path, bool debug_path, std::map<std::string, std::string> clr);
	
	// return max_args
	int get_max_args();

	int get_max_M_DIR_args();
	int get_max_RM_DIR_args();

private:
	int max_args;

	int max_M_DIR_args;
	int max_RM_DIR_args;
};