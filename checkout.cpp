// Collin Campbell
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
		getline(bookFile, title);
		getline(bookFile, title);
		getline(bookFile, author);
		getline(bookFile, category);
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
		personFile >> act;
		personFile >> fName;
		personFile >> lName;
		myCardholders.push_back(new Person(cardNo, act, fName, lName));
	}
	return 0;
}
/*void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders)
{
	ifstream rentalFile;
	long bookID
	rentalFile.open("rentals.txt");
	while (rentalFile)
	{
		if (rentalFile.eof() == true)
			return;
		rentalFile >> BookID;
		
	}
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
	string fullName, fName, lName;
	string input;
	ofstream bookFile;
	ofstream personFile;
	bool outRentals = false, cardHold = false;
	readBooks(books);
	readPersons(cardholders);

	int choice;
	do
	{
		printMenu();
		cin >> choice;
		cout << endl;
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
			cin >> cardID;
			for (j = 0; j < cardholders.size(); j++)
			{
				if(cardholders[j]->getId() == cardID)
					cout << "Cardholder: " << cardholders[j]->fullName() << endl << endl;
			}
			for(i = 0; i < books.size(); i++)
			{
				if(books[i]->getPersonPtr() != 0)
				{
					if(books[i]->getPersonPtr()->getId() == cardID)
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
			cout << "Please enter the first name: ";
			cin >> fName;
			cout << "Please enter the last name: ";
			cin >> lName;
			fullName = fName + " " + lName;
			for (i = 0; i < cardholders.size(); i++)
			{
				if (cardholders[i]->fullName() == fullName)
				{
					cardholders[i]-> setActive(true);
					cout << "Card ID " << cardholders[i]->getId() << " is active" << endl;
					cout << "Cardholder: " << cardholders[i]->fullName() << endl;
					cardHold = true;
					break;
				}
			}
			if (cardHold == false)
				{
					cardholders.push_back(new Person(cardholders[i - 1]->getId() + 1, true, fName, lName));
					cout << "Card ID " << cardholders[i]->getId() << " is active" << endl;
					cout << "Cardholder: " << cardholders[i]->fullName() << endl;
				}
			cardHold = false;
			break;

		case 7:
			cout << "Please enter the card ID: ";
			cin >> cardID;
			for (i = 0; i < cardholders.size(); i++)
			{
				if(cardholders[i]->getId() == cardID)
				{
					cout << "Cardholder: " << cardholders[i]->fullName() << endl;
					if(cardholders[i]->isActive() == true)
					{
						cout << "Are you sure you want to deactivate your card (y/n)? ";
						cin >> input;
						if(input == "y")
						{
							cardholders[i]->setActive(false);
							cout << "Card ID deactivated" << endl;
						}
					}
					else
						cout << "Card ID is already active" << endl;
					cardHold = true;
					break;
				}
			}
			if (cardHold == false)
				cout << "Card ID not found" << endl;
			cardHold = false;
			break;

		case 8:
			personFile.open("person.txt");
			for(i = 0; i < cardholders.size(); i++)
			{
				personFile << cardholders[i]->getId() << " ";
				personFile << cardholders[i]->isActive() << " ";
				personFile << cardholders[i]->fullName() << endl;
			}
			personFile.close();
			break;

		default:
			cout << "Invalid entry" << endl;
			break;
		}
		cout << endl;
	} while (choice != 8);
	return 0;
}
