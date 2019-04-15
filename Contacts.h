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
	void printAllContacts(); //this works for any tree
	void editContact(); //I think this should be in the GUI file with displayContact(). (There is no GUI file yet)
	void deleteContact(); //this can work for any tree because the algorithm is to replace the deleted node with the leftmost node from the right branch

	void displayContact(Contact* c); //temporary function; this should probably be in GUI and it should make data fields instead of printing.

	void addByName(); //add a contact to a tree organized by name
	void searchByName(); //currently finds all contacts with search term in the name and prints them out in in-order fashion
	Contact* contactByName(std::string name); //this is what we would use if we do tries to find the names and then choose 1 name to bring up the contact for.

	void addByNumber(); //add a contact to a tree organized by phone number
	void searchByNumber(); //print out all the contacts (print their name and phone number) with the search term anywhere in the phone number.
	//Contact* contactByNumber(std::string name); //this is what we would use if we do tries to find the phone numbers and then choose 1 number to bring up the contact for.

	/*
	void addByEmail(); //add a contact to a tree organized by email
	void searchByEmail(); //print out all the contacts (print their name and email) with the search term anywhere in the email.
	//Contact* contactByEmail(std::string name); //this is what we would use if we do tries to find the emails and then choose 1 email to bring up the contact for.
	*/

	void addByBday(); //add a contact to a tree organized by birthday
	void searchByBday(); //print out all the contacts (print their name and birthday) with the search term anywhere in the birthday.
	//Contact* contactByBday(std::string name); //this is what we would use if we do tries to find the birthdays and then choose 1 birthdays to bring up the contact for.

	void addByAddress(); //add a contact to a tree organized by phone number
	void searchByAddress(); //print out all the contacts (print their name and phone number) with the search term anywhere in the phone number.
	//Contact* contactByAddress(std::string name); //this is what we would use if we do tries to find the emails and then choose 1 email to bring up the contact for.

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

void toLowercase(std::string &x) { // takes a string, replaces it with lowercase of itself
	for (int i = 0; i < x.length(); i++) { // for every letter
		int ascii = x[i]; // ascii integer for letter
		if (ascii >= 'A' && ascii <= 'Z') { // if it's capital ascii, 'A' is the same as the ascii value
			ascii += 32; // add 32 to make lowercase
		}
		x[i] = ascii; // the letter is now this new ascii. Converts back to char from int.
	}
	return;
}

void inOrderSearch(treeNode* curr, std::string userInput) {
	if (curr == nullptr) {
		return;
	}
	inOrderSearch(curr->leftChild, userInput);
	std::string firstAndLastString = curr->c->firstName + curr->c->lastName;
	toLowercase(firstAndLastString);
	int currentIndex = 0;
	while (userInput.length() + currentIndex < firstAndLastString.length() + 1) { // for every 'spot' the search can fit into
		bool isMatch = true;
		for (int i = 0; i < userInput.length(); i++) {
			if (userInput[i] == firstAndLastString[currentIndex + i]) {
				std::cout << "userInput <" << userInput << "> at pos <" << i << "> equals the <" << firstAndLastString[currentIndex + i] << "> in string <" << firstAndLastString << ">" << std::endl;
			}
			else {
				isMatch = false;
				break; // stop comparing at this position if it's not a match
			}
		}
		currentIndex++;
		if (isMatch) {
			std::cout << "--[ " << firstAndLastString << " matches search term <" << userInput << "> ]--" << std::endl;
			break; // stop loop if it is a match, else repeating matches get caught twice
		}
	}
	inOrderSearch(curr->rightChild, userInput);
}

void Contacts::searchByName() {
	std::cout << "Type your search term: " << std::endl;
	std::string userInput = "";
	std::cin >> userInput; // doesn't support spaces yet
	toLowercase(userInput);
	inOrderSearch(root, userInput);
}

void Contacts::addByName() { // just asking for contact info first
	Contact* newContact = new Contact;
	treeNode* newNode = new treeNode;

	std::string input;
	std::cout << "What is the new contact's first name? : ";
	std::cin >> input;
	newContact->firstName = input;

	std::cout << "What is the new contact's last name? : ";
	std::cin >> input;
	newContact->lastName = input;

	std::cout << "What is the new contact's phone number? Enter in xxx-xxx-xxxx format : ";
	std::cin >> input;
	newContact->phoneNumber = input;

	std::cout << "What is the new contact's birthdate? Enter in mm/dd/yyyy form : ";
	std::cin >> input;
	newContact->birthdate = input;

	std::cout << "What is the new contact's address? : ";
	getline(std::cin, input); //clear the \n left over from the >>
	getline(std::cin, input); //actually get the address
	newContact->address = input;

	newNode->c = newContact; // puts the new contact onto the new tree node
	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl; //I moved this up here so it works with root also.
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
			std::cout << "(supposed to infinite loop since there's nothing else for it to do)" << std::endl;
		}
	}
	if (isLeft) {
		newNode->parent->leftChild = newNode; // K - reason for having parent
	}
	else {
		newNode->parent->rightChild = newNode;
	}

}


/* Return null if the contact is not found */
Contact* Contacts::contactByName(std::string input)
{
	std::string name;
	//transfer input to name with no spaces
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] != ' ')
		{
			name += input[i];
		}
	}
	toLowercase(name);

	treeNode* traverse = root;
	//go through in BST fashion until a matching full name is found.
	while(traverse != 0)
	{
		std::string firstlast = traverse->c->firstName + traverse->c->lastName;
		toLowercase(firstlast);
		if(name == firstlast)
		{
			return traverse->c;
		}
		else if(name < firstlast)
		{
			traverse = traverse->leftChild;
		}
		else
		{
			traverse = traverse->rightChild;
		}
	}

	std::cout << input << " does not exist in your contacts." << std::endl;
	return 0; //return nullptr if the name is not found.
}

void Contacts::editContact() {

}

void Contacts::deleteContact() {

}

//In the future, this will show every aspect of the contact on the GUI. This might actually just be another form of editContact.
void Contacts::displayContact(Contact* c)
{
	std::cout << "Showing information for Contact:" << std::endl;
	std::cout << "    First Name: "<< c->firstName << std::endl;
	std::cout << "    Last Name: " << c->lastName << std::endl;
	std::cout << "    Phone Number: " << c->phoneNumber << std::endl;
	std::cout << "    Birthday: " << c->birthdate << std::endl;
	std::cout << "    Address: " << c->address << std::endl;
}
