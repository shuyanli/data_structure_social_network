#ifndef WALLPOST_H
#define WALLPOST_H
#include <ctime>   
using std::time_t;
#include <string>
using std::string;
#include <sstream>
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
class WallPost{

private:
	string content;
	time_t timeOfPost;
	string authorName;
	int deep;  
	vector<WallPost> WallpostResponse;

public:

	WallPost(std::string cnt, std::string author, int deepnumber);

	//getters and setters
	void setContent(std::string cnt);
	string getContent() const;

	void setTime(std::time_t timeptr);	
	time_t getTime() const;

	int getDeep() const;
	string getAuthor() const;

	void printWall();
	void printWallResponse();

	void addWallpostResponse(std::string cnt, std::string author);
	void deleteWallpostResponse(string aname);

	string saveString(string ownername);
};

#endif
