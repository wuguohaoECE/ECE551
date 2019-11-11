#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <dirent.h>

using namespace std;
typedef unordered_map<string,vector<string>> stringmap;

void insert_file(stringmap & map, const char * link) {
  ifstream in(link);
  string contents;
  if (in) {
    in.seekg(0, ios::end);
    size_t len = in.tellg();
    in.seekg(0);
    contents.resize(len + 1, '\0');
    in.read(&contents[0], len);
    map[contents].emplace_back(link);
  }
}



void find_file(stringmap & map, const char * link) {
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (link)) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      if( (strcmp(ent->d_name,".") == 0) || (strcmp(ent->d_name,"..") == 0) ) {
	continue;
      }
      string old_dir(link);
      string file_n(ent->d_name);
      string new_dir = old_dir + "/" + file_n;
      if( ent->d_type == DT_DIR ) {
	cout << new_dir << endl;
	find_file(map, new_dir.c_str());
      }
      else if(ent->d_type != DT_LNK) {
	insert_file(map, new_dir.c_str());
      }
    }
    closedir (dir);
  }
  else {
    /* could not open directory */
    perror ("");
  }
  
}

int main(int argc, char ** argv) {
  stringmap dedup;
  if(argc < 2) {
    cerr << "must have at least one directory" << endl;
  }

  for(int i = 1; i < argc; i++) {
    find_file(dedup, argv[i]);
  }
  cout << "#!/bin/bash" << endl;
  for (auto it = dedup.begin(); it != dedup.end(); ++it) {
    if(it->second.size() > 1) {
      for(size_t i = 1; i < it->second.size(); i++) {
	cout << "#Removing " << it->second[i] << " (duplicate of"<< "\n" << it->second[0] << "\n" << endl;
       	cout << "rm " << it->second[i] << "\n" << endl;
      }
    }
  }  
  return EXIT_SUCCESS;
}
