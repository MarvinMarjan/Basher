class FILE_HAND
{
public:
	FILE_HAND();

	// creates a file
	void m_file(std::string path); 

	// removes a file
	void rm_file(std::string path); 
	
	// reads a file and return it's content
	std::vector<std::string> read_file(std::string path); 

	// writes text in a file
	void write_file(std::string path, std::string content); 

	// return the max args of m_file
	int get_M_FILE_max_args();

	// return the max args of rm_file
	int get_RM_FILE_max_args();

	// return the max args of read_file
	int get_READ_FILE_max_args();

	// return the max args of write_file
	int get_WRITE_FILE_max_args();

	

private:
	int max_M_FILE_args;
	int max_RM_FILE_args;
	int max_READ_FILE_args;
	int max_WRITE_FILE_args;
};