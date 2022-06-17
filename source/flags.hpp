#pragma once

namespace FLAGS
{
	class READ_FILE_FLAG
	{
	public:
		READ_FILE_FLAG(bool active, int iterator, int rf_index);

		int iterator;
		int rf_index;
	};

	class INLINE_COMMAND_FLAG
	{
	public:
		INLINE_COMMAND_FLAG(bool active, std::vector<std::string> program_args, int current);

		int count;
		int current;

		std::vector<std::vector<std::string>> cmds;
	};
}