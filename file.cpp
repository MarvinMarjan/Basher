#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "file.hpp"
#include "cli.hpp"

using namespace std;

FILE_HAND::FILE_HAND()
{
	this->max_M_FILE_args = 1;
	this->max_RM_FILE_args = 1;
	this->max_READ_FILE_args = 1;
	this->max_WRITE_FILE_args = 2;
	this->max_COPY_FILE_args = 2;
}

void FILE_HAND::m_file(string path)
{
	fstream file;
	file.open(path, ios::out);
	
	file.close();
}

void FILE_HAND::rm_file(string path)
{
	remove(path.c_str());
}

vector<string> FILE_HAND::read_file(string path)
{
	vector<string> buffer;

	fstream file;
	file.open(path, ios::in);

	while (!file.eof())
	{
		string aux_buff;
		getline(file, aux_buff);

		buffer.push_back(aux_buff);
	}

	if (buffer.size() == 1 && buffer[0] == "")
		buffer.erase(buffer.begin());

	return buffer;
}

string FILE_HAND::read_file_line(string path, int line)
{
	string buffer;

	fstream file;
	file.open(path, ios::in);

	for (int i = 1; i <= line; i++)
		getline(file, buffer);
	
	return buffer;
}

int FILE_HAND::get_file_lines(string path)
{
	string buffer;
	int lines = 0;

	fstream file;
	file.open(path, ios::in);

	while (!file.eof())
	{
		lines++;
		getline(file, buffer);
	}

	return lines;
}

float FILE_HAND::get_file_size(string path)
{
	struct stat sb{};

	if (!stat(path.c_str(), &sb))
		return sb.st_size;

	else
		return -1.0;
}

void FILE_HAND::write_file(string path, string content, bool clear)
{
	vector<string> buffer = read_file(path);

	string str_buffer = "";

	if (!clear)
		for (int i = 0; i < buffer.size(); i++)
			str_buffer += buffer[i] + ((buffer.size() == 0) ? "" : "\n");
	
	ofstream file_write;
	file_write.open(path);

	file_write << str_buffer + content;

	file_write.close();
}

void FILE_HAND::copy_file(string file_path, string targ_path)
{
	vector<string> content = this->read_file(file_path);
	string str_content = "";

	for (string i : content)
		str_content += i + "\n";

	this->m_file(targ_path);

	this->write_file(targ_path, str_content, false);
}

int FILE_HAND::get_M_FILE_max_args()
{
	return this->max_M_FILE_args;
}

int FILE_HAND::get_RM_FILE_max_args()
{
	return this->max_RM_FILE_args;
}

int FILE_HAND::get_READ_FILE_max_args()
{
	return this->max_READ_FILE_args;
}

int FILE_HAND::get_WRITE_FILE_max_args()
{
	return this->max_WRITE_FILE_args;
}

int FILE_HAND::get_COPY_FILE_max_args()
{
	return this->max_COPY_FILE_args;
}