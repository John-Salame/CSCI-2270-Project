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

	treeNode* leftChild = nullptr; // if organized by name, this name is less than the current name
	treeNode* rightChild = nullptr; // if organized by name, this name is greater than the current name
	treeNode* parent = nullptr; // K - easier to delete contacts I think
	Contact c; // contact information located at tree pos

};

class Contacts {
public:
	Contacts();
	void printAllContacts();
	void searchContact();
	void addContact();
	void editContact();
	void deleteContact();

private:
	treeNode* root; // root of the treeNode
};

Contacts::Contacts() {
	root = nullptr; // initializes root as nullptr
}

void inOrder(treeNode* curr) {
	if (curr == nullptr) {
		return;
	}
	inOrder(curr->leftChild);
	std::cout << "-" << curr->c.name << " - " << curr->c.phoneNumber << std::endl; // simple print name / phone number
	inOrder(curr->rightChild);
}

void Contacts::printAllContacts() { // prints all of the contacts in the tree.
	inOrder(root);
}

void Contacts::searchContact() {

}

void Contacts::addContact() { // just asking for contact info first
	Contact newContact;
	treeNode* newNode = new treeNode;

	std::string input;
	std::cout << "What is the new contacts name? : ";
	std::cin >> input;
	newContact.name = input;
	newNode->c = newContact; // puts the new contact onto the new tree node
	// actually adding to the tree now, again alphabetically.
	if (root == nullptr) {
		root = newNode;
		return;
	}

	treeNode* parse = root;
	bool isLeft = false;

	while (parse != nullptr) { // puts the parse at the end of the tree
		newNode->parent = parse;
		if (parse->c.name < newNode->c.name) { // comparing to a name less than the new name
			parse = parse->leftChild;
			isLeft = true;
		}
		else if (parse->c.name > newNode->c.name) { // comparing to a name greater than the new name
			parse = parse->rightChild;
			isLeft = false;
		}
		else if (parse->c.name == newNode->c.name) {
			std::cout << "Name is the same as another name in the tree, not programmed yet." << std::endl;
		}
	}
	if (isLeft) {
		newNode->parent->leftChild = newNode;
	}
	else {
		newNode->parent->rightChild = newNode;
	}

	std::cout << std::endl << "Added " << input << " to your contact list!" << std::endl;
}

void Contacts::editContact() {

}

void Contacts::deleteContact() {

}