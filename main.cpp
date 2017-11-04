#include <cstdio>
#include <cerrno>
#include <dirent.h>
#include <cstring>
#include <regex>
#include <iostream>
#include <fstream>

#include "node.h"

#define PROC_PATH "/proc"

std::vector<std::string> get_children_dir(const char * path) {

    std::vector<std::string> dirlist;

    DIR * dir = opendir(path);

    if (dir == nullptr) {
        printf("Error opening dir \"%s\": %s", path, strerror(errno));
    }

    errno = 0;
    dirent * entry;

    while ( (entry = readdir(dir)) )  {
        dirlist.emplace_back(entry->d_name);
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

    for (const auto &proc_entrie : proc_entries) {

        if ( ! std::regex_match(proc_entrie, pid_pattern) )
            continue;

        pid_list.push_back(proc_entrie);

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

    for (const auto &i : pid_list) {
        // para registro, procurar os pids com ppid igual ao do parametro
        path = std::string(PROC_PATH) + "/" + i + "/stat";
        ifs.open(path.c_str());
        ifs >> process_pid >> process_comm >> process_state >> process_ppid;

        if (process_ppid == ppid) {
            pid_children_list.push_back(i);
        }

        ifs.close();
    }

    return pid_children_list;
}

void generate_sub_tree(Node * node, const std::vector<std::string> &pid_list, unsigned int ppid) {

    std::vector<std::string> sub_list = get_pid_children_list(pid_list, ppid);

    for (const auto &i : sub_list) {

        auto * new_node = new Node();
        new_node->setValue(i);
        new_node->setParent(node);
        node->addChildren(new_node);

        generate_sub_tree(new_node, pid_list, (unsigned int) std::stoi(i) );
    }

}

Node treeify(const std::vector<std::string> &pid_list) {
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

