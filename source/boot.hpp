#pragma once

class BOOT
{
public:
	std::map<std::string, bool> set_program_modes(std::vector<std::string> flags);
	std::string check_app_path();
};