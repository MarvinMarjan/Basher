// c++ modules
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <map>
#include <fstream>
#include <direct.h>

// program modules
#include "dir.hpp"
#include "path.hpp"

using namespace std;

DIRS::DIRS()
{
    this->max_args = 0;
    this->max_M_DIR_args = 1;
    this->max_RM_DIR_args = 1;
}

vector<vector<string>> DIRS::get_dir_list(string path)
{
    DIR* dir = opendir(path.c_str());
    vector<vector<string>> list;

    struct dirent* ent;

    while ((ent = readdir(dir)) != NULL)
    {
        if ((string)ent->d_name != "." && (string)ent->d_name != "..")
            list.push_back(vector<string>(
                {
                    (string)ent->d_name,
                    get_buf_type(path + ((path[path.size() - 1] == '/') ? "" : "/") + (string)ent->d_name)
                }
            ));
    }

    return list;
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