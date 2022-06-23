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
	std::vector<std::vector<std::string>> get_dir_list(std::string path, bool get_size, bool debug_path, std::map<std::string, std::string> clr);

	// returns the buf type (FILE | DIRS)
	std::string get_buf_type(std::string path);

	float get_dir_size(std::string path, bool debug_path, std::map<std::string, std::string> clr);

	// creates a directory
	void m_dir(std::string d_name);

	//removes a directory
	void rm_dir(std::string d_name);
	
	// return max_args
	int get_max_args();

	int get_max_M_DIR_args();
	int get_max_RM_DIR_args();

private:
	int max_args;

	int max_M_DIR_args;
	int max_RM_DIR_args;
};