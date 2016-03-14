#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h> 
#include "User.h"
using namespace std;

vector<User> result;

void randomUser(int number);
void randomFriendRelationship(int number);
int randomNumber(int max);
void save();

int main()
{
	srand((unsigned)time(NULL));
	randomUser(10000);
	randomFriendRelationship(100);
	save();
}


void randomUser(int number)
{
	int date[3] = { 11, 5, 2000 };
	for (int i = 0; i < number; i++) {
		std::stringstream sstream;
		sstream << "abc" << i;
		result.push_back(User(sstream.str(), "123456", "bbbb", "aaaa", date));
	}
}

void randomFriendRelationship(int number)
{
	for (int i = 0; i < number; i++) {
		User *a = &result[randomNumber(result.size())];
		User *b = &result[randomNumber(result.size())];
		a->addFriend(b);
		b->addFriend(a);
	}
}


int randomNumber(int max)
{
	return rand() % max;
}

void save()
{
	ofstream myfile;
	ofstream myfileFriend;
	ofstream myfileWall;
	myfile.open("Users.txt", ios::trunc);
	myfileFriend.open("Friend.txt", ios::trunc);
	for (vector<User>::iterator i = result.begin(); i != result.end(); ++i) {
		myfile << i->getInfo() << endl;
		myfileFriend << i->friendSaveString();
	}
}