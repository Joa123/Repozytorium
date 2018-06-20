#pragma once
#include<string>

using namespace std;

class Librarian
{
private:
	string login;
	string password;
	string id;
public:
	Librarian();
	Librarian(string id, string login, string password);
	~Librarian();
	string getLogin();
	string getPassword();
};

