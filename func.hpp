class FUNC
{
public:
	FUNC();

	void repeat(int count, std::vector<std::string> cmds);
	void run(std::vector<std::string> cmds);

	int get_REPEAT_max_args();

private:
	int repeat_max_args;
};