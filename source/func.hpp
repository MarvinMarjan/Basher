#pragma once

class FUNC
{
public:
	FUNC();

	void repeat(int count, std::vector<std::string> cmds, std::vector<std::string> flags);
	void run(std::vector<std::string> cmds, std::vector<std::string> flags);

	int get_REPEAT_max_args();

private:
	int repeat_max_args;
};