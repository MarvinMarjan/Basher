#pragma once

#include <string>
#include <map>

class DATA
{
public:
	DATA(std::string app_path);

	std::map<std::string, std::string> get_data(std::string source);
	void set_data(std::string source, std::map<std::string, std::string> data);

private:
	std::string app_path;


};