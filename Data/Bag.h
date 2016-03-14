
#ifndef BAG_H
#define BAG_H
#include <string> 
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
// from http://www.austincc.edu/akochis/cosc1320/bag.htm

class User;

class Bag {

private:
	vector <User *>  data;  // data store up to 20 members
public:
	Bag();					// Constructor
	bool insert(User*);		// Put a member in the bag
	bool remove(User*);		// remove a member from the bag
	int size();				// number of members in bag
	void clear();           // remove all members from bag
	bool inbag(User*);		// is a member in the bag
	vector <User *> getFriendList();
};
#endif