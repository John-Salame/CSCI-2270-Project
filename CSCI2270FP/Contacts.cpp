#include "Contacts.h"

Contacts::Contacts() {
	*currentlySortedBy = nullptr; // initializes root as nullptr
	firstNameRoot = nullptr;
	lastNameRoot = nullptr;
	birthdateRoot = nullptr;
}

//// //// /////
//// PRINTING
void printInOrder(treeNode* curr) { // prints all entries inOrder based on which root is given to it.
	if (curr == nullptr) {
		return;
	}
	printInOrder(curr->leftChild);
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
	if (curr->c->birthdate == "") {
		std::cout << "<emptyBirthdate> ";
	}
	else {
		std::cout << "- " << curr->c->birthdate << " ";
	}
	std::cout << std::endl;
	printInOrder(curr->rightChild);
}

void Contacts::printAllContacts() { // prints all of the contacts in the tree.
	std::cout << "By First Name -- " << std::endl;
	printInOrder(firstNameRoot);
	std::cout << "By Last Name -- " << std::endl;
	printInOrder(lastNameRoot);
	std::cout << "By Birthdate hehe --" << std::endl;
	printInOrder(birthdateRoot);
}

//In the future, this will show every aspect of the contact on the GUI. This might actually just be another form of editContact.
void Contacts::displayDetailedContact(Contact* c) {
	std::cout << "Showing information for Contact:" << std::endl;
	std::cout << "    First Name: " << c->firstName << std::endl;
	std::cout << "    Last Name: " << c->lastName << std::endl;
	std::cout << "    Phone Number: " << c->phoneNumber << std::endl;
	std::cout << "    Birthday: " << c->birthdate << std::endl;
	std::cout << "    Address: " << c->address << std::endl;
}

//// //// ////
//// UTILITIES
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

//// //// /////
//// SEARCHING


//nodeSub and userInput are both lowercase
void Contacts::searchByFirstName(std::string userInput, treeNode* parse) {  // goes through firstName tree

	if (parse == 0) {
		return;
	}

	int len = userInput.length();

	std::string nodeSub = toLowercase(parse->c->firstName.substr(0, len));

	//only go left if the current node's first name is not < search term
	if (parse->leftChild != 0 && nodeSub >= userInput)
	{
		searchByFirstName(userInput, parse->leftChild);
	}

	//in-order: instead of printing, add to vector
	if (nodeSub == userInput)
	{
		searchResults.push_back(parse);
	}

	//only go right if the current node's first name is not > search term
	if (parse->rightChild != 0 && nodeSub <= userInput)
	{
		searchByFirstName(userInput, parse->rightChild);
	}
} //end of searchByFirstName

void Contacts::searchByLastName(std::string userInput, treeNode* parse) { // goes through lastName tree

	if (parse == 0) {
		return;
	}

	int len = userInput.length();

	std::string nodeSub = toLowercase(parse->c->lastName.substr(0, len));

	//only go left if the current node's first name is not < search term
	if (parse->leftChild != 0 && nodeSub >= userInput)
	{
		searchByLastName(userInput, parse->leftChild);
	}

	//in-order: instead of printing, add to vector
	if (nodeSub == userInput)
	{
		searchResults.push_back(parse);
	}

	//only go right if the current node's first name is not > search term
	if (parse->rightChild != 0 && nodeSub <= userInput)
	{
		searchByLastName(userInput, parse->rightChild);
	}

} //end of searchByLastName

void Contacts::searchByBirthdate(std::string userInput, treeNode* parse) { // goes through birthdate tree

	if (parse == 0) {
		return;
	}

	int len = userInput.length();

	std::string nodeSub = toLowercase(parse->c->birthdate.substr(0, len));

	//only go left if the current node's first name is not < search term
	if (parse->leftChild != 0 && nodeSub >= userInput)
	{
		searchByBirthdate(userInput, parse->leftChild);
	}

	//in-order: instead of printing, add to vector
	if (nodeSub == userInput)
	{
		searchResults.push_back(parse);
	}

	//only go right if the current node's first name is not > search term
	if (parse->rightChild != 0 && nodeSub <= userInput)
	{
		searchByBirthdate(userInput, parse->rightChild);
	}

} //end of searchByBirthdate

void Contacts::addToSearchResults(treeNode* pointer) {
	for (int i = 0; i < searchResults.size(); i++) {
		if (searchResults[i]->c == pointer->c) {
			return;
		}
	}
	searchResults.push_back(pointer);
}

void Contacts::clearSearchResults() {
	while (searchResults.size() > 0) {
		searchResults.pop_back();
	}
}

void Contacts::search() {
	std::cout << "Type your search term. Please do not type full name: " << std::endl;
	std::string userInput = "";
	std::cin >> userInput;
	//remove spaces
	std::string noSpaces = "";
	for (int i = 0; i < userInput.length(); i++)
	{
		if (userInput[i] != ' ')
		{
			noSpaces += userInput[i];
		}
	}
	userInput = toLowercase(userInput);
	clearSearchResults();

	searchByFirstName(userInput, firstNameRoot);
	searchByLastName(userInput, lastNameRoot);
	searchByBirthdate(userInput, birthdateRoot);

	if (searchResults.size() == 0) {
		std::cout << "No contacts were found!" << std::endl;
	}
	else {
		std::string x = "100";
		for (int i = 0; i < searchResults.size(); i++) {
			std::cout << i << ") " << searchResults[i]->c->firstName << " " << searchResults[i]->c->lastName << std::endl;
		}
		//input an option to go to main menu, edit, or delete
		while (stoi(x) > searchResults.size() || stoi(x) < 0) {
			std::cout << "Selection: ";
			std::cin >> x;
			if (stoi(x) > searchResults.size() || stoi(x) < 0) {
				std::cout << "Not a valid selection! Choose between 0 and " << searchResults.size() << std::endl;
			}
			displayDetailedContact(searchResults[stoi(x)]->c);
			std::cout << "0) Main Menu, 1) Edit, 2) Delete :";
			std::string y = "100";
			while (stoi(y) > 2 || stoi(y) < 0) {
				std::cout << "Selection: ";
				std::cin >> y;
				if (stoi(y) > 2 || stoi(y) < 0) {
					std::cout << "Not a valid selection! Choose between 0 and 2" << std::endl;
				}
			}
			if (stoi(y) == 0) { // user chose to go back to main menu
				return;
			}
			if (stoi(y) == 1) { // user chose to edit the contact selected
				editContact(searchResults[stoi(x)]->c);
				return;
			}
			if (stoi(y) == 2) { // user chose to delete the contact
				Contact* c = searchResults[stoi(x)]->c;

				currentlySortedBy = &firstNameRoot;
				deleteTreeNode(c->firstTreePointer);
				currentlySortedBy = &lastNameRoot;
				deleteTreeNode(c->lastTreePointer);
				currentlySortedBy = &birthdateRoot;
				deleteTreeNode(c->birthTreePointer);

				delete c; //finally, delete the Contact*

				currentlySortedBy = &firstNameRoot;

				return;
			}
		}
		// working on next, they select one to do. it calls displayDetailedContact. Then the user can edit / delete it.
	}
}

//// //// /////
//// CREATING

void Contacts::addToFirstTree(treeNode* given) {
	if (firstNameRoot == nullptr) {
		firstNameRoot = given;
		return;
	}
	treeNode* parse = firstNameRoot;
	bool isLeft = true;
	while (parse != nullptr) {
		given->parent = parse;
		if (toLowercase(parse->c->firstName) > toLowercase(given->c->firstName)) { // comparing to a name less than the new name
			parse = parse->leftChild;
			isLeft = true;
		}
		else if (toLowercase(parse->c->firstName) < toLowercase(given->c->firstName)) { // comparing to a name greater than the new name
			parse = parse->rightChild;
			isLeft = false;
		}
		else { // if the new name is equal, decide to go left or right (right if last name is >= parse)
			if (toLowercase(parse->c->lastName) > toLowercase(given->c->lastName)) { // comparing to a name less than the new name
				parse = parse->leftChild;
				isLeft = true;
			}
			else { //last name >= parse
				parse = parse->rightChild;
				isLeft = false;
			}
		}
	}
	if (isLeft) {
		given->parent->leftChild = given; // K - reason for having parent
	}
	else {
		given->parent->rightChild = given;
	}
} // done.

void Contacts::addToLastTree(treeNode* given) {
	if (lastNameRoot == nullptr) {
		lastNameRoot = given;
		return;
	}
	treeNode* parse = lastNameRoot;
	bool isLeft = true;
	while (parse != nullptr) {
		given->parent = parse;
		if (toLowercase(parse->c->lastName) > toLowercase(given->c->lastName)) { // comparing to a name less than the new name
			parse = parse->leftChild;
			isLeft = true;
		}
		else if (toLowercase(parse->c->lastName) < toLowercase(given->c->lastName)) { // comparing to a name greater than the new name
			parse = parse->rightChild;
			isLeft = false;
		}
		else if (toLowercase(parse->c->lastName) == toLowercase(given->c->lastName)) {
			if (toLowercase(parse->c->lastName) > toLowercase(given->c->lastName)) {
				parse = parse->leftChild;
				isLeft = true;
			}
			else { // if the new name is equal, check first name. First name >= goes right.
				if (toLowercase(parse->c->firstName) > toLowercase(given->c->firstName)) { // comparing to a name less than the new name
					parse = parse->leftChild;
					isLeft = true;
				}
				else { // comparing to a name greater than the new name
					parse = parse->rightChild;
					isLeft = false;
				}
			}
		}
	}
	if (isLeft) {
		given->parent->leftChild = given; // K - reason for having parent
	}
	else {
		given->parent->rightChild = given;
	}
} // done.

void Contacts::addToBirthTree(treeNode* given) {
	if (birthdateRoot == nullptr) {
		birthdateRoot = given;
		return;
	}
	treeNode* parse = birthdateRoot;
	bool isLeft = true;
	while (parse != nullptr) {
		given->parent = parse;
		if (parse->c->birthdate > given->c->birthdate) {
			parse = parse->leftChild;
			isLeft = true;
		}
		else {
			parse = parse->rightChild;
			isLeft = false;
		}
	}
	if (isLeft) {
		given->parent->leftChild = given; // K - reason for having parent
	}
	else {
		given->parent->rightChild = given;
	}
}

void Contacts::createContact() {
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

	treeNode* firstNode = new treeNode;
	treeNode* lastNode = new treeNode;
	treeNode* birthNode = new treeNode;

	firstNode->c = newContact;
	lastNode->c = newContact;
	birthNode->c = newContact;

	newContact->firstTreePointer = firstNode;
	newContact->lastTreePointer = lastNode;
	newContact->birthTreePointer = birthNode;

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);
	currentlySortedBy = &firstNameRoot; //point to the firstNameRoot pointer
	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl;
}


void Contacts::createContact(std::string firstName, std::string lastName, std::string phoneNumber, std::string birthdate, std::string address, std::string email)
{
	Contact* newContact = new Contact;

	newContact->firstName = firstName;
	newContact->lastName = lastName;
	newContact->phoneNumber = phoneNumber;
	newContact->birthdate = birthdate;
	newContact->address = address;
	newContact->email = email;

	treeNode* firstNode = new treeNode;
	treeNode* lastNode = new treeNode;
	treeNode* birthNode = new treeNode;

	firstNode->c = newContact;
	lastNode->c = newContact;
	birthNode->c = newContact;

	newContact->firstTreePointer = firstNode;
	newContact->lastTreePointer = lastNode;
	newContact->birthTreePointer = birthNode;

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);
	currentlySortedBy = &firstNameRoot; //point to the firstNameRoot pointer
	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl;
}


//// //// ////
//// EDITING
void Contacts::editContact(Contact* editThis) {

}

//helper function for deleteContact(); del is the treeNode to delete. this will only be called if del exists.
treeNode* findReplacement(treeNode* del)
{
	treeNode* traverse = del;

	if (del->rightChild == 0 && del->leftChild == 0)
	{
		return 0;
	}
	else if (del->rightChild != 0) //del has a rightChild
	{
		traverse = traverse->rightChild; //start in right branch and find the leftmost leaf during the while loop
	}
	else //no right child; replace del with its leftChild
	{
		return del->leftChild;
	}

	while (traverse->leftChild != 0)
	{
		traverse = traverse->leftChild;
	}

	return traverse;
}

void Contacts::deleteTreeNode(treeNode* del) {
	//edge case: tree is empty or del does not exist
	if (del == 0)
	{
		std::cout << "Nothing to delete." << std::endl;
		return;
	}

	treeNode* rep = findReplacement(del); //leftmost leaf of the right child of del (or the left branch if rightChild is null), or null if del has no children

	if (del->parent == 0) //root is being deleted
	{
		*currentlySortedBy = rep;
	}

	if (rep != 0)
	{
		//make the parent of rep stop pointing to it.
		if (rep != del->leftChild && rep == rep->parent->leftChild) //rep is a left child. This is necessary if rep is in the middle of the right branch
		{
			rep->parent->leftChild = rep->rightChild;
		}
		else if (rep == rep->parent->rightChild) //rep is a right child (this should only happen if rep is the child of what we are deleting)
		{
			del->rightChild = rep->rightChild;
		}


		//put the replacement contact where the soon-to-be-deleted contact was.
		rep->parent = del->parent;
		if (rep != del->leftChild)
		{
			rep->leftChild = del->leftChild;
			rep->rightChild = del->rightChild;
		}
	}

	//make the parent of del point to rep (or null if rep doesn't exist)
	if (del->parent != 0)
	{
		if (del == del->parent->leftChild) //del is a left child
		{
			del->parent->leftChild = rep;
		}
		else //del is a right child
		{
			del->parent->rightChild = rep;
		}
	}

	//delete del whether or not there is a replacement. Make del stop pointing to things in case anything in another part of the program is still pointing to del.
	del->parent = 0;
	del->leftChild = 0;
	del->rightChild = 0;
	delete del;
	del = 0;
}


//ACCESSOR METHODS
treeNode* Contacts::treeHead()
{
	return *currentlySortedBy;
}
void Contacts::changeToFirstNames()
{
	currentlySortedBy = &firstNameRoot;
}
void Contacts::changeToLastNames()
{
	currentlySortedBy = &lastNameRoot;
}
void Contacts::changeToPhoneNumbers()
{
	//NOTHING YET
}
void Contacts::changeToBirthdates()
{
	currentlySortedBy = &birthdateRoot;
}
void Contacts::changeToAddresses()
{
	//NOTHING YET
}
void Contacts::changeToEmails()
{
	//NOTHING YET
}
std::vector<treeNode*> Contacts::getSearchResults()
{
	return searchResults;
}