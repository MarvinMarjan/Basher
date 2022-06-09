class PATH
{
public:
	// sets the initial path value
	PATH(std::string path);

	std::string get_path(); // returns the PATH::path
	void set_path(std::string path); // assign a new path (string path) to PATH::path

	static bool is_absoulute_path(std::string path);

	void operator=(std::string path);

private:
	std::string path;
};