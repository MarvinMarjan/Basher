class CD
{
public:
	CD(std::string path);

	void cd_dir(std::string);
	void cd_b_dir();
	void cd_rt_dir();

	int get_max_args();

	bool path_exist(std::string path);

	std::string get_path();

private:
	int max_args;
	std::string path;
};