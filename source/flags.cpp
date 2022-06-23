#include <string>
#include <vector>
#include <map>

#include "flags_arg.hpp"
#include "flags.hpp"

using namespace std;

FLAGS::READ_FILE_FLAG::READ_FILE_FLAG(bool active, int iterator, int rf_index)
{
	if (active)
	{
		this->iterator = iterator;
		this->rf_index = rf_index;
	}
}

FLAGS::INLINE_COMMAND_FLAG::INLINE_COMMAND_FLAG(bool active, vector<string> program_args, int current)
{
	FLAG_ARG flag_arg;

	if (active)
	{
		this->cmds = flag_arg.get_inline_commands(program_args);
		this->count = this->cmds.size();
		this->current = current;
	}
}