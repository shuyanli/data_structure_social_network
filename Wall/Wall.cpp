#include "Wall.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Wall::Wall() : username{ "" } {}

Wall::Wall(string username) : username{ username } {}

void Wall::addPost(WallPost wp) {
	posts.push_back(wp);
}

void Wall::addWallPostResponse(int number, WallPost wp) {
	if (!hasTheWall(number))
		return;
	posts[number - 1].addWallpostResponse(wp.getContent(), wp.getAuthor());
}

void Wall::deleteWallpostResponse(int number, string aname){
	if (!hasTheWall(number))
		return;
	posts[number].deleteWallpostResponse(aname);
}

void Wall::removePost(int pos) {
	if (pos >= posts.size())
		return;
	std::vector<WallPost>::iterator it = posts.begin() + pos;
	posts.erase(it);
}

string Wall::getUsername() const {
	return username;
}

void Wall::setUsername(string new_name){
	username = new_name;
}

void Wall::writeWall() {
	int count = 1;
	for (vector<WallPost>::iterator i = posts.begin(); i != posts.end(); ++i, count++) {
		cout << "Post " << count << endl;
		i->printWall();
		cout << endl;
	}
}
void Wall::writeWall(int number)
{
	if (number - 1 >= posts.size())
		return;
	cout << "Post " << number << endl;
	posts[number - 1].printWall();
	cout << endl;
}


void Wall::printWallResponse(int number)
{
	if (number - 1 >= posts.size())
		return;
	cout << "Post " << number << endl;
	posts[number - 1].printWallResponse();
	cout << endl;
}

bool Wall::hasTheWall(int number) {
	return number - 1 < posts.size();
}

void Wall::removePost(string name) {
	bool hasmore = false;
	for (vector<WallPost>::iterator i = posts.begin(); i != posts.end(); ++i) {
		if (i->getAuthor() == name)
		{
			posts.erase(i);
			hasmore = true;
			break;
		}
	}
	if (hasmore)
		removePost(name);
}

string Wall::saveString() {
	string result = "";
	for (vector<WallPost>::iterator i = posts.begin(); i != posts.end(); ++i) {
		result += i->saveString(username);
	}
	return result;
}