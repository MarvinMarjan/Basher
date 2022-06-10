#include <string>
#include <vector>

#include "flags.hpp"
#include "file.hpp"
#include "cli.hpp"

using namespace std;

FLAGS::FLAGS()
{

}

vector<string> FLAGS::get_rf_commands(string path, int iterator)
{
	FILE_HAND file;

	return split_string(file.read_file_line(path, iterator));
}

/*vector<vector<string>> FLAGS::get_inline_commands(vector<string> program_args)
{
	// stoped here =--------
}*/