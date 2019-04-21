#pragma once
#include <iostream>
#include <string>
#include <vector>

struct treeNode;

struct Contact { // actual contact

	std::string firstName = ""; // EX: Kyran
	std::string lastName = ""; // EX: Butler
	std::string phoneNumber = ""; // EX: 303-303-3003
	std::string birthdate = ""; // EX: 04-06-2001
	std::string address = ""; // EX: 50181 South Street, Denver, Colorado
	std::string email = ""; // EX: kyran@butlerhq.com

	treeNode* firstTreePointer = nullptr;
	treeNode* lastTreePointer = nullptr;
	treeNode* birthTreePointer = nullptr;
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
	void createContact(std::string firstName, std::string lastName, std::string phoneNumber, std::string birthdate, std::string address, std::string email);
	void editContact(Contact* editThis); //I think this should be in the GUI file with displayContact(). (There is no GUI file yet)
	void editContact(Contact* editThis, std::string firstName, std::string lastName, std::string phoneNumber, std::string birthdate, std::string address, std::string email);
	void postEdit(Contact* c); //deletes all tree nodes with contact, then adds it back to all the trees
	void deleteTreeNode(treeNode* del);
	void deleteFromAllTrees(Contact* c, bool deleteContact); //delete all the treeNodes with Contact c, then delete the contact from the heap if deleteContact is true

	void search();
	void search(std::string input); //overloaded for In Ji
	void searchByFirstName(std::string userInput, treeNode* parse);
	void searchByLastName(std::string userInput, treeNode* parse);
	void searchByBirthdate(std::string userInput, treeNode* parse);
	void addToSearchResults(treeNode* pointer);
	void clearSearchResults();

	void displayDetailedContact(Contact* c); //temporary function; this should probably be in GUI and it should make data fields instead of printing.

	void addToFirstTree(treeNode* c);
	void addToLastTree(treeNode* c);
	void addToBirthTree(treeNode* c);

	bool saveAllToFile(std::string x);
	bool loadAllFromFile(std::string filename);


	//getters and setters
	treeNode** treeHead(); //return the pointer that currentlySortedBy points to
	std::vector<treeNode*> getSearchResults(); //return searchResults, vector won't change when a contact is deleted
	void getContactsInOrder(std::vector<Contact*>& vec); //get all the contacts from a tree in order.
	void changeToFirstNames(); //make treeHead point to firstNamesRoot (in Contacts, not in main)
	void changeToLastNames();
	void changeToPhoneNumbers();
	void changeToBirthdates();
	void changeToAddresses();
	void changeToEmails();


private:
	// the 'print all' tree is currently sorted by:
	treeNode** currentlySortedBy;
	treeNode* firstNameRoot; // root of the tree sorted by first names
	treeNode* lastNameRoot; // root of the tree sorted by last names
	treeNode* birthdateRoot; // root of the tree sorted by birthday -> can make more of these easily
	std::vector<treeNode*> searchResults;
};
