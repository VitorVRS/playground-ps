#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <vector>

std::vector<char *> getChildrenDir(char * path) {

	std::vector<char *> dirlist;

	DIR * dir = opendir(path);

	if (dir == NULL) {
		printf("Error opening dir \"%s\": %s", path, strerror(errno));
	}

	errno = 0;
	dirent * entry;

	while ( entry = readdir(dir) )  {
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

int main( int argc, char ** argv) {

	const char * procPath = "/proc";

	std::vector<char *> list = getChildrenDir((char *) procPath);

	for (unsigned int i = 0; i < list.size(); i++ ) {
		printf("%s\n", list[i]);
	}
	return 0;
}

