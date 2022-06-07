class PATH
{
public:
	// sets the initial path value
	PATH(std::string path);

	// returns the PATH::path
	std::string get_path();

	// assign a new path (string path) to PATH::path
	void set_path(std::string path);

private:
	std::string path;
};