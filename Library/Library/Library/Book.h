#pragma once
#include<string>

using namespace std;

class Book
{
private:
	string author;
	string title;
	int releaseDate;
	bool available;
	string id;
public:
	Book();
	~Book();
	string getAuthor();
	string getTitle();
	int getReleaseDate();
	bool isAvailable();
	string getId();
	void setAuthor(string author);
	void setTitle(string title);
	void setReleaseDate(int releaseDate);
	void setAvailable(bool available);
	void setId(string id);
	friend ostream& operator<<(ostream& os, const Book& book);
};

