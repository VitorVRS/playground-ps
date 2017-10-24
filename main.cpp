#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "node.h"

#define PROC_PATH "/proc"

std::vector<char *> get_children_dir(const char * path) {

	std::vector<char *> dirlist;

	DIR * dir = opendir(path);

	if (dir == NULL) {
		printf("Error opening dir \"%s\": %s", path, strerror(errno));
	}

	errno = 0;
	dirent * entry;

	while ( (entry = readdir(dir)) )  {
		dirlist.push_back(entry->d_name);
	}

	int _errno = errno;

	if ( -1 == closedir(dir)) {
		printf("Error closing dir \"%s\": %s", path, strerror(errno));
	}

	if ( 0 != _errno ) {
		printf("Error reading dir \"%s\": %s", path, strerror(_errno));
	}

	return dirlist;
}

std::vector<char *> get_all_pid_list() {

	std::vector<char *> pid_list;
	std::vector<char *> proc_entries = get_children_dir( PROC_PATH );

	std::regex pid_pattern ("^\\d+$");

	for (unsigned int i = 0; i < proc_entries.size(); i++ ) {

		if ( ! std::regex_match(proc_entries[i], pid_pattern) )
			continue;

		pid_list.push_back(proc_entries[i]);

	}

	return pid_list;
}

std::vector<char *> get_pid_children_list(std::vector<char *> pid_list, int ppid) {

	std::vector<char *> pid_children_list;

	std::ifstream ifs;
	std::string path;

	for (unsigned int i = 0; i < pid_list.size(); i++) {
		// para registro, procurar os pids com ppid igual ao do parametro
		path = std::string(PROC_PATH) + "/" + pid_list[i] + "/stat";
		ifs.open(path.c_str());
		/// TODO
		ifs.close();
	}

	return pid_children_list;
}

Node treeify(std::vector<char *> pid_list) {
	Node root;

	root.setValue(0);
	root.setParent(nullptr);

	int ppid = 0;

	std::vector<char *> root_list = get_pid_children_list(pid_list, ppid);

//	generate_sub_tree(root, root_list);

	return root;
}

int main( int argc, char ** argv) {

	std::vector<char *> pid_list = get_all_pid_list();

	Node tree_root = treeify(pid_list);

	return 0;
}

