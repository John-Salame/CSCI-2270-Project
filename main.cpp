/** CSCI-2270 - Data Structures Project. 

John Salame - 
Kyran Butler - 108492940
Inji Chung - 

*/

#include <iostream>
#include <string>

struct Contact { // actual contact

	std::string name;
	std::string phoneNumber;
	std::string birthdate;
	std::string socialSecurityNumber;
	std::string creditCardNumber;
	std::string threeDigitsOnTheBack;
	std::string favoriteAnime;

};

struct treeNode { // used to build tree of contacts, built as if the tree is organized by first name alphabatized right now

	treeNode* leftChild; // if organized by name, this name is less than the current name
	treeNode* rightChild; // if organized by name, this name is greater than the current name
	treeNode* parent; // K - easier to delete contacts I think
	Contact c; // contact information located at tree pos

};



class Contacts {
public:
	void printAllContacts();
	void searchContact();
	void addContact();
	void editContact();
	void deleteContact();

private:
	treeNode* root; // root of the treeNode
};

void inOrder(treeNode* curr) {
	inOrder(curr->leftChild);
	std::cout << "-" << curr->c.name << " - " << curr->c.phoneNumber << std::endl; // simple print name / phone number
	inOrder(curr->rightChild);
}

void Contacts::printAllContacts() { // prints all of the contacts in the tree.
	inOrder(root);
}




void m() { // main menu
	std::cout << "--=[ Contact Book ]=--" << std::endl;
	std::cout << "1) Print All Contacts" << std::endl;
	std::cout << "2) Search For Contact" << std::endl;
	std::cout << "3) Add Contact" << std::endl;
	std::cout << "4) Close Book" << std::endl;
}

// everything that's here is super rough just to get some work done
int main(){
	Contacts iCloud; // named the main book iCloud, because why not!

	//Add in loading functionality from a file.

	std::string mainMenuChoice = "";
	while (mainMenuChoice != "4") {
		m();
		std::cin >> mainMenuChoice;

		switch (stoi(mainMenuChoice)) { // will break if mainMenuChoice is a non-number.
		case 1: // User selected to print all of the contacts in their book.
			iCloud.printAllContacts(); 
			break;
		case 2: // User selected to search for an existing contact
			iCloud.searchContact(); // K - User searches, finds, then can edit or delete is what I'm thinking
			break;
		case 3: // User selected to add a new contact
			iCloud.addContact();
			break;
		case 4: // User selected to close the book. Should put saving into here.
			std::cout << "*closes book*" << std::endl;
			break;
		default:
			std::cout << "Not a Valid Number Selection! Please choose between 1 and 4" << std::endl;
			break;
		}
	}
	return 0;
}
