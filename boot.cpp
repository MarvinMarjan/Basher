#include <string>
#include <vector>

#include "file.hpp"
#include "boot.hpp"
#include "cli.hpp"

using namespace std;

bool BOOT::is_rf_mode(vector<string> program_args)
{
	if (program_args.size() > 1 && program_args[1] == "-rf") // read file mode
		return true;

	else
		return false;
}