#pragma once
#include<string>
#include<vector>
#include "Book.h"

using namespace std;

class Collection
{
private:
	vector<Book> books;
public:
	Collection();
	~Collection();
	vector<Book> getBooks();
	void addBook(Book book);
	bool searchBookByTitle(string title, Book& bookResult);
	bool searchBookByAuthor(string author, Book& bookResult);
	void sortByTitles();
	void sortByAuthors();
	void sortByReleaseDate();
	void updateBook(Book book);
	void saveToFile(string filename);
	friend ostream& operator<<(ostream& os, const Collection& collection);
};

