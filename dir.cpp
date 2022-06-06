#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <map>
#include <fstream>

#include "dir.hpp"

using namespace std;

DIRS::DIRS()
{
    this->max_args = 0;
}

int DIRS::get_max_args()
{
    return this->max_args;
}

vector<vector<string>> DIRS::get_dir_list(string path)
{
    DIR* dir = opendir(path.c_str());
    vector<vector<string>> list;

    struct dirent* ent;

    while ((ent = readdir(dir)) != NULL)
    {
        if ((string)ent->d_name != "." && (string)ent->d_name != "..")
        {
            //cout << path + ((path[path.size() - 1] == '/') ? "" : " ") + (string)ent->d_name << endl;
            list.push_back(vector<string>({ (string)ent->d_name, get_buf_type(path + ((path[path.size() - 1] == '/') ? "" : "/") + (string)ent->d_name) }));
        }
    }

    return list;
}

string DIRS::get_buf_type(string path)
{
    ifstream buf;
    buf.open(path);

    if (!buf) { return "DIRS"; }
    else { return "FILE"; }
}