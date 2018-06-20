#include "stdafx.h"
#include "Book.h"


Book::Book()
{
}


Book::~Book()
{
}

string Book::getAuthor()
{
	return author;
}

string Book::getTitle()
{
	return title;
}

int Book::getReleaseDate()
{
	return releaseDate;
}

bool Book::isAvailable()
{
	return available;
}

string Book::getId()
{
	return id;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

void Book::setTitle(string title)
{
	this->title = title;
}

void Book::setReleaseDate(int releaseDate)
{
	this->releaseDate = releaseDate;
}

void Book::setAvailable(bool available)
{
	this->available = available;
}

void Book::setId(string id)
{
	this->id = id;
}

ostream & operator<<(ostream & os, const Book & book)
{
	os << "id: " << book.id << "; ";
	os << "autor: " << book.author << "; ";
	os << "tytul: " << book.title << "; ";
	os << "data wydania: " << book.releaseDate << "; ";
	return os;
}
