
#ifndef USER_H
#define USER_H
#include "WallPost.h"
#include "Wall.h"
#include "Bag.h"
#include <string>
#include <set>
using std::string;
using std::set;
class User {
private:
	std::string username;

	std::string firstname;
	std::string lastname;
	std::string password;
	int* dob;               //private data field, dynamic date array
	Wall wall;
	Bag friends;

public:
	User(std::string name, std::string password, std::string firstname, std::string lastname, int date[]);
	User(std::string formatString);       //add info from formatString
	User();
	User(const User &rhs);
	~User();

	// format: plain string with spaces, ex. "name password realname dd mm yyyy"
	std::string getPassword() const; //returns password to check account
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getUsername() const;
	void setUsername(std::string);

	void addWallPost(WallPost wp);
	void addWallPostResponse(int number, WallPost wp);
	void deleteWallPost(int pos);  //change param, maybe something else to indicate the wallpost?
	void deleteWallPost(string uname);
	void deleteWallPostResponse(int number, string uname);

	void printFriendList();
	void printWallResponse(int number);

	int* getDOB() const;

	std::string getInfo() const;        //return all private info into formatted string
	void writeWall();
	void writeWall(int number);
	bool hasTheWall(int number);

	void addFriend(User* frienduser);
	void removeFriend(User* frienduser);

	bool isMyFriends(User *u);
	set<string> getpossibleFriend();

	vector<string> getTheRoute(string pname);
	vector<string> getTheRoute(User *u, string pname, set<string> visit, vector<string> result);

	bool operator==(const User &o) const;
	bool operator<(const User &o) const;
	bool operator>(const User &o) const;

	string wallSaveString();
	string friendSaveString();
};

#endif
