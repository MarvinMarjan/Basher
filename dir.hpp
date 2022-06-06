class DIRS
{
public:
	DIRS();

	std::vector<std::vector<std::string>> get_dir_list(std::string path);
	std::string get_buf_type(std::string path);
	
	int get_max_args();

private:
	int max_args;
};