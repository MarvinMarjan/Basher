class FLAGS
{
public:
	FLAGS();

	std::vector<std::string> get_rf_commands(std::string path, int iterator);
	//std::vector<std::vector<std::string>> get_inline_commands(std::vector<std::string> program_args);
};