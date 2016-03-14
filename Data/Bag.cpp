//from http://www.austincc.edu/akochis/cosc1320/bag.htm

#include "Bag.h"

Bag::Bag() {

}

void Bag::clear() {
	data.clear();
}

bool Bag::insert(User *value) {
	if (!inbag(value))
		data.push_back(value);
	return true;
}

bool Bag::inbag(User* value) {
	vector<User*>::iterator result = find(data.begin(), data.end(), value);
	return result != data.end();
}

bool Bag::remove(User* value) {
	vector<User*>::iterator result = find(data.begin(), data.end(), value);
	if (result != data.end())
	{
		data.erase(result);
		return true;
	}
	return false;
}


vector <User *> Bag::getFriendList() {
	return data;
}

int Bag::size() {
	return data.size();
}
