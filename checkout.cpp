// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include "person.cpp"
#include "book.h"

using namespace std;

void printMenu() {
	cout << "----------Library Book Rental System----------" << endl;
	cout << "1.  Book checkout" << endl;
	cout << "2.  Book return" << endl;
	cout << "3.  View all available books" << endl;
	cout << "4.  View all outstanding rentals" << endl;
	cout << "5.  View outstanding rentals for a cardholder" << endl;
	cout << "6.  Open new library card" << endl;
	cout << "7.  Close library card" << endl;
	cout << "8.  Exit system" << endl;
	cout << "Please enter a choice: ";
}

//You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks)
{
	int id;
	string title, author, category;
	ifstream bookFile;
	bookFile.open("books.txt");
	while (bookFile)
	{
		if(bookFile.eof() == true)
			return;
		bookFile >> id;
		//cout << id << endl;
		getline(bookFile, title); //used to get rid of the new line after the id line
		getline(bookFile, title);
		//cout << title << endl;
		getline(bookFile, author);
		//cout << author << endl;
		getline(bookFile, category);
		//cout << category << endl;
		myBooks.push_back(new Book(id, title, author, category));
	}
	return;
}

int readPersons(vector<Person *> & myCardholders)
{
	int cardNo, act;
	string fName, lName;
	ifstream personFile;
	personFile.open("person.txt");
	while (personFile)
	{
		if (personFile.eof() == true)
			return 0;
		personFile >> cardNo;
		//cout << id << endl;
		personFile >> act;
		//cout << active << endl;
		personFile >> fName;
		//cout << fName << endl;
		personFile >> lName;
		//cout << lName << endl;
		myCardholders.push_back(new Person(cardNo, act, fName, lName));
	}
	return 0;
}
/*
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
	return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
	return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
	return nullptr;
}
*/

int main()
{
	vector<Book *> books;
	vector<Person *> cardholders;
	int cardID, bookID, i, j;
	bool outRentals = false;
	string cardholder;
	readBooks(books);
	//cout << books[0]->getId() << endl;
	readPersons(cardholders);

	int choice;
	do
	{
		// If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
		// the user pressed when entering a menu option. This is still in the input stream.
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Please enter the card ID: ";
			cin >> cardID;
			for (i = 0; i < cardholders.size(); i++)
			{
				if(cardholders[i]->getId() == cardID)
				{
					cout << "Cardholder: " << cardholders[i]->getFirstName() << " " << cardholders[i]->getLastName() << endl;
					cout << "Please enter the book ID: ";
					cin >> bookID;
					for (j = 0; j < books.size(); j++)
					{
						if(books[j]->getId() == bookID)
						{
							cout << "Title: " << books[j]->getTitle() << endl;
							if(books[j]->getPersonPtr() == 0)
							{
								books[j]->setPersonPtr(cardholders[i]);
								cout << "Rental Complete" << endl;
							}
							else
								cout << "Book already checked out" << endl;
							break;
						}
					}
					if(j == books.size())
						cout << "Book ID not found" << endl;
					break;
				}
			}
			if(i == cardholders.size())
				cout << "Card ID not found" << endl;
			break;

		case 2:
			cout << "Please enter the book ID to return: ";
			cin >> bookID;
			for(i = 0; i < books.size(); i++)
			{
				if(bookID == books[i]->getId())
				{
					cout << "Title: " << books[i]->getTitle();
					cout << "Return Completed" << endl;
					books[i]->setPersonPtr(nullptr);
					break;
				}
				else
					cout << "Book ID not found" << endl;
			}
			break;

		case 3:
			for(i = 0; i < books.size(); i++)
			{
				if(books[i]->getPersonPtr() == 0)
				{
					cout << "Book ID: " << books[i]->getId() << endl;
					cout << "Title: " << books[i]->getTitle() << endl;
					cout << "Author: " << books[i]->getAuthor() << endl;
					cout << "Category: " << books[i]->getCategory() << endl << endl;
					outRentals = true;
				}
			}
			if (outRentals == false)
				cout << "No outstanding rentals" << endl;
			outRentals = false;
			break;

		case 4:
			for(i = 0; i < books.size(); i++)
			{
				if(books[i]->getPersonPtr() != 0)
				{
					cout << "Book ID: " << books[i]->getId() << endl;
					cout << "Title: " << books[i]->getTitle() << endl;
					cout << "Author: " << books[i]->getAuthor() << endl;
					cout << "Category: " << books[i]->getCategory() << endl;
					cout << "Cardholder: " << books[i]->getPersonPtr()->fullName() << endl;
					cout << "Card ID: " << books[i]->getPersonPtr()->getId() << endl << endl;
					outRentals = true;
				}
			}
			if (outRentals == false)
				cout << "No outstanding rentals" << endl;
			outRentals = false;
			break;

		case 5:
			cout << "Please enter the card ID: ";
			cin >> cardholder;
			for (j = 0; j < cardholders.size(); j++)
			{
				if(cardholders->getId() == cardholder)
					cout << "Cardholder: " << cardholders->fullName() << endl << endl;
			}
			for(i = 0; i < books.size(); i++)
			{
				if(books[i]->getPersonPtr() != 0)
				{
					if(books[i]->getPersonPtr()->getId() == cardholder)
					{
						cout << "Book ID: " << books[i]->getId() << endl;
						cout << "Title: " << books[i]->getTitle() << endl;
						cout << "Author: " << books[i]->getAuthor() << endl << endl;
						outRentals = true;
					}
				}
			}
			if (outRentals == false)
				cout << "No books currently checked out" << endl;
			outRentals = false;
			break;

		case 6:
			// Open new library card
			break;

		case 7:
			// Close library card
			break;

		case 8:
			// Must update records in files here before exiting the program
			break;

		default:
			cout << "Invalid entry" << endl;
			break;
		}
		cout << endl;
	} while (choice != 8);
	return 0;
}
