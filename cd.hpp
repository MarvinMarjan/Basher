class CD
{
public:
	// CD constructor
	CD(std::string path);

	// enter a directory
	void cd_dir(std::string);

	// back a directory
	void cd_b_dir();

	// goes to root directory: "C:/"
	void cd_rt_dir();

	// returns a formated path
	std::string format_path(std::string path);

	// returns this->max_args
	int get_max_args();

	// returns true if path exists
	bool path_exist(std::string path);

	// return this->path
	std::string get_path();

private:
	int max_args;
	std::string path;
};