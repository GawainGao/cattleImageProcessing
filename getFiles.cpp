//
//  getFiles.cpp
//  New_cattle
//
//  Created by 高源 on 2018/10/28.
//  Copyright © 2018 Gao Yuan. All rights reserved.
//

#include "getFiles.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <regex>


using namespace std;

/*
 path
 exd: jpg,png ex. if all the file, use ""
 files: getFile
*/

vector<string> getFiles( string path, string exd )
{
    struct dirent *ptr;
    DIR *dir;
    dir = opendir(path.c_str());
    vector<string> files;
    files.clear();
    cout << "List of files" << endl;
    dir = opendir(path.c_str());
    regex reg_obj(exd, regex::icase);
    if ((dir = opendir(path.c_str())) == NULL)
    {
        cout << "Can not open " << path << endl;
        return files;
    }
    while ((ptr = readdir(dir)) != NULL) {
        if (ptr -> d_type == 8)
        {
            if (ptr->d_name[0] == '.')
                continue;
            //cout << "Check" << endl;
            if (regex_match(ptr->d_name, reg_obj))
            {
                string all_path = path + "/" + ptr->d_name;
                files.push_back(all_path);
                //cout << ptr->d_name << " " << ptr->d_ino << " " << ptr->d_reclen << " " << ptr->d_type << endl;
            }
        }
    }
    closedir(dir);
    return files;
}
