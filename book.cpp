#include "book.h"

Book::Book(int id = 0, string bookName = "", string auth = "", string cat = "") 
{
	title = bookName;
	author = auth;
	category = cat;
	bookID = id;
}

string Book::getTitle() 
{
	return title;
}

string Book::getAuthor()
{
	return author;
}

string Book::getCategory()
{
	return category;
}

int Book::getId() 
{
	return bookID;
}
void Book::setPersonPtr(Person * ptr) 
{

} // complete

Person * Book::getPersonPtr()
{
	return nullptr; // complete
}