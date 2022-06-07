class DIRS
{
public:
	// DIRS constructor
	DIRS();

	// returns a vector containing all bufs
	std::vector<std::vector<std::string>> get_dir_list(std::string path);

	// returns the buf type (FILE | DIRS)
	std::string get_buf_type(std::string path);

	// creates a directory
	void m_dir(std::string d_name);
	
	// return max_args
	int get_max_args();
	int get_max_M_DIR_args();

private:
	int max_args;
	int max_M_DIR_args;
};