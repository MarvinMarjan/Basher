class EXCP
{
public:
	void _isfct_args(int args_c, std::string targ_args, std::map<std::string, std::string> clr);
	void _cmd_not_found(std::string cmd, std::map<std::string, std::string> clr);
	void _max_args_overload(std::string cmd, int args_c, std::string targ_args, std::map<std::string, std::string> clr);
	void _path_not_found(std::string path, std::map<std::string, std::string> clr);
};