#include "User.h"
#include <sstream>

using namespace std;

User::User() {
	username = "";
	firstname = "";
	lastname = "";
	password = "";
	wall = Wall(username);
}

User::User(const User &rhs) {
	dob = new int[3];
	username = rhs.getUsername();
	firstname = rhs.getFirstName();
	lastname = rhs.getLastName();
	password = rhs.getPassword();
	wall.setUsername(username);
	for(int i=0; i<3; i++)
		dob[i] = rhs.getDOB()[i];
	wall = Wall(username);
}
User::User(string name, string _password, string _firstname, string _lastname, int date[]) {
	//precondition: date has 3 elements: day, month, year
	dob = new int[3];
	username = name;
	password = _password;
	firstname = _firstname;
	lastname = _lastname;
	wall.setUsername(name);
	for(int i=0; i<3; i++)
		dob[i] = date[i];
	wall = Wall(username);
}

User::User(string formatString) {      
	//add info from formatString
	// format "name password realname dd mm yyyy"
	// no functionality for wall posts in format string yet.

	dob = new int[3];
	istringstream iss(formatString);
	iss >> username;
	iss >> password;
	iss >> firstname;
	iss >> lastname;
	iss >> dob[0];
	iss >> dob[1];
	iss >> dob[2];
	wall = Wall(username);
}

User::~User() { 
	if (dob != nullptr)
		delete [] dob;
}
void User::addWallPost(WallPost wp) {  
	wall.addPost(wp);
}

void User::addWallPostResponse(int number, WallPost wp) {
	wall.addWallPostResponse(number, wp);
}

void User::deleteWallPost(int pos) { 
	wall.removePost(pos);			
}

string User::getUsername() const {
	return username;
}
void User::setUsername(string _username) {
	username = _username;
}

string User::getPassword() const {
	return password;
}
string User::getFirstName() const {
	return firstname;
}
string User::getLastName() const {
	return lastname;
}
int* User::getDOB() const {
	return dob; //not quite working yet 
}
string User::getInfo() const {        //return all private info into formatted string
	stringstream ss;
	ss 	<< username << " " << password << " " << firstname << " " 
		<< lastname << " " << dob[0] << " " << dob[1] << " " << dob[2];
	return ss.str();
}

void User::writeWall() {
	wall.writeWall();
}

void User::writeWall(int number) {
	wall.writeWall(number);
}

bool User::hasTheWall(int number) {
	return wall.hasTheWall(number);
}

void User::addFriend(User* frienduser) {
	if (friends.inbag(frienduser))
		return;
	friends.insert(frienduser);
}

void User::removeFriend(User* frienduser) {
	if (friends.inbag(frienduser))
		return;
	friends.remove(frienduser);
}

void User::printFriendList() {
	vector <User *> lis = friends.getFriendList();
	cout << "Friend: " << endl;
	for (int i = 0; i < lis.size(); i++) {
		cout << "\t" <<lis[i]->username << endl;
	}
	cout << "-----------------------------------------------------" << endl;
}

void User::printWallResponse(int number) {
	wall.printWallResponse(number);
	cout << "-----------------------------------------------------" << endl;
}
void User::deleteWallPost(string uname) {
	wall.removePost(uname);
}

void User::deleteWallPostResponse(int number, string uname) {
	wall.deleteWallpostResponse(number, uname);
}
set<string> User::getpossibleFriend() {
	set<string> possible;
	vector <User *> myfriend = friends.getFriendList();
	for (int i = 0; i < myfriend.size(); i++) {
		vector <User *> myfriendfriend = myfriend[i]->friends.getFriendList();
		for (int j = 0; j < myfriendfriend.size(); j++) {
			if (!isMyFriends(myfriendfriend[j])) {
				if (possible.find(myfriendfriend[j]->getUsername()) == possible.end()) {
					possible.insert(myfriendfriend[j]->getUsername());
				}
			}
		}
	}
	return possible;
}

bool User::isMyFriends(User *u) {
	return friends.inbag(u);
}


vector<string> User::getTheRoute(string pname) {
	set<string> visit;
	vector<string> result;
	result.push_back(username);
	visit.insert(username);
	return getTheRoute(this, pname, visit, result);
}

vector<string> User::getTheRoute(User *u, string pname, set<string> visit, vector<string> result) {
	vector <User *> myfriend = u->friends.getFriendList();
	for (int i = 0; i < myfriend.size(); i++) {
		if (myfriend[i]->getUsername() == pname) {
			result.push_back(myfriend[i]->getUsername());
			return result;
		}
		if (visit.find(myfriend[i]->getUsername()) == visit.end()) {
			visit.insert(myfriend[i]->getUsername());
			result.push_back(myfriend[i]->getUsername());
			vector<string> res = getTheRoute(myfriend[i], pname, visit, result);
			if (res.size() != 0)
				return res;
			result.pop_back();
			visit.erase(myfriend[i]->getUsername());
		}
	}
	return vector<string>();
}

bool User::operator==(const User &o) const {
	return username == o.username;
}

bool User::operator<(const User &o) const {
	return strcmp(username.c_str(), o.username.c_str()) < 0;
}

bool User::operator>(const User &o) const {
	return strcmp(username.c_str(), o.username.c_str()) > 0;
}


string User::wallSaveString() {
	return wall.saveString();
}

string User::friendSaveString() {
	vector <User *> myfriend = friends.getFriendList();
	string result = "";
	for (int i = 0; i < myfriend.size(); i++) {
		result += username + "," + myfriend[i]->username + "\n";
	}
	return result;
}