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