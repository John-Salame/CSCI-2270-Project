#include <iostream>
#include <string>

struct Contact { // actual contact

	std::string firstName = ""; // EX: Kyran
	std::string lastName = ""; // EX: Butler
	std::string phoneNumber = ""; // EX: 303-303-3003
	std::string birthdate = ""; // EX: 04-06-2001 
	std::string address = ""; // EX: 50181 South Street, Denver, Colorado

};

struct treeNode { // used to build tree of contacts, built as if the tree is organized by first name alphabatized right now

	treeNode* leftChild = nullptr; // if organized by name, this name is less than the current name
	treeNode* rightChild = nullptr; // if organized by name, this name is greater than the current name
	treeNode* parent = nullptr; // K - easier to delete contacts I think
	Contact* c; // contact information located at tree pos

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

void inOrder(treeNode* curr) { // prints all entries inOrder.
	if (curr == nullptr) {
		return;
	}
	inOrder(curr->leftChild);
	if (curr->c->firstName == "") {
		std::cout << "<emptyFirstName> ";
	}
	else {
		std::cout << "- " << curr->c->firstName << " ";
	}
	if (curr->c->lastName == "") {
		std::cout << "<emptyLastName> ";
	}
	else {
		std::cout << "- " << curr->c->lastName << " ";
	}
	if (curr->c->phoneNumber == "") {
		std::cout << "<emptyPhoneNumber> ";
	}
	else {
		std::cout << "- " << curr->c->phoneNumber << " ";
	}
	std::cout << std::endl;
	inOrder(curr->rightChild);
}

void Contacts::printAllContacts() { // prints all of the contacts in the tree.
	inOrder(root);
}

void inOrderSearch(treeNode* curr, std::string userInput, Contact* searchHead) {
	if (curr == nullptr) {
		return;
	}
	inOrderSearch(curr->leftChild, userInput, searchHead);
	// traverse to compare string userInput to spots in the word
	std::string firstAndLastString = curr->c->firstName + curr->c->lastName;
	int currentIndex = 0;
	while (userInput.length() + currentIndex < firstAndLastString.length() - 1) { // for every 'spot' the search can fit into
		// check all the letters of userInput with the current spot in firstAndLastString
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[i] == firstAndLastString[currentIndex + i]) {
				std::cout << "userInput <" << userInput << "> at pos <" << i << "> equals the <" << firstAndLastString[currentIndex + i] << "> in string <" << firstAndLastString << ">" << std::endl;
			}
		}
		currentIndex++;
		std::cout << "currentIndex length is " << currentIndex << std::endl;;
	}



	inOrderSearch(curr->rightChild, userInput, searchHead);
}

void Contacts::searchContact() {
	std::cout << "Type your search term: " << std::endl;
	// enter a string
	std::string userInput = "";
	std::cin >> userInput;
	// inorder traversal
	Contact* searchHead = nullptr;
	inOrderSearch(root, userInput, searchHead);
	// at each step, traverse each letter to find that string
	
	// if found, add to a linked list of contacts
	// print that ll with options to select
}

void Contacts::addContact() { // just asking for contact info first
	Contact* newContact = new Contact;
	treeNode* newNode = new treeNode;

	std::string input;
	std::cout << "What is the new contacts first name? : ";
	std::cin >> input;
	newContact->firstName = input;
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
		if (parse->c->firstName < newNode->c->firstName) { // comparing to a name less than the new name
			parse = parse->rightChild;
			isLeft = false;
		}
		else if (parse->c->firstName > newNode->c->firstName) { // comparing to a name greater than the new name
			parse = parse->leftChild;
			isLeft = true;
		}
		else if (parse->c->firstName == newNode->c->firstName) {
			std::cout << "Name is the same as another name in the tree, not programmed yet." << std::endl;
		}
	}
	if (isLeft) {
		newNode->parent->leftChild = newNode; // K - reason for having parent
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