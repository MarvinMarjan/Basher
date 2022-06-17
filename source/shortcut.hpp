class SHORTCUT
{
public:
	SHORTCUT();

	void add_shortcut(std::pair<std::string, std::string> shortcut);
	void rmv_shortcut(std::string shortcut_name);
	void edit_shortcut(std::string shortcut_name, std::string new_values);

	void update(std::string mode);

	std::map<std::string, std::string> get_shortcuts();

	bool exist(std::string key);

	int get_max_ADD_args();
	int get_max_RMV_args();
	int get_max_EDIT_args();
	int get_max_LIST_args();

private:
	std::map<std::string, std::string> shortcuts;

	int max_ADD_args;
	int max_RMV_args;
	int max_EDIT_args;
	int max_LIST_args;
};