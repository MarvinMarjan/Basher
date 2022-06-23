#pragma once

#include <vector>
#include <string>
#include <map>

// returns the full line
std::vector<std::string> get_command();

// returns all arguments of a command
std::vector<std::string> get_args(std::vector<std::string> cmd, std::map<std::string, std::string> shortcut);

std::vector<std::string> get_program_args(char* argv[], int argc);
std::vector<std::string> get_program_flags(char* argv[], int argc);
std::vector<std::string> get_cmd_flags(std::vector<std::string> cmd);
std::map<std::string, bool> set_cmd_modes(std::vector<std::string> args);