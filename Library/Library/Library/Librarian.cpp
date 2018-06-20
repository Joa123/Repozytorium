#include "stdafx.h"
#include "Librarian.h"


Librarian::Librarian()
{
}

Librarian::Librarian(string id, string login, string password)
{
	this->id = id;
	this->login = login;
	this->password = password;
}


Librarian::~Librarian()
{
}

string Librarian::getLogin()
{
	return login;
}

string Librarian::getPassword()
{
	return password;
}
