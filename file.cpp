#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "file.hpp"
#include "cli.hpp"

using namespace std;

FILE_HAND::FILE_HAND()
{
	this->max_M_FILE_args = 1;
	this->max_RM_FILE_args = 1;
	this->max_READ_FILE_args = 1;
	this->max_WRITE_FILE_args = 2;
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

void FILE_HAND::write_file(string path, string content)
{
	vector<string> buffer = read_file(path);

	string str_buffer = "";

	for (int i = 0; i < buffer.size(); i++)
		str_buffer += buffer[i] + ((buffer.size() == 0) ? "" : "\n");
	
	ofstream file_write;
	file_write.open(path);

	file_write << str_buffer + content;

	file_write.close();
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