#include <string>

class CD
{
public:
	CD(std::string path);

	void cd_dir(std::string);
	void cd_b_dir();

	std::string get_path();

private:
	std::string path;
};