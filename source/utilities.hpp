#pragma once

class UTILS
{
public:
	int find_item(std::vector<std::string> target_array, std::string target_string);

	std::vector<std::string> split_string(std::string str);

	std::string to_lower_case(std::string source);
	std::string concat_string(std::vector<std::string> source);
	
	std::string remove_last_char(std::string source);
};