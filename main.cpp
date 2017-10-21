#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <regex>
#include <iostream>
#include <vector>

const char * PROC_PATH = "/proc";

std::vector<char *> get_children_dir(char * path) {

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
	std::vector<char *> proc_entries = get_children_dir( (char *) PROC_PATH );

	std::regex pid_pattern ("^\\d+$");

	for (unsigned int i = 0; i < proc_entries.size(); i++ ) {

		if ( ! std::regex_match(proc_entries[i], pid_pattern) )
			continue;

		pid_list.push_back(proc_entries[i]);
	}

	return pid_list;
}

void treeify(std::vector<char *> pid_list) {
	return;
}

int main( int argc, char ** argv) {

	std::vector<char *> pid_list = get_all_pid_list();

	std::cout << "SIZE: " << pid_list.size();

	return 0;
}

