#pragma once
#include <stdlib.h>
#include <string>
using std::string;

class RepoException {
private:
	string mesaj;
public:
	RepoException(string msg) : mesaj{ msg } {}
	string getMesaj();
};
