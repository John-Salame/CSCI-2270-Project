/** CSCI-2270 - Data Structures Project.

John Salame - 109001053
Kyran Butler - 108492940
Inji Chung -

g++ -std=c++11 main.cpp -o runner
*/

#include <iostream>
#include <string>
#include "Contacts.h"

void m() { // main menu
	std::cout << "--=[ Contact Book ]=--" << std::endl;
	std::cout << "1) Print All Contacts" << std::endl;
	std::cout << "2) Search For Contact" << std::endl;
	std::cout << "3) Add Contact" << std::endl;
	std::cout << "4) Display Contact" << std::endl; //search contact by exact name, return pointer to Contact. In Ji will turn this into GUI stuff later.
	std::cout << "5) Close Book" << std::endl;
}

int main(){
	Contacts iCloud; // named the main book iCloud, because why not!
	Contact* edit = 0; //the contact returned by contactByName (or other variation)
	std::string input; //the string that you use to in (4) to search for a Contact and return a pointer to it.

	//Add in loading functionality from a file.

	std::string mainMenuChoice = "";
	while (mainMenuChoice != "5") {
		m();
		std::cin >> mainMenuChoice;
		if (mainMenuChoice < "1" || mainMenuChoice > "5") {
			std::cout << "Not a Valid Number Selection! Please choose between 1 and 4." << std::endl;
		}
		else {
			switch (stoi(mainMenuChoice)) { // will break if mainMenuChoice is a non-number.
			case 1: // User selected to print all of the contacts in their book.
				iCloud.printAllContacts();
				break;
			case 2: // User selected to search for an existing contact
				iCloud.searchByName(); // K - User searches, finds, then can edit or delete is what I'm thinking
				break;
			case 3: // User selected to add a new contact
				iCloud.addByName();
				break;
			case 4:
				std::cout << "Enter the full name of the contact (this will be replaced by clicking a name later)" << std::endl;
				std::getline(std::cin, input); //get rid of the \n from using << everywehre else
				std::getline(std::cin, input); //get exact name or phone number or email, etc.
				edit = iCloud.contactByName(input);
				if(edit != 0)
				{
					iCloud.displayContact(edit);
				}
				//editing stuff could be in here as well, but that's up to In Ji.
				break;
			case 5: // User selected to close the book. Should put saving into here.
				std::cout << "*closes book*" << std::endl;
				break;
			}
		}
		std::cout << std::endl; // for main menu spacing
	}
	return 0;
}
