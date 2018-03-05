#include "navigation.h"
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]){
	stepCount = 0;
	string temp = argv[1];//takes command line input as argument
	init(temp.c_str());
	print();
	getEuc();
	checkNbr();
	findMinEuc();
}
void init(string temp){
	ifstream temPlate;//getting stream and file input setup
	temPlate.open(temp.c_str());
	int org = 0;
	if(temPlate.is_open()){//check if file is open and available.
		getline(temPlate, line);
		size = atoi(line.c_str());//converting first row into an integer to determine size of grid.
		grid = new roboClass* [size];
		for(int x = 0; x < size; ++x ){//creating the grid and assigning the size based on the first row
			grid[x] = new roboClass[size];
		}
		for (int i = 0; i < size; ++i)//going throuh the grid and adding the contents of the text file to the array
		{
			getline(temPlate, line);
			for (int j = 0; j < size; ++j)
			{
				grid[i][j].type = line[j];//assigning the char that represents the "node" in the new grid
				grid[i][j].localRow = i;//assigning the coordinates
				grid[i][j].localCol = j;
				if (grid[i][j].type == 'g')
				{
					goalX = i;//labeling the goal state
					goalY = j;
				}
				if (grid[i][j].type == 'i')
				{
					currentX = i;//labeling the initial state
					currentY = j;
				}
				
			}	

		}
	}
}
void getEuc(){
	//iterating through the 2d array and assigning each node with a local value with the given equation.
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (grid[i][j].type == '+')
			{
				grid[i][j].Dist = 1000;
			}else{	
				grid[i][j].Dist = sqrt(pow(i-goalX, 2)+ pow(j-goalY, 2));
			}
		}
	}
}
void getMan(){
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if(grid[i][j].type == '+')
			{
				grid[i][j].Dist = 1000;
			}else{
				grid[i][j].Dist = abs(i-goalX) + abs(j-goalY);
			}
		}
	}
}
void findMinEuc(){//finding the minimum distance cell and assigning that as the enw current node.
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator it;
	/*for(it = _path.begin(); it != _path.end(); ++it){
    	cout<<(*it).localRow<<"," << (*it).localCol<<endl;
	}*/
	it = min_element(_path.begin(), _path.end());
	intendedX = (*it).localRow;
	intendedY = (*it).localCol;
	currentX = intendedX;
	currentY = intendedY;
	if (grid[currentX][currentY].type == 'g')
	{
		print();
		getMan();
		findMinMan();
	}else{
		grid[currentX][currentY].type = 'o';
		/* to solve the last part of the assignment we need to add a counter after the above line so that everytime we make a move towards
		the goal, we increment the cost by 1 (g(N)).  then we need to find a way to include the values that we get from the 
		getEuc() and getMan() functions.

		something like:
		else{
			grid[currentX][currentY].type = 'o';
			costCounter = 1 + grid[i][j].eucDist; (or .manDist)
		}
		*/
	}
	//cout << "before" <<_path.size() << endl;
	_path.remove(grid[intendedX][intendedY]);
	//cout << intendedX << "," << intendedY << endl;
	//cout << "after" << _path.size() << endl;
	checkNbr();
	//print();
	findMinEuc();	
}
void findMinMan(){
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator iterate;

	iterate = min_element(_path.begin(),_path.end());
	intentX = (*iterate).localRow;
	intentY = (*iterate).localCol;
	currentX = intentX;
	currentY = intentY;
	if(grid[currentX][currentY].type == 'g')
	{
		print();
		exit(0);
	}
	else{
		grid[currentX][currentY].type == 'o';
	}
	_path.remove(grid[intentX][intentY]);
	checkNbr();
	//print();
	findMinMan();
}
void traverse(){
}
void checkNbr(){//checking the neighbors of the current cell while ignoring cells that are on the edge or have already been visited.
	if(currentX < size-1 && grid[currentX+1][currentY].type != '+' && !checkContains(currentX+1, currentY) && grid[currentX+1][currentY].visited != true){
		_path.push_back(grid[currentX+1][currentY]);
		grid[currentX+1][currentY].prev = &grid[currentX][currentY];
		//cout << "hi" << endl;
		
	}
	if(currentX != 0 && grid[currentX-1][currentY].type != '+' && !checkContains(currentX-1, currentY) && grid[currentX-1][currentY].visited != true){
		_path.push_back(grid[currentX-1][currentY]);
		grid[currentX-1][currentY].prev = &grid[currentX][currentY];
		//cout << "bye" << endl;
	}
	if(currentY < size-1 && grid[currentX][currentY+1].type != '+' && !checkContains(currentX, currentY+1) && grid[currentX][currentY+1].visited != true){
		_path.push_back(grid[currentX][currentY+1]);
		grid[currentX][currentY+1].prev = &grid[currentX][currentY];
		//cout << "no" << endl;
	}
	if(currentY != 0 && grid[currentX][currentY-1].type != '+' && !checkContains(currentX, currentY-1) && grid[currentX][currentY-1].visited != true){
		_path.push_back(grid[currentX][currentY-1]);
		grid[currentX][currentY-1].prev = &grid[currentX][currentY];
		//cout << "ok" << endl;
	}//push the node into the fringe that is used later to find the ideal distance in findMinEuc

}
bool checkContains(int x, int y){//checks if the node already exists and returns boolean, used to make sure no duplicates in list.
	return find(_path.begin(), _path.end(), grid[x][y]) != _path.end();
}
void print(){//printing out the graph.
	cout << "Success" <<endl;
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].type;
		}
		cout << endl;
	}
}