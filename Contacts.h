#include <iostream>
#include <string>
#include <vector>

struct Contact { // actual contact

	std::string firstName = ""; // EX: Kyran
	std::string lastName = ""; // EX: Butler
	std::string phoneNumber = ""; // EX: 303-303-3003
	std::string birthdate = ""; // EX: 04-06-2001
	std::string address = ""; // EX: 50181 South Street, Denver, Colorado
	std::string email = ""; // EX: kyran@butlerhq.com

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
	void createContact(); //create a contact from user input and return the pointer. Can be called as Contacts::createContact() instead of dot notation.
	void editContact(Contact* editThis); //I think this should be in the GUI file with displayContact(). (There is no GUI file yet)
	void deleteContact(); //this can work for any tree because the algorithm is to replace the deleted node with the leftmost node from the right branch

	void search();
	void searchByFirstName(std::string userInput);
	void searchByLastName(std::string userInput);
	void searchByBirthdate(std::string userInput);
	void addToSearchResults(treeNode* pointer);
	void clearSearchResults();

	void displayDetailedContact(Contact* c); //temporary function; this should probably be in GUI and it should make data fields instead of printing.

	void addToFirstTree(treeNode* c);
	void addToLastTree(treeNode* c);
	void addToBirthTree(treeNode* c);

private:
	// the 'print all' tree is currently sorted by:
	treeNode* currentlySortedBy;
	treeNode* firstNameRoot; // root of the tree sorted by first names
	treeNode* lastNameRoot; // root of the tree sorted by last names
	treeNode* birthdateRoot; // root of the tree sorted by birthday -> can make more of these easily
	std::vector<treeNode*> searchResults;
};
 //// //// /////
 //// CONSTRUCTOR
Contacts::Contacts() {
	currentlySortedBy = nullptr; // initializes root as nullptr
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
	std::cout << std::endl;
	printInOrder(curr->rightChild);
}

void Contacts::printAllContacts() { // prints all of the contacts in the tree.
	printInOrder(currentlySortedBy);
}

//In the future, this will show every aspect of the contact on the GUI. This might actually just be another form of editContact.
void Contacts::displayDetailedContact(Contact* c){
	std::cout << "Showing information for Contact:" << std::endl;
	std::cout << "    First Name: "<< c->firstName << std::endl;
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

void Contacts::searchByFirstName(std::string userInput) {  // goes through firstName tree
	treeNode* parse = firstNameRoot;
	if (parse == nullptr) {
		return;
	}
	while (parse != nullptr) {
		if (parse->c->firstName < userInput) {
			parse = parse->rightChild;
		}
		else if (parse->c->firstName > userInput) {
			parse = parse->leftChild;
		}
		else {
			addToSearchResults(parse);
			return;
		}
	}
}

void Contacts::searchByLastName(std::string userInput) { // goes through lastName tree
	treeNode* parse = lastNameRoot;
	if (parse == nullptr) {
		return;
	}
	while (parse != nullptr) {
		if (parse->c->lastName < userInput) {
			parse = parse->rightChild;
		}
		else if (parse->c->lastName > userInput) {
			parse = parse->leftChild;
		}
		else {
			addToSearchResults(parse);
			return;
		}
	}
} 

void Contacts::searchByBirthdate(std::string userInput) { // goes through birthdate tree
	treeNode* parse = birthdateRoot;
	if (parse == nullptr) {
		return;
	}
	while (parse != nullptr) {
		if (parse->c->birthdate < userInput) {
			parse = parse->rightChild;
		}
		else if (parse->c->birthdate > userInput) {
			parse = parse->leftChild;
		}
		else {
			addToSearchResults(parse);
			return;
		}
	}
}

void Contacts::addToSearchResults(treeNode* pointer) {
	for (int i = 0; i < searchResults.size(); i++) {
		if (searchResults[i] == pointer) {
			return;
		}
	}
	searchResults.push_back(pointer);
}

void Contacts::clearSearchResults() {
	for (int i = 0; i < searchResults.size(); i++) {
		searchResults.pop_back();
	}
}

void Contacts::search() {
	std::cout << "Type your search term: " << std::endl;
	std::string userInput = "";
	std::cin >> userInput; // doesn't support spaces yet
	userInput = toLowercase(userInput);
	clearSearchResults();
	searchByFirstName(userInput);
	searchByLastName(userInput);
	searchByBirthdate(userInput);
	if (searchResults.size() == 0) {
		std::cout << "No contacts were found!" << std::endl;
	}
	else {
		for (int i = 0; i < searchResults.size(); i++) {
			std::cout << i << ") " << searchResults[i]->c->firstName << " " << searchResults[i]->c->lastName << std::endl;;
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
		else if (toLowercase(parse->c->firstName) < toLowercase(given->c->firstName)){ // comparing to a name greater than the new name
			parse = parse->rightChild; 
			isLeft = false;
		}
		else if (toLowercase(parse->c->lastName) == toLowercase(given->c->lastName)) {
			if(toLowercase(parse->c->lastName) > toLowercase(given->c->lastName)){
				parse = parse->leftChild;
				isLeft = true;
			}
			else { // if the new name is equal to OR greater than, it goes to the right child.
				parse = parse->rightChild;
				isLeft = false;
			}
		}
	}
	if (isLeft) {
		given->parent->leftChild = parse; // K - reason for having parent
	}
	else {
		given->parent->rightChild = parse;
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
		else if (toLowercase(parse->c->lastName) < toLowercase(given->c->lastName)){ // comparing to a name greater than the new name
			parse = parse->rightChild; 
			isLeft = false;
		}
		else if (toLowercase(parse->c->lastName) == toLowercase(given->c->lastName)) {
			if(toLowercase(parse->c->lastName) > toLowercase(given->c->lastName)){
				parse = parse->leftChild;
				isLeft = true;
			}
			else { // if the new name is equal to OR greater than, it goes to the right child.
				parse = parse->rightChild;
				isLeft = false;
			}
		}
	}
	if (isLeft) {
		given->parent->leftChild = parse; // K - reason for having parent
	}
	else {
		given->parent->rightChild = parse;
	}
} // done.

void Contacts::addToBirthTree(treeNode* given) { 
	if (birthdateRoot == nullptr) {
		birthdateRoot = given;
		return;
	}
	treeNode* parse = firstNameRoot;
	bool isLeft = true;
	while (parse != nullptr) {
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
		given->parent->leftChild = parse; // K - reason for having parent
	}
	else {
		given->parent->rightChild = parse;
	}
}

void Contacts::createContact(){
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

	treeNode* firstNode;
	treeNode* lastNode;
	treeNode* birthNode;
	firstNode->c = newContact;
	lastNode->c = newContact;
	birthNode->c = newContact;

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);

	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl; //I moved this up here so it works with root also.
} //end of createContact function

 //// //// ////
 //// EDITING
void Contacts::editContact(Contact* editThis) {

}

//helper function for deleteContact(); del is the treeNode to delete. this will only be called if del exists.
treeNode* findReplacement(treeNode* del)
{
	treeNode* traverse = del;

	if(del->rightChild == 0 && del->leftChild == 0)
	{
		return 0;
	}
	else if(del->rightChild != 0) //del has a rightChild
	{
		traverse = traverse->rightChild; //start in right branch and find the leftmost leaf during the while loop
	}
	else //no right child; replace del with its leftChild
	{
		return del->leftChild;
	}

	while(traverse->leftChild != 0)
	{
		traverse = traverse->leftChild;
	}

	return traverse;
}

void Contacts::deleteTreeNode(treeNode* del) {
	//edge case: tree is empty or del does not exist
	if(del == 0)
	{
		std::cout << "Nothing to delete." << std::endl;
		return;
	}

	treeNode* rep = findReplacement(del); //leftmost leaf of the right child of del (or the left branch if rightChild is null), or null if del has no children

	if(del->parent == 0) //root is being deleted
	{
		root = rep;
	}

	if(rep != 0)
	{
		//make the parent of rep stop pointing to it.
		if(rep != del->leftChild && rep == rep->parent->leftChild) //rep is a left child. This is necessary if rep is in the middle of the right branch
		{
			rep->parent->leftChild = rep->rightChild;
		}
		else if(rep == rep->parent->rightChild) //rep is a right child (this should only happen if rep is the child of what we are deleting)
		{
			del->rightChild = rep->rightChild;
		}


		//put the replacement contact where the soon-to-be-deleted contact was.
		rep->parent = del->parent;
		if(rep != del->leftChild)
		{
			rep->leftChild = del->leftChild;
			rep->rightChild = del->rightChild;
		}
	}

	//make the parent of del point to rep (or null if rep doesn't exist)
	if(del->parent != 0)
	{
		if(del == del->parent->leftChild) //del is a left child
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
