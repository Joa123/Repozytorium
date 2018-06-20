#pragma once
#include<string>
#include<vector>
#include"Book.h"

using namespace std;

class Reader
{
private:
	string name;
	string surname;
	string cardNumber;
	vector<string> booksIds;
public:
	Reader();
	~Reader();
	string getName();
	string getSurname();
	string getCardNumber();
	vector<string> getBooksIds();
	void setName(string name);
	void setSurname(string surname);
	void setCardNumber(string cardNumber);
	void setBooksIds(vector<string> ids);
	void borrowBook(Book& book);
	void returnBook(Book& book);
};

