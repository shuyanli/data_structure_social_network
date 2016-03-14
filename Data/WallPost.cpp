#include "WallPost.h"

using namespace std;

WallPost::WallPost(std::string cnt, std::string author, int deepnumber) {
	content = cnt;
	authorName = author;
	deep = deepnumber;
	time(&(timeOfPost));	

}

void WallPost::setContent(string cnt) {
	content = cnt;
	time(&(timeOfPost)); //change the time when post is edited
}

string WallPost::getContent() const {
	return content;
}

void WallPost::setTime(time_t timeptr) {
	timeOfPost = timeptr;
}

time_t WallPost::getTime() const {
	return timeOfPost;
}

int WallPost::getDeep() const {
	return deep;
}

string WallPost::getAuthor() const {
	return authorName;
}

void WallPost::printWall() {
	if (deep > 0)
		cout << "Response " << deep << endl;
	cout << "Content: " << getContent() << endl;
	cout << "\t time: " << getTime() << endl;
	cout << "\t author: " << authorName << endl;
	if (WallpostResponse.size() > 0)
		cout << "Response message: " << WallpostResponse.size() << endl;
}

void WallPost::printWallResponse()
{
	printWall();
	for (int i = 0; i < WallpostResponse.size(); i++)
	{
		WallpostResponse[i].printWall();
	}
}


void WallPost::addWallpostResponse(std::string cnt, std::string author) {
	WallpostResponse.push_back(WallPost(cnt, author, deep + 1));
}


void WallPost::deleteWallpostResponse(string aname) {

	bool hasmore = false;
	for (std::vector<WallPost>::iterator it = WallpostResponse.begin(); it != WallpostResponse.end(); it++) {
		if (it->getAuthor() == aname) {
			WallpostResponse.erase(it);
			hasmore = true;
			break;
		}
	}
	if (hasmore)
		deleteWallpostResponse(aname);
}


string WallPost::saveString(string ownername) {
	std::stringstream sstream;
	sstream << ownername << "," << authorName << "," << content << endl;
	return sstream.str();
}