#include "stdafx.h"
#include "Collection.h"
#include <algorithm>
#include <iostream>
#include <fstream>


Collection::Collection()//to jest konstruktor
{
}


Collection::~Collection()
{
}

vector<Book> Collection::getBooks()
{
	return books;
}

void Collection::addBook(Book book)
{
	books.push_back(book);
}

ostream & operator<<(ostream & os, const Collection & collection)
{
	vector<Book> books = collection.books;
	for (auto book : books)
	{
		if (book.isAvailable())
		{
			os << book << endl;
		}
	}

	return os;
}

bool Collection::searchBookByTitle(string title, Book & bookResult)
{
	for (auto book : books)
	{
		if (book.getTitle() == title)
		{
			bookResult = book;
			return true;
		}
	}
	return false;
}

bool Collection::searchBookByAuthor(string author, Book & bookResult)
{
	for (auto book : books)
	{
		if (book.getAuthor() == author)
		{
			bookResult = book;
			return true;
		}
	}
	return false;
}

void Collection::sortByTitles()
{
	sort(books.begin(), books.end(), [](Book lhs, Book rhs)
	{
		return lhs.getTitle() < rhs.getTitle();
	});
}

void Collection::sortByAuthors()
{
	sort(books.begin(), books.end(), [](Book lhs, Book rhs)
	{
		return lhs.getAuthor() < rhs.getAuthor();
	});
}

void Collection::sortByReleaseDate()
{
	sort(books.begin(), books.end(), [](Book lhs, Book rhs)
	{
		return lhs.getReleaseDate() < rhs.getReleaseDate();
	});
}

void Collection::updateBook(Book book)//aktualizacja ksiazek
{
	int i = 0;
	for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it, i++)
	{
		if (it->getId() == book.getId())
		{
			books.at(i) = book;
		}
	}
}

void Collection::saveToFile(string filename)
{
	ofstream outputFile(filename);
	
	for (auto book : books)
	{
		outputFile << book.getId();
		outputFile << ";";
		outputFile << book.getAuthor();
		outputFile << ";";
		outputFile << book.getTitle();
		outputFile << ";";
		outputFile << book.getReleaseDate();
		outputFile << ";";
		outputFile << (book.isAvailable() ? "T" : "N");
		outputFile << ";";
		
		outputFile << endl;
	}

	outputFile.close();
}

