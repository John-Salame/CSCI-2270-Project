#include "Contacts.h"
#include <afx.h>
#include <fstream>
#include <sstream>

//Constructor
Contacts::Contacts() {
	firstNameRoot = nullptr; // root of the tree sorted by first name
	lastNameRoot = nullptr; // root of the tree sorted by last name
	birthdateRoot = nullptr; // root of the tree sorted by birthdate
	currentlySortedBy = &firstNameRoot; //point to the firstNameRoot pointer so we sort by first names when we start the program
}

//Delete everything from every tree
void Contacts::deleteEverything() {
	while (firstNameRoot != 0) {

		/** While the root of the first name tree (meaning all of the trees) isn't null,
		delete the contact by telling deleteFromAllTrees to delete the contact located at
		the root*/

		deleteFromAllTrees(firstNameRoot->c, true);
	}
}

//Destructor
Contacts::~Contacts() {
	deleteEverything(); // calls deleteEverything
}

//// //// /////
//// PRINTING
void printInOrder(treeNode* curr) { // prints all entries inOrder based on which root is given to it.

	/** function prints all of the contacts currently stored based on
	which tree the data is currently being sorted by. This is irrelevant
	in the final program, as the final doesn't use printing (since this
	is for command line only)*/

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
	printInOrder(firstNameRoot); // Called with the first name root so it prints out by first name
	std::cout << "By Last Name -- " << std::endl;
	printInOrder(lastNameRoot); // Called with the last name root so it prints out by last name
	std::cout << "By Birthdate hehe --" << std::endl;
	printInOrder(birthdateRoot); // Called with the birthdate root so it prints out by birthdate
}

//In the future, this will show every aspect of the contact on the GUI. This might actually just be another form of editContact.
void Contacts::displayDetailedContact(Contact* c) { // When this is called, detailed information is displayed. Not neccessary for GUI.
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

void inOrderSave(treeNode* curr, std::ofstream& saveStream) {
	/**This is the saving function. It traverses the firstname tree recursively,
	and writes the information to a file called saveFile.csv (saveStream ofstream)

	An entry looks like this:  First*Last*PhoneNum*Birthdate*Address*e-mail

	*/

	if (curr == nullptr) {
		return;
	}
	inOrderSave(curr->leftChild, saveStream);
	if (curr->c->firstName == "") {
		saveStream << "<emptyfirstName>";
	}
	else {
		saveStream << curr->c->firstName;
	}
	saveStream << "*";
	if (curr->c->lastName == "") {
		saveStream << "<emptyLastName>";
	}
	else {
		saveStream << curr->c->lastName;
	}
	saveStream << "*";
	if (curr->c->phoneNumber == "") {
		saveStream << "<emptyPhoneNumber>";
	}
	else {
		saveStream << curr->c->phoneNumber;
	}
	saveStream << "*";
	if (curr->c->birthdate == "") {
		saveStream << "<emptyBirthdate>";
	}
	else {
		saveStream << curr->c->birthdate;
	}
	saveStream << "*";
	if (curr->c->address == "") {
		saveStream << "<emptyAddress>";
	}
	else {
		saveStream << curr->c->address;
	}
	saveStream << "*";
	if (curr->c->email == "") {
		saveStream << "<emptyEmail>";
	}
	else {
		saveStream << curr->c->email;
	}

	saveStream << std::endl;
	inOrderSave(curr->rightChild, saveStream);
}

bool Contacts::saveAllToFile(std::string fileName) {
	std::ofstream saveStream; // saveStream
	saveStream.open("savefile.csv"); // opens savefile.csv
	if (saveStream.is_open()) { // if the ofstream was successfully opened
		inOrderSave(firstNameRoot, saveStream);
	}
	else {
		return false; // save stream couldn't be opened. (file might not exist)
	}
	saveStream.close(); // closes the ofstream
	return true;
}

bool Contacts::loadAllFromFile() {
	/*simply reads file line by line, places the split words
	into the different variables, then the variables are used
	as parameters to create a new contact.*/

	std::string line;
	std::string splitWord;

	std::stringstream s;
	int x = 1;

	// first last phone birthdate address email

	std::ifstream iS;
	iS.open("savefile.csv");
	if (iS.is_open()) {
		while (getline(iS, line)) {
			std::string firstName = "";
			std::string lastName = "";
			std::string phoneNum = "";
			std::string birthdate = "";
			std::string address = "";
			std::string email = "";
			s.clear();
			s << line;
			while (getline(s, splitWord, '*')) {
				if (splitWord[0] == '<') {
					if (x == 6) {
						x = 1;
					}
					else {
						x++;
					}
				}
				else {
					switch (x) {
					case 1:
						firstName = splitWord;
						x++;
						break;
					case 2:
						lastName = splitWord;
						x++;
						break;
					case 3:
						phoneNum = splitWord;
						x++;
						break;
					case 4:
						birthdate = splitWord;
						x++;
						break;
					case 5:
						address = splitWord;
						x++;
						break;
					case 6:
						email = splitWord;
						x = 1;
						break;
					}
				}
			}
			createContact(firstName, lastName, phoneNum, birthdate, address, email);
		}
	}
	else {
		return false; // returns false if file can't be loaded in.
	}
	iS.close();
	return true; // returns true if file was loaded in successfully.
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
		addToSearchResults(parse);
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

	//only go left if the current node's last name is not < search term
	if (parse->leftChild != 0 && nodeSub >= userInput)
	{
		searchByLastName(userInput, parse->leftChild);
	}

	//in-order: instead of printing, add to vector
	if (nodeSub == userInput)
	{
		addToSearchResults(parse);
	}

	//only go right if the current node's last name is not > search term
	if (parse->rightChild != 0 && nodeSub <= userInput)
	{
		searchByLastName(userInput, parse->rightChild);
	}

} //end of searchByLastName


//search through the whole tree and find matches based on month, day, and year
void Contacts::searchByBirthdate(std::string userInput, treeNode* parse) { // goes through birthdate tree

	if (parse == 0) {
		return;
	}

	int len = userInput.length();
	std::string bday = parse->c->birthdate;

	std::stringstream parseDate(bday);
	std::string pMon;
	std::string pDay;
	std::string pYr;
	std::getline(parseDate, pMon, '/');
	std::getline(parseDate, pDay, '/');
	std::getline(parseDate, pYr);

	//first part of in-order traversal
	searchByBirthdate(userInput, parse->leftChild);


	//in-order: instead of printing, add to vector if the input is any part of the date.
	if (bday.length() >= userInput.length() && bday.substr(0, len) == userInput)
	{
		addToSearchResults(parse);
	}
	else if (pMon.length() >= userInput.length() && pMon.substr(0, len) == userInput)
	{
		addToSearchResults(parse);
	}
	else if (pDay.length() >= userInput.length() && pDay.substr(0, len) == userInput)
	{
		addToSearchResults(parse);
	}
	else if (pYr.length() >= userInput.length() && pYr.substr(0, len) == userInput)
	{
		addToSearchResults(parse);
	}

	//final part of in-order traversal
	searchByBirthdate(userInput, parse->rightChild);

} //end of searchByBirthdate

void Contacts::addToSearchResults(treeNode* pointer) {
	/** If a contact is found that matches, add it to the search results vector.
	This function makes sure that the contact doesn't already exist within the
	results vector, as someone might have 2 matching search terms that would put
	the contact into the results vector normally. */


	for (int i = 0; i < searchResults.size(); i++) {
		if (searchResults[i] == pointer->c) {
			return;
		}
	}
	searchResults.push_back(pointer->c);
}

void Contacts::clearSearchResults() {
	// simply clears the vector by popping until the length is 0.
	while (searchResults.size() > 0) {
		searchResults.pop_back();
	}
}

void Contacts::search() { // Search function that's BASICALLY obselete given the GUI.
	std::cout << "Type your search term. Search by first name, last name, or phone number, but not full name." << std::endl;
	std::string userInput = "";
	std::cin >> userInput;
	userInput = toLowercase(userInput);
	clearSearchResults();

	searchByFirstName(userInput, firstNameRoot);
	searchByLastName(userInput, lastNameRoot);
	if (userInput.length() != 0 && userInput[0] <= '9' && userInput[0] >= '0')
	{
		searchByBirthdate(userInput, birthdateRoot);
	}


	if (searchResults.size() == 0) {
		std::cout << "No contacts were found!" << std::endl;
	}
	else {
		std::string x = "100";
		for (int i = 0; i < searchResults.size(); i++) {
			std::cout << i << ") " << searchResults[i]->firstName << " " << searchResults[i]->lastName << std::endl;
		}
		//input an option to go to main menu, edit, or delete
		while (stoi(x) > searchResults.size() || stoi(x) < 0) {
			std::cout << "Selection: ";
			std::cin >> x;
			if (stoi(x) > searchResults.size() || stoi(x) < 0) {
				std::cout << "Not a valid selection! Choose between 0 and " << searchResults.size() << std::endl;
			}
			displayDetailedContact(searchResults[stoi(x)]);
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
				editContact(searchResults[stoi(x)]);
				return;
			}
			if (stoi(y) == 2) { // user chose to delete the contact
				Contact* c = searchResults[stoi(x)];
				deleteFromAllTrees(c, true);
				return;
			}
		}
		// working on next, they select one to do. it calls displayDetailedContact. Then the user can edit / delete it.
	}
}

/* PRECONDITION: userInput is a name (or part of a name) or birthday, but not a full name or anything with a space
* PURPOSE: Add matches to the searchResults member variable of Contacts.
*/
void Contacts::search(std::string userInput) {
	/** search function the GUI uses.*/


	userInput = toLowercase(userInput);
	clearSearchResults(); //clear search results before adding anything

	//these 3 functions add matches to searchResults member variable
	searchByFirstName(userInput, firstNameRoot);
	searchByLastName(userInput, lastNameRoot);
	if (userInput.length() != 0 && userInput[0] <= '9' && userInput[0] >= '0')
	{
		searchByBirthdate(userInput, birthdateRoot);
	}

	if (searchResults.size() == 0) {
		std::cout << "No contacts were found!" << std::endl;
	}
}
//// //// /////
//// CREATING

void Contacts::addToFirstTree(treeNode* given) {
	given->c->firstTreePointer = given;
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
	given->c->lastTreePointer = given;
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
	given->c->birthTreePointer = given;
	if (birthdateRoot == nullptr) {
		birthdateRoot = given;
		return;
	}
	std::stringstream givenDate(given->c->birthdate);
	std::string gMon;
	std::string gDay;
	std::string gYr;
	std::getline(givenDate, gMon, '/');
	std::getline(givenDate, gDay, '/');
	std::getline(givenDate, gYr);

	treeNode* parse = birthdateRoot; //start with parse at root
	bool isLeft = true;
	while (parse != nullptr) {
		given->parent = parse;

		std::stringstream parseDate(parse->c->birthdate);
		std::string pMon;
		std::string pDay;
		std::string pYr;
		std::getline(parseDate, pMon, '/');
		std::getline(parseDate, pDay, '/');
		std::getline(parseDate, pYr);

		if (std::stoi(gMon) < std::stoi(pMon)) {
			parse = parse->leftChild;
			isLeft = true;
		}
		else if (std::stoi(gMon) > std::stoi(pMon)) {
			parse = parse->rightChild;
			isLeft = false;
		}
		else //same month
		{
			if (std::stoi(gDay) < std::stoi(pDay)) {
				parse = parse->leftChild;
				isLeft = true;
			}
			else if (std::stoi(gDay) > std::stoi(pDay)) {
				parse = parse->rightChild;
				isLeft = false;
			}
			else //same month and day; make lesser years be a left child. Right child is >= years
			{
				if (gYr < pYr)
				{
					parse = parse->leftChild;
					isLeft = true;
				}
				else
				{
					parse = parse->rightChild;
					isLeft = false;
				}
			} //end of code for same month and day
		}
	}
	if (isLeft) {
		given->parent->leftChild = given; // K - reason for having parent
	}
	else {
		given->parent->rightChild = given;
	}
}

//// //// /////
//// ADD TO ALL TREES
void Contacts::createContact() { // for non-GUI only.
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

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);
	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl;
}

void Contacts::createContact(std::string firstName, std::string lastName, std::string phoneNumber, std::string birthdate, std::string address, std::string email) {
	/*Parameterized contact creator for the GUI to use.*/


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

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);
	//TRACE0("ADDED NEW CONTACT");
	std::cout << std::endl << "Added " << newContact->firstName << " to your contact list!" << std::endl;
}

//// //// ////
//// EDITING

//FOR TESTING IN OLD MAIN
void Contacts::editContact(Contact* editThis) { // non-gui only.
	std::string firstName;
	std::cout << "What is the new contact's first name? : ";
	std::cin >> firstName;
	editThis->firstName = firstName;

	std::string lastName;
	std::cout << "What is the new contact's last name? : ";
	std::cin >> lastName;
	editThis->lastName = lastName;

	std::string phoneNumber;
	std::cout << "What is the new contact's phone number? Enter in xxx-xxx-xxxx format : ";
	std::cin >> phoneNumber;
	editThis->phoneNumber = phoneNumber;

	std::string birthdate;
	std::cout << "What is the new contact's birthdate? Enter in mm/dd/yyyy form : ";
	std::cin >> birthdate;
	editThis->birthdate = birthdate;

	std::string address;
	std::cout << "What is the new contact's address? : ";
	getline(std::cin, address); //clear the \n left over from the >>
	getline(std::cin, address); //actually get the address
	editThis->address = address;

	std::string email;
	std::cout << "What is the new contact's address? : ";
	getline(std::cin, email); //actually get the address
	editThis->email = email;

	editThis->firstName = firstName;
	editThis->lastName = lastName;
	editThis->phoneNumber = phoneNumber;
	editThis->birthdate = birthdate;
	editThis->address = address;
	editThis->email = email;

	postEdit(editThis);
}

//OVERLOADED FOR GUI. PASS IN POINTER TO CONTACT YOU WANT TO EDIT, THEN NAME, ETC.
void Contacts::editContact(Contact* editThis, std::string firstName, std::string lastName, std::string phoneNumber, std::string birthdate, std::string address, std::string email) {
	editThis->firstName = firstName;
	editThis->lastName = lastName;
	editThis->phoneNumber = phoneNumber;
	editThis->birthdate = birthdate;
	editThis->address = address;
	editThis->email = email;

	postEdit(editThis);
}

//deletes all tree nodes with contact, then adds it back to all the trees
void Contacts::postEdit(Contact* c)
{
	deleteFromAllTrees(c, false);
	treeNode* firstNode = new treeNode;
	treeNode* lastNode = new treeNode;
	treeNode* birthNode = new treeNode;

	firstNode->c = c;
	lastNode->c = c;
	birthNode->c = c;

	addToFirstTree(firstNode);
	addToLastTree(lastNode);
	addToBirthTree(birthNode);
} //end of postEdit function


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
		traverse = del->rightChild; //start in right branch and find the leftmost leaf during the while loop
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
} //end of findReplacement


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
		*currentlySortedBy = rep; //change firstNameRoot / lastNameRoot / birthdateRoot to match rep (the new root)
	}

	if (rep != 0)
	{
		//make the parent of rep stop pointing to it.
		if (rep != del->leftChild && rep == rep->parent->leftChild) //rep is a left child. This is necessary if rep is in the middle of the right branch
		{
			rep->parent->leftChild = rep->rightChild;
		}
		else if (rep == del->rightChild) //rep is a right child (this should only happen if rep is the child of what we are deleting)
		{
			del->rightChild = rep->rightChild; //this should work since rep has no left child
		}


		//put the replacement contact where the soon-to-be-deleted contact was.
		rep->parent = del->parent;
		if (rep != del->leftChild)
		{
			rep->leftChild = del->leftChild;
			rep->rightChild = del->rightChild;
		}

		//finally, make the new children of rep point to it as a parent
		if (rep->leftChild != 0)
		{
			rep->leftChild->parent = rep;
		}
		if (rep->rightChild != 0)
		{
			rep->rightChild->parent = rep;
		}
	} //end of code for if replacement exists


	//make the parent of del point to rep
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
} //end of deleteTreeNode


//delete all the treeNodes with Contact c, then delete the contact from the heap if deleteContact is true
void Contacts::deleteFromAllTrees(Contact* c, bool deleteContact) {


	treeNode** previouslySortedBy = currentlySortedBy;

	currentlySortedBy = &firstNameRoot;
	deleteTreeNode(c->firstTreePointer);
	currentlySortedBy = &lastNameRoot;
	deleteTreeNode(c->lastTreePointer);
	currentlySortedBy = &birthdateRoot;
	deleteTreeNode(c->birthTreePointer);

	currentlySortedBy = previouslySortedBy; //make currentlySortedBy point to what it was before deleteFromAllTrees was called

	if (deleteContact)
	{
		delete c;
	}
}



//HELPER FUNCTION FOR getContactsInOrder
void getInOrder(treeNode* parse, std::vector<Contact*>& vec)
{
	if (parse == 0)
	{
		return;
	}
	else
	{
		getInOrder(parse->leftChild, vec);

		vec.push_back(parse->c);

		getInOrder(parse->rightChild, vec);
	}
}


//ACCESSOR METHODS
std::vector<Contact*> Contacts::getSearchResults()
{
	return searchResults;
}
void Contacts::getContactsInOrder(std::vector<Contact*>& vec)
{
	//clear the vector
	while (vec.size() > 0)
	{
		vec.pop_back();
	}
	//start at root of tree
	getInOrder(*currentlySortedBy, vec);
}
void Contacts::changeToFirstNames()
{
	currentlySortedBy = &firstNameRoot;
}
void Contacts::changeToLastNames()
{
	currentlySortedBy = &lastNameRoot;
}
void Contacts::changeToBirthdates()
{
	currentlySortedBy = &birthdateRoot;
}
