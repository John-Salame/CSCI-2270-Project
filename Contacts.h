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
	static Contact* createContact(); //create a contact from user input and return the pointer. Can be called as Contacts::createContact() instead of dot notation.
	void editContact(); //I think this should be in the GUI file with displayContact(). (There is no GUI file yet)
	void deleteContact(); //this can work for any tree because the algorithm is to replace the deleted node with the leftmost node from the right branch

	void displayContact(Contact* c); //temporary function; this should probably be in GUI and it should make data fields instead of printing.

	void addByFirstName(Contact* newContact); //add a contact to a tree organized by first name. LInked lists are alphabetical by last name.
	void searchByFirstName(); //currently finds all contacts with search term in the name and prints them out in in-order fashion

	void addByLastName(Contact* newContact); //add a contact to a tree organized by last name. Linked lists are alphabetical by first name.
	void searchByLastName(); //currently finds all contacts with search term in the name and prints them out in in-order fashion

	Contact* contactByName(std::string name); //pass in the full name of the contact and return the pointer to it.

	void addByNumber(Contact* newContact); //add a contact to a tree organized by phone number
	void searchByNumber(); //print out all the contacts (print their name and phone number) with the search term anywhere in the phone number.
	//Contact* contactByNumber(std::string name); //this is what we would use if we do tries to find the phone numbers and then choose 1 number to bring up the contact for.

	/*
	void addByEmail(); //add a contact to a tree organized by email
	void searchByEmail(); //print out all the contacts (print their name and email) with the search term anywhere in the email.
	//Contact* contactByEmail(std::string name); //this is what we would use if we do tries to find the emails and then choose 1 email to bring up the contact for.
	*/

	void addByBday(Contact* newContact); //add a contact to a tree organized by birthday
	void searchByBday(); //print out all the contacts (print their name and birthday) with the search term anywhere in the birthday.
	//Contact* contactByBday(std::string name); //this is what we would use if we do tries to find the birthdays and then choose 1 birthdays to bring up the contact for.

	void addByAddress(Contact* newContact); //add a contact to a tree organized by phone number
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

//static function, called with Contacts::createContact() instead of iCloud.createContact()
Contact* Contacts::createContact()
{
	Contact* newContact = new Contact;

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

	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl; //I moved this up here so it works with root also.

	return newContact;
} //end of createContact function


void toLowercase(std::string x) {
std::string toLowercase(std::string x) { // takes a string, replaces it with lowercase of itself
	for (int i = 0; i < x.length(); i++) { // for every letter
		int ascii = x[i]; // ascii integer for letter
		if (ascii >= 'A' && ascii <= 'Z') { // if it's capital ascii, 'A' is the same as the ascii value
			ascii += 32; // add 32 to make lowercase
		}
		x[i] = ascii; // the letter is now this new ascii. Converts back to char from int.
	}
	return x; // returns back the string
}

void inOrderSearch(treeNode* curr, std::string userInput) {
	if (curr == nullptr) {
		return;
	}
	inOrderSearch(curr->leftChild, userInput);

	std::string lowerSearchInput = toLowercase(userInput);
	std::string lowerFirst = toLowercase(curr->c->firstName); // searches firstName
	std::string lowerLast = toLowercase(curr->c->lastName); // lowercase lastName
	std::string lowerAddress = toLowercase(curr->c->address); // lowercase address

	int x = 0;
	bool found = false;

	while (x < lowerSearchInput.length() && x < lowerFirst.length()) {
		if (lowerSearchInput[x] != lowerFirst[x]) {
			break;
		}
		x++;
	}
	if (x == lowerSearchInput.length()) {
		found = true;
	}
	x = 0;
	while (x < lowerSearchInput.length() && x < lowerLast.length() && !found) { // don't need to search if found already within contact
		if (lowerSearchInput[x] != lowerLast[x]) {
			break;
		}
		x++;
	}
	if (x == lowerSearchInput.length()) {
		found = true;
	}
	x = 0;
	while (x < lowerSearchInput.length() && x < lowerAddress.length() && !found) {
		if (lowerSearchInput[x] != lowerAddress[x]) {
			break;
		}
		x++;
	}
	if (x == lowerSearchInput.length()) {
		found = true;
	}
	x = 0;
	
	if (found) {
		std::cout << curr->c->firstName << " " << curr->c->lastName << " " << curr->c->address << std::endl;
	}
	inOrderSearch(curr->rightChild, userInput);
}

void Contacts::searchByFirstName() {
	std::cout << "Type your search term: " << std::endl;
	std::string userInput = "";
	std::cin >> userInput; // doesn't support spaces yet
	toLowercase(userInput);
	inOrderSearch(root, userInput);
}

void Contacts::addByFirstName(Contact* newContact) { // just asking for contact info first
	treeNode* newNode = new treeNode;
	newNode->c = newContact; // puts the new contact into the new tree node

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
	name = toLowercase(name);

	treeNode* traverse = root;
	//go through in BST fashion until a matching full name is found.
	while(traverse != 0)
	{
		std::string firstlast = traverse->c->firstName + traverse->c->lastName;
		firstlast = toLowercase(firstlast);
		
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
