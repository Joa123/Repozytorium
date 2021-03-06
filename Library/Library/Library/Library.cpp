// Library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "Librarian.h"
#include "Reader.h"
#include "Collection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;

const string LIBRARIAN_FILENAME = "librarians.txt";
const string READERS_FILENAME = "readers.txt";
const string BOOKS_FILENAME = "books.txt";
const char SPLIT_CHARACTER = ';';

vector<Librarian> librarians;
vector<Reader> readers;
Collection collection;

vector<Librarian> loadLibrariansFromFile(string fileName);
vector<Reader> loadReadersFromFile(string fileName);
Collection loadCollectionFromFile(string fileName);
vector<string> split(string line, char splitBy);
bool login(string login);
void sortCollection();
void searchBook();
string getSearchedText();
void lentBook();
bool getReader(string id, Reader& searchedReader);
bool getBookById(string id, Book& searchedBook);
void replaceReaderInList(Reader reader);
void saveChangesToFiles();
void saveReadersToFile(string filename);
void returnBook();


int main()
{
	//load
	librarians = loadLibrariansFromFile(LIBRARIAN_FILENAME);
	readers = loadReadersFromFile(READERS_FILENAME);
	collection = loadCollectionFromFile(BOOKS_FILENAME);
	
	//main loop
	while (true)
	{
		Librarian activeLibrarian;
		bool librarianFound = false;
		string username;

		cout << "\nPodaj login do zalogowania: ";
		cin >> username;
		cout << endl;

		for (auto librarian : librarians)
		{
			if (librarian.getLogin() == username)
			{
				activeLibrarian = librarian;
				librarianFound = true;
				break;
			}
		}

		if (librarianFound)
		{
			//kontynuacja logowania
			string password;
			cout << "\nPodaj haslo: ";
			cin >> password;

			if (password == activeLibrarian.getPassword())
			{
				bool isLogged = true;
				while (isLogged)
				{
					//zalogowano
					int action;
					cout << "\nWitamy w systemie.\n1. Wyswietl dostepne ksiazki.\n2. Sortuj ksiegozbior.\n3. Wyszukaj ksiazke.\n4. Wypozycz ksiazke.\n5. Zwroc ksiazke.\n6. Wyloguj\nProsze wybrac akcje: ";
					cin >> action;
					switch (action)
					{
					case 1:
						//wyswietl dostepne
						cout << endl;
						cout << collection;
						break;
					case 2:
						//sortuj
						sortCollection();
						break;
					case 3:
						//wyszukaj
						searchBook();
						break;
					case 4:
						//wypozycz
						lentBook();
						break;
					case 5:
						//zwroc
						returnBook();
						break;
					case 6:
						//wylogowanie
						isLogged = false;
						cout << "\nWylogowano z systemu.";
						break;
					default:
						cout << "\nWpisana akcja nie jest obslugiwana!";
					}
				}
			}
			else
			{
				cout << "\nNiepoprawne hasło!";
			}
		}
		else
		{
			cout << "\nBrak pracownika o podanym loginie";
		}

	}

	system("PAUSE");
    return 0;
}

vector<Librarian> loadLibrariansFromFile(string fileName)
{
	vector<Librarian> librarians;
	ifstream myfile(fileName);
	string line;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> values = split(line, SPLIT_CHARACTER);
			Librarian librarian(values[0], values[1], values[2]);
			librarians.push_back(librarian);
		}
		myfile.close();
	}
	else 
		cout << "Nie mozna otworzyc pliku z pracownikami!";


	return librarians;
}

vector<Reader> loadReadersFromFile(string fileName)
{
	vector<Reader> readers;
	ifstream myfile(fileName);
	string line;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> values = split(line, SPLIT_CHARACTER);
			Reader reader;
			reader.setCardNumber(values[0]);
			reader.setName(values[1]);
			reader.setSurname(values[2]);
			
			vector<string> ids;
			for (vector<string>::iterator it = values.begin() + 3; it != values.end(); it++)
			{
				ids.push_back(*it);
			}
			reader.setBooksIds(ids);

			readers.push_back(reader);
		}
		myfile.close();
	}
	else
		cout << "Nie mozna otworzyc pliku z czytelnikami!";


	return readers;
}

Collection loadCollectionFromFile(string fileName)
{
	Collection collection;
	ifstream myfile(fileName);
	string line;

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector<string> values = split(line, SPLIT_CHARACTER);
			Book book;
			book.setId(values[0]);
			book.setAuthor(values[1]);
			book.setTitle(values[2]);
			book.setReleaseDate(stoi(values[3]));
			book.setAvailable(values[4] == "T" ? true : false);

			collection.addBook(book);
		}
		myfile.close();
	}
	else
		cout << "Nie mozna otworzyc pliku z ksiegozbiorem!";


	return collection;
}

vector<string> split(string line, char splitBy)//rozdzielanie-do szufladkowania informacji z plików
{
	stringstream temp(line);
	string segment;
	vector<string> seglist;

	while (getline(temp, segment, splitBy))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

bool login(string login)
{
	return false;
}

void sortCollection()
{
	int sortType;
	cout << "\n1. Po tytule.\n2. Po autorze.\n3. Po dacie wydania.\n Wybierz numer atrybutu do sortowania: ";
	cin >> sortType;

	switch (sortType)
	{
	case 1:
		//po tytule
		collection.sortByTitles();
		break;
	case 2:
		//po autorze
		collection.sortByAuthors();
		break;
	case 3:
		//po dacie wydania
		collection.sortByReleaseDate();
		break;
	default:
		cout << "\nWybrano nieobslugiwane sortowanie!";
		break;
	}
}

void searchBook()
{
	int searchType;
	string searchText;
	Book searchedBook;
	bool bookFounded = false;
	cout << "\n1. Szukaj po tytule.\n2. Szukaj po autorze.\nWybierz akcje: ";
	cin >> searchType;

	switch (searchType)
	{
	case 1:
		//title
		searchText = getSearchedText();
		bookFounded = collection.searchBookByTitle(searchText, searchedBook);
		break;
	case 2:
		//author
		searchText = getSearchedText();
		bookFounded = collection.searchBookByAuthor(searchText, searchedBook);
		break;
	default:
		cout << "\nWybrano nieobslugiwane wyszukiwanie!";
		return;
	}

	if (bookFounded)
	{
		cout << "\nZnaleziono ksiazke: " << searchedBook << ". Czy mozna wyporzyczyc: " << (searchedBook.isAvailable() ? "T" : "N");
	}
	else
	{
		cout << "\nWyszukiwana ksiazka nie zostala znaleziona.";
	}
}

string getSearchedText()
{
	string searchText;
	cout << "\nPodaj wyszukiwana fraze: ";
	getline(cin, searchText);//dla wyczyszczenia z bufora cin znaku konca lini
	getline(cin, searchText);
	return searchText;
}

void lentBook()
{
	Reader customer;
	string readerCardId;
	cout << "\nPodaj numer karty osoby wypozyczajacej: ";
	cin >> readerCardId;
	
	if (getReader(readerCardId, customer))
	{
		string bookId;
		Book bookToLent;

		cout << "\nPodaj id ksiazki: ";
		cin >> bookId;

		if (getBookById(bookId, bookToLent))
		{
			if (bookToLent.isAvailable())
			{
				//wypozyczenie
				customer.borrowBook(bookToLent);
				collection.updateBook(bookToLent);
				replaceReaderInList(customer);
				saveChangesToFiles();
			}
			else
			{
				cout << "\nKsiazka jest niedostepna";
			}
		}
		else
		{
			cout << "\nBrak ksiazki o podanym numerze id!";
		}
	}
	else
	{
		cout << "\nBrak czytelnika o podanym numerze karty!";
	}
}

bool getReader(string id, Reader& searchedReader)
{
	for (auto reader : readers)
	{
		if (reader.getCardNumber() == id)
		{
			searchedReader = reader;
			return true;
		}
	}
	return false;
}

bool getBookById(string id, Book & searchedBook)
{
	for (auto book : collection.getBooks())
	{
		if (book.getId() == id)
		{
			searchedBook = book;
			return true;
		}
	}
	return false;
}

void replaceReaderInList(Reader reader)//uaktualnianie czytelników
{
	int i = 0;
	for (vector<Reader>::iterator it = readers.begin(); it != readers.end(); ++it, i++)
	{
		if (it->getCardNumber() == reader.getCardNumber())
		{
			readers.at(i) = reader;
		}
	}
}

void saveChangesToFiles()
{
	collection.saveToFile(BOOKS_FILENAME);
	saveReadersToFile(READERS_FILENAME);
}

void saveReadersToFile(string filename)
{
	ofstream outputFile(filename);

	for (auto reader : readers)
	{
		outputFile << reader.getCardNumber();
		outputFile << ";";
		outputFile << reader.getName();
		outputFile << ";";
		outputFile << reader.getSurname();
		outputFile << ";";

		for (auto bookId : reader.getBooksIds())
		{
			outputFile << bookId;
			outputFile << ";";
		}
		outputFile << endl;
	}

	outputFile.close();
}

void returnBook()
{
	Reader customer;
	string readerCardId;
	cout << "\nPodaj numer karty czytelnika: ";
	cin >> readerCardId;

	if (getReader(readerCardId, customer))
	{
		string bookId;
		Book bookToReturn;

		cout << "\nPodaj id ksiazki: ";
		cin >> bookId;

		if (getBookById(bookId, bookToReturn))
		{
			customer.returnBook(bookToReturn);
			collection.updateBook(bookToReturn);
			replaceReaderInList(customer);
			saveChangesToFiles();
			
		}
		else
		{
			cout << "\nBrak ksiazki o podanym numerze id!";
		}
	}
	else
	{
		cout << "\nBrak czytelnika o podanym numerze karty!";
	}
}
