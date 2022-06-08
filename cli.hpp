// splits a string each space " "
std::vector<std::string> split_string(std::string str);

// returns the full line
std::vector<std::string> get_command();

// returns all arguments of a command
std::vector<std::string> get_args(std::vector<std::string> cmd);