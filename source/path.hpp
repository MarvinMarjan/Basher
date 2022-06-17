#pragma once

class PATH
{
public:
	// sets the initial path value
	PATH(std::string path);

	std::string get_path(); // returns the PATH::path
	void set_path(std::string path); // assign a new path (string path) to PATH::path

	static bool is_absolute_path(std::string path);
	static bool is_same_path(std::string path);
	static std::string check(std::string path, std::string abs_path);

	static std::string remove_esc_chars(std::string path);

	void operator=(std::string path);

private:
	std::string path;
};