// c++ modules
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <map>
#include <fstream>
#include <direct.h>

// program modules
#include "path.hpp"
#include "file.hpp"
#include "cd.hpp"
#include "dir.hpp"

using namespace std;

DIRS::DIRS()
{
    this->max_args = 2;
    this->max_M_DIR_args = 1;
    this->max_RM_DIR_args = 1;
}

vector<vector<string>> DIRS::get_dir_list(string path, bool get_size, bool debug_path)
{
    CD cd;
    FILE_HAND file;
    DIR* dir = opendir(path.c_str());
    vector<vector<string>> list;

    struct dirent* ent;

    while ((ent = readdir(dir)) != NULL)
    {
        string buf_type = this->get_buf_type(cd.format_path(path) + (string)ent->d_name);

        if ((string)ent->d_name != "." && (string)ent->d_name != "..")
            list.push_back(vector<string>(
                {
                    (string)ent->d_name,
                    buf_type,
                    ((get_size) ? ((buf_type == "FILE") ? to_string(file.get_file_size(cd.format_path(path) + ent->d_name)) 
                    : to_string(this->get_dir_size(cd.format_path(path) + ent->d_name))) : "null"),
                    ((debug_path) ? cd.format_path(path) + ent->d_name : "null")
                }
            ));
    }

    return list;
}

 float DIRS::get_dir_size(string path)
{
    FILE_HAND file;
    CD cd;
    vector<vector<string>> buf_list = this->get_dir_list(path, true, false);

    float size = 0;

    for (vector<string> i : buf_list)
    {
        if (i[1] == "FILE" && i[0] != "." && i[0] != "..")
            size += file.get_file_size(cd.format_path(path) + i[0]);

        else
            size += this->get_dir_size(cd.format_path(path) + i[0]);
    }

    return size;
}

string DIRS::get_buf_type(string path)
{
    ifstream buf;
    buf.open(path); // try to open a file, if it can't be open it's because the buff (buffer: file or directory) type is a Directory

    if (!buf)
        return "DIRS";

    else 
        return "FILE"; 
}

void DIRS::m_dir(string d_name)
{
    mkdir(d_name.c_str());
}

void DIRS::rm_dir(string d_name)
{
    rmdir(d_name.c_str());
}

int DIRS::get_max_args()
{
    return this->max_args;
}

int DIRS::get_max_M_DIR_args()
{
    return this->max_M_DIR_args;
}

int DIRS::get_max_RM_DIR_args()
{
    return this->max_RM_DIR_args;
}