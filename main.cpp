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
	std::cout << "4) Close Book" << std::endl;
}

int main(){
	Contacts iCloud; //replace this with one Contacts object per tree.
	Contact* newNode = 0; //for use in adding contacts
	treeNode* node = 0; //the contact returned by contactByName (or other variation)
	Contact* del = 0; //variable to store a node to delete
	std::string input; //the string that you use to in (4) to search for a Contact and return a pointer to it.

	//Add in loading functionality from a file.

	std::string mainMenuChoice = "";
	while (mainMenuChoice != "5") {
		m();
		std::cin >> mainMenuChoice;
		if (mainMenuChoice < "1" || mainMenuChoice > "4") {
			std::cout << "Not a Valid Number Selection! Please choose between 1 and 4." << std::endl;
		}
		else {
			switch (stoi(mainMenuChoice)) { // will break if mainMenuChoice is a non-number.
			case 1: // User selected to print all of the contacts in their book.
				iCloud.printAllContacts(); // need option to change sorting
				break;
			case 2: // User selected to search for an existing contact
				iCloud.search(); // K - User searches, finds, then can edit or delete is what I'm thinking
				break;
			case 3: // User selected to add a new contact
				iCloud.createContact();
				break;
			case 4: // User selected to close the book. Should put saving into here.
				std::cout << "*closes book*" << std::endl;
				break;
			case 5:
				std::cout << "secret hacker menu, I've just added a few contacts :)" << std::endl;
				
				break;
			}
		}
		std::cout << std::endl; // for main menu spacing
	}
	return 0;
}
