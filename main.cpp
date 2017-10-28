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

std::vector<std::string> get_children_dir(const char * path) {

	std::vector<std::string> dirlist;

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

std::vector<std::string> get_all_pid_list() {

	std::vector<std::string> pid_list;
	std::vector<std::string> proc_entries = get_children_dir( PROC_PATH );

	std::regex pid_pattern ("^\\d+$");

	for (unsigned int i = 0; i < proc_entries.size(); i++ ) {

		if ( ! std::regex_match(proc_entries[i], pid_pattern) )
			continue;

		pid_list.push_back(proc_entries[i]);

	}

	return pid_list;
}

std::vector<std::string> get_pid_children_list(std::vector<std::string> pid_list, unsigned int ppid) {

	std::vector<std::string> pid_children_list;

	std::ifstream ifs;
	std::string path;

	// SEE: man 5 proc
	unsigned int process_pid;
	std::string process_comm;
	char process_state;
	unsigned int process_ppid;

	for (unsigned int i = 0; i < pid_list.size(); i++) {
		// para registro, procurar os pids com ppid igual ao do parametro
		path = std::string(PROC_PATH) + "/" + pid_list[i] + "/stat";
		ifs.open(path.c_str());
		ifs >> process_pid >> process_comm >> process_state >> process_ppid;

		if (process_ppid == ppid) {
			pid_children_list.push_back(pid_list[i]);
		}

		ifs.close();
	}

	return pid_children_list;
}

void generate_sub_tree(Node * node, std::vector<std::string> pid_list, unsigned int ppid) {

	std::vector<std::string> sub_list = get_pid_children_list(pid_list, ppid);

	for (unsigned int i = 0; i < sub_list.size(); i++ ) {

		Node * new_node = new Node();
		new_node->setValue( sub_list[i] );
		new_node->setParent(node);
		node->addChildren(new_node);

		generate_sub_tree(new_node, pid_list, std::stoul(sub_list[i]) );
	}

}

Node treeify(std::vector<std::string> pid_list) {
	Node root;

	root.setValue("");
	root.setParent(nullptr);

	generate_sub_tree(&root, pid_list, 0);

	root.doPrint();
	return root;
}

int main( int argc, char ** argv) {

	std::vector<std::string> pid_list = get_all_pid_list();

	Node tree_root = treeify(pid_list);


	return 0;
}

