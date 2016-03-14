#ifndef WALL_H
#define WALL_H
#include "WallPost.h"
#include <string>
#include <vector>
using std::vector;
class Wall {
private:
    std::string username;           
	vector<WallPost> posts;
    
public:
    //Constructor
	Wall();
    Wall(std::string username);

    //Member functions
	void addPost(WallPost wp);
	void addWallPostResponse(int number, WallPost wp);

	void removePost(int pos);	            // delete by unique id
	void removePost(string name);	            // delete by unique id
	void deleteWallpostResponse(int number, string aname);

    std::string getUsername() const;		    
    void setUsername(std::string new_name);

    void writeWall();                                   //writes entire wall to string, using cout on each wallpost
	void writeWall(int number);
	bool hasTheWall(int number);
	void printWallResponse(int number);

	string saveString();
};

#endif