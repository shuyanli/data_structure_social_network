#include "UserNetwork.h"
#include <fstream>
#include <iostream>

using namespace std;

UserNetwork::UserNetwork() {
	numUsers = 0;
}

User* UserNetwork::inNetwork(std::string username) {

	for (vector<User>::iterator userptr = userlist.begin(); userptr != userlist.end(); userptr++) {
		if((userptr->getUsername() == username))
			return &(*userptr);
	}
	return nullptr;
}

bool UserNetwork::checkPassword(std::string username, std::string password) {
	//precondition: username in userlist, userlist is not empty
	for (vector<User>::iterator userptr = userlist.begin(); userptr != userlist.end(); userptr++) {
		if ((userptr->getUsername() == username))
			return userptr->getPassword() == password;
	}
	return false; 
}

void UserNetwork::addUser(const User &user) {
	userlist.push_back(user);
}

void UserNetwork::removeUser(string username) { 
	for (vector<User>::iterator userptr = userlist.begin(); userptr != userlist.end(); userptr++) {
		if ((userptr->getUsername() == username)) {
			userlist.erase(userptr);
		}
			
	}
}

void UserNetwork::printUsers() { 
	for (vector<User>::iterator i = userlist.begin(); i != userlist.end(); ++i) {
		cout << i->getInfo() << endl;
	}
}

void UserNetwork::writeToFile(){
	ofstream myfile;
	ofstream myfileFriend;
	ofstream myfileWall;
	myfile.open("Users.txt", ios::trunc);
	myfileFriend.open("Friend.txt", ios::trunc);
	myfileWall.open("Wall.txt", ios::trunc);
	for (vector<User>::iterator i = userlist.begin(); i != userlist.end(); ++i) {
		myfile << i->getInfo() << endl;
		myfileFriend << i->friendSaveString();
		myfileWall << i->wallSaveString();
	}
}


User * UserNetwork::getUser(std::string username) {
	for (vector<User>::iterator userptr = userlist.begin(); userptr != userlist.end(); userptr++) {
		if ((userptr->getUsername() == username)) {
			return &(*userptr);
		}
	}
	return nullptr;
}

void UserNetwork::readFromFile() {
	ifstream myfile;
	myfile.open("Users.txt");
	if(myfile.fail()) { //file not found
		myfile.close();
		return;
	} else {
		string line;
		while(!myfile.eof() && !myfile.fail()) {	//if there is still content in file:
			getline(myfile, line); //don't think this has a newline at the end
			if (line.length() < 2)
				continue;
			User newUser = User(line);
			userlist.push_back(newUser);
		}
	}
	myfile.close();
	//
	ifstream myfileFriend;
	myfileFriend.open("Friend.txt");
	if (myfileFriend.fail()) { //file not found
		myfileFriend.close();
		return;
	} else {
		string line;
		while (!myfileFriend.eof() && !myfileFriend.fail()) {
			getline(myfileFriend, line);
			if (line.length() < 2)
				continue;
			string u1 = "", u2 = "";
			int i = 0;
			for (i = 0; i < line.length(); i++) {
				if (line[i] == ',')
					break;
				u1 += line[i];
			}
			for (i++; i < line.length(); i++) {
				u2 += line[i];
			}
			User * user1 = getUser(u1);
			User * user2 = getUser(u2);
			if (user1 != nullptr && user2 != nullptr) {
				user1->addFriend(user2);
				user2->addFriend(user1);
			}
		}
	}

	//

	ifstream myfileWall;
	myfileWall.open("Wall.txt");
	if (myfileWall.fail()) { //file not found
		myfileWall.close();
		return;
	} else {
		string line;
		while (!myfileWall.eof() && !myfileWall.fail()) {
			getline(myfileWall, line);
			if (line.length() < 2)
				continue;
			string ownername ="", authorName = "", content = "";
			int i = 0;
			for (i = 0; i < line.length(); i++) {
				if (line[i] == ',')
					break;
				ownername += line[i];
			}
			for (i++; i < line.length(); i++) {
				if (line[i] == ',')
					break;
				authorName += line[i];
			}
			for (i++; i < line.length(); i++) {
				content += line[i];
			}
			User * user1 = getUser(ownername);
			if (user1 != nullptr) {
				user1->addWallPost(WallPost(content, authorName, 0));
			}
		}
	}
}

