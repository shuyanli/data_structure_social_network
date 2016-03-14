#ifndef USERNETWORK_H
#define USERNETWORK_H
#include "User.h"
#include <vector>
using std::vector;
class UserNetwork{
	private:
		vector<User> userlist;
		int numUsers;
	public:
		UserNetwork();
		User* inNetwork(std::string username); //if username is in the network
		//inNetwork is only way to access userlist
		bool checkPassword(std::string username, std::string password);
		void addUser(const User &user);
		void removeUser(std::string username);
		void printUsers(); //print all users to stdout
		void writeToFile();		//specify filename in implementation
		void readFromFile();	//specify filename in implementation 
					//users.txt
		User * getUser(std::string username);
};
#endif
