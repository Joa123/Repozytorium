#include "stdafx.h"
#include "Reader.h"


Reader::Reader()
{
}


Reader::~Reader()
{
}

string Reader::getName()
{
	return name;
}

string Reader::getSurname()
{
	return surname;
}

string Reader::getCardNumber()
{
	return cardNumber;
}

vector<string> Reader::getBooksIds()
{
	return booksIds;
}

void Reader::setName(string name)
{
	this->name = name;
}

void Reader::setSurname(string surname)
{
	this->surname = surname;
}

void Reader::setCardNumber(string cardNumber)
{
	this->cardNumber = cardNumber;
}

void Reader::setBooksIds(vector<string> ids)
{
	this->booksIds = ids;
}

void Reader::borrowBook(Book & book)
{
	booksIds.push_back(book.getId());//dodaje id ksiazki do czytelnika
	book.setAvailable(false);//ksiazka nie jest dostepna
}

void Reader::returnBook(Book & book)
{
	for (vector<string>::iterator it = booksIds.begin(); it != booksIds.end(); ++it)
	{
		if (*it == book.getId())
		{
			booksIds.erase(it);//usuwa id ksiazki z konta czytelnika 
			book.setAvailable(true);//ksiazka znow jest dostepna
			return;
		}
	}
}

