#include "User.h"
#include "UserNetwork.h"
#include "Wall.h"
#include "WallPost.h"
#include "Bag.h"

#include <cctype>  // for toupper
#include <iostream>
#include <string>
#include <fstream> // for input and output
#include <sstream>
#include <set>

using namespace std;

void print_menu();
void print_login_menu(string username);
char get_command(); //user input
void show_network(UserNetwork usernetwork); // show  usernetwork
void createUser(); // reads username from cin, prints to screen and returns string
void userLogin();
void displayWall(string username);
void createNewPost(string username);
void deleteProfile(); //TODO
void searchByName(string query); //TODO
void sendFriendRequest(string username); //TODO
void showPendingRequests(); //TODO
void removeFriend(); //TODO
void displayAllFriend();
void enterFriendWall();
void enterPost(User *f_user);
void getTheRoute();
void getpossibleFriend();
void addFriend();
//global vars
UserNetwork usernetwork;  // UserNetwork	usernetwork from file
bool loginStatus = false;
string uname;
User *curr_user;
int main() {
	/*std::ifstream myfile;
	myfile.open("users.txt"); //default modes: ios::in and ios::out for input and output
	std::string user;
	*/
	curr_user = nullptr;
	usernetwork.readFromFile();
	cout << "User Network read from file. " << endl;

	char choice; // command entered by user

	do {
		(loginStatus) ? print_login_menu(uname) : print_menu();
		choice = toupper(get_command());
		switch (choice) {
			//basic functions
		case 'C': //create new user
			createUser();
			break;
		case 'L': //login
			if (!loginStatus)
				userLogin();
			else
				loginStatus = false;
			break;
		case 'Q':
			break;
		case 'A':
			if (loginStatus) {
				addFriend();
				break;
			}
		case 'D': 	//display wall
			if (loginStatus) {
				displayWall(uname);
				break;
			}
		case 'N':	//create new post on wall
			if (loginStatus) {
				createNewPost(uname);
				break;
			}
		case 'E':	// enter my wall
			if (loginStatus) {
				enterPost(curr_user);
				break;
			}
			//debug functions
		case 'P': //print all users
			show_network(usernetwork);
			break;

		case 'F':	// Display my friend
			if (loginStatus) {
				displayAllFriend();
				break;
			}

		case 'I':	// Enter my friend's wall
			if (loginStatus) {
				enterFriendWall();
				break;
			}

		case 'R':	// Get the Route of other user
			if (loginStatus) {
				getTheRoute();
				break;
			}

		case 'S':	// Find my possible friend
			if (loginStatus) {
				getpossibleFriend();
				break;
			}
		default:
			cout << choice << " is invalid." << endl;
		}
	} while (choice != 'Q');

	usernetwork.writeToFile();
	return 0;
}

void print_menu() {
	cout << endl;
	cout << "The following options are available:" << endl;
	cout << "C    Create new account" << endl;
	cout << "L    Login to an existing account" << endl;
	cout << "Q    Quit" << endl;

}

void print_login_menu(string username) {
	//if username exists:
	cout << endl;
	cout << "Welcome, " << username << "!" << endl;
	cout << "D    Display contents of your wall" << endl;
	cout << "F    Display my friend" << endl;
	cout << "N    Create new post on my wall" << endl;
	cout << "E    Enter a post on my wall" << endl;
	cout << "A    Add a friends" << endl;
	cout << "I    Enter my friend's wall" << endl;
	cout << "R    Get the Route of other user" << endl;
	cout << "S    Find my possible friend" << endl;
	cout << "L    Logout of your account" << endl;
	cout << "Q    Quit" << endl;
	//cout << ".     Logout of your account" << endl;
}

char get_command() {
	char command;
	cout << "Enter your choice: ";
	while (!(cin >> command))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "I don't recognize that input. Please try again." << endl;
	}

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return command;
}

void show_network(UserNetwork usernetwork) {
	usernetwork.printUsers();
}

void createUser() {
	string username, firstname, lastname, password;
	int date[3] = { 0, 0, 0 };//day, month, year;

	cout << "Creating new user account" << endl;
	cout << "Enter desired username: ";
	cin >> username;

	if (usernetwork.inNetwork(username))
		cout << "Username taken." << endl;
	else {
		cout << "Please enter a password: ";
		cin >> password;
		cout << "Please enter your first name: ";
		cin >> firstname;
		cout << "Please enter your last name: ";
		cin >> lastname;
		cout << "Enter your date of birth." << endl;
		cout << "Day: (dd) ";
		while (!(cin >> date[0]) || date[0] > 31 || date[0] < 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Please input a valid day: " << endl;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "Month: (mm) ";
		while (!(cin >> date[1]) || date[1] > 12 || date[1] < 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Please input a valid month: " << endl;
		}

		cin.clear();

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Year: (yyyy) ";
		while (!(cin >> date[2]) || date[2] > 2015 || date[2] < 1900)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Please input a valid year: " << endl;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		stringstream formatString;
		formatString << username << " " << password << " " << firstname << " " << lastname << " " << date[0] << " " << date[1] << " " << date[2];



		User newUser(formatString.str());
		// cout << formatString.str() << endl;
		usernetwork.addUser(newUser);
		//usernetwork.printUsers();
		cout << "User has been added successfully." << endl;
	}
}

void userLogin() {
	string username, password;

	if (!loginStatus) {
		cout << "Login to existing account" << endl;
		cout << "Enter username: ";
		cin >> username;
		if (usernetwork.inNetwork(username)) {
			cout << "Enter password for " << username << ": ";
			cin >> password;
			if (usernetwork.checkPassword(username, password)) {
				cout << "Login successful. " << endl;
				loginStatus = true;
				uname = username;
				curr_user = usernetwork.getUser(username);
				return;
			}
			else {
				cout << "Login unsuccessful. " << endl;
				return;
			}

		}
		cout << "User does not exist." << endl;
	}
	//else implement logout
}

void displayWall(string username) {
	cout << "\n\n" << endl;
	usernetwork.inNetwork(username)->writeWall(); //displays to stdout
}

void createNewPost(string username) {
	string content = "";
	cout << "Enter post content:" << endl;
	cin.get();
	getline(cin, content);
	usernetwork.inNetwork(username)->addWallPost(WallPost(content, username, 0));
}

void displayAllFriend() {
	curr_user->printFriendList();
}

void addFriend() {
	cout << "Enter a user name: ";
	string name;
	cin >> name;
	//
	User * fri_user = usernetwork.getUser(name);
	if (fri_user == nullptr) {
		cout << "Can't find the user in system" << endl;
		return;
	}
	curr_user->addFriend(fri_user);
	cout << "Success!" << endl;
}

void getpossibleFriend() {
	set<string> possible = curr_user->getpossibleFriend();
	//print all the users v such that the degree
	// of separation between u and v is equal to 3
	cout << "my all possible friend: " << endl;
	for (set<string>::iterator it = possible.begin(); it != possible.end(); it++) {
		cout << *it << endl;
	}
}

void enterFriendWall() {
	cout << "Enter your friend name: ";
	string name;
	cin >> name;
	//
	User * fri_user = usernetwork.getUser(name);
	if (fri_user == nullptr) {
		cout << "Can't find the user in system" << endl;
		return;
	}
	if (!curr_user->isMyFriends(fri_user)) {
		cout << "Can't find the user in my friends" << endl;
		return;
	}
	//
	string option = "1";
	while (option != "0") {
		fri_user->writeWall();
		cout << endl;
		cout << "0 return" << endl;
		cout << "1 write a post" << endl;
		cout << "2 delete my post" << endl;
		cout << "3 enter a post" << endl;
		cout << "enter your option: ";
		cin >> option;
		if (option == "0")
			return;
		else if (option == "1") {
			string content = "";
			cout << "Enter post content:" << endl;
			cin.get();
			getline(cin, content);
			fri_user->addWallPost(WallPost(content, curr_user->getUsername(), 0));
		}
		else if (option == "2") {
			fri_user->deleteWallPost(curr_user->getUsername());
		}
		else if (option == "3") {
			enterPost(fri_user);
		}
		else  {
			cout << "Invalid option" << endl;
		}
	}
}


void enterPost(User *f_user)
{
	if (f_user == nullptr) {
		cout << "Invalid user!" << endl;
		return;
	}
	cout << "Enter the post number: ";
	int num;
	cin >> num;
	if (!f_user->hasTheWall(num)) {
		cout << "Invalid post number!" << endl;
		return;
	}
	string option = "1";
	while (option !=  "0") {
		f_user->writeWall(num);
		cout << endl;
		cout << "0 return" << endl;
		cout << "1 write a response" << endl;
		cout << "2 delete my response" << endl;
		cout << "3 display response" << endl;
		cout << "enter your option: ";
		cin >> option;
		if (option == "0")
			return;
		else if (option == "1") {
			string content = "";
			cout << "Enter post content:" << endl;
			cin.get();
			getline(cin, content);
			f_user->addWallPostResponse(num, WallPost(content, curr_user->getUsername(), 0));
		}
		else if (option == "2") {
			f_user->deleteWallPostResponse(num, curr_user->getUsername());
		}
		else if (option == "3") {
			f_user->printWallResponse(num);
		}
		else  {
			cout << "Invalid option" << endl;
		}
	}

}

void getTheRoute()
{
	cout << "Enter a user name: ";
	string name;
	cin >> name;
	vector<string> result = curr_user->getTheRoute(name);
	if (result.size() != 0) {
		for (int i = 0; i < result.size(); i++){
			cout << result[i];
			if (i < result.size() - 1)
				cout << " -> ";
		}
		cout << endl;
	}
	else {
		cout << "Can't find the route" << endl;
	}
}