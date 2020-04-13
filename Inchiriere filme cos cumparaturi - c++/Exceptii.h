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

class ServiceException {
private:
	string mesaj;
public:
	ServiceException(string msg) : mesaj { msg } {}
	string getMesaj();
};