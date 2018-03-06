#include "navigation.h"
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]){
	stepCount = 0;
	mode = false;
	temp = argv[1];//takes command line input as argument
	init(temp.c_str());
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
		grid2 = new roboClass* [size];
		for(int x = 0; x < size; ++x ){//creating the grid and assigning the size based on the first row
			grid[x] = new roboClass[size];
			grid2[x] = new roboClass[size];
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
				grid2[i][j].type = line[j];//assigning the char that represents the "node" in the new grid
				grid2[i][j].localRow = i;//assigning the coordinates
				grid2[i][j].localCol = j;
				if (grid2[i][j].type == 'g')
				{
					goalX = i;//labeling the goal state
					goalY = j;
				}
				if (grid2[i][j].type == 'i')
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
	//iterating through the 2d array and assigning each node with a local value with the given equation.
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
void findMinEuc(){//finding the minimum distance cell and assigning that as the new current node.
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator it;
	it = min_element(_path.begin(), _path.end());
	intendedX = (*it).localRow;
	intendedY = (*it).localCol;
	currentX = intendedX;
	currentY = intendedY;
	if (grid[currentX][currentY].type == 'g')
	{
		cout << "Euclidian" << endl;
		getTrail();
		print();
		_path.clear();
		init(temp.c_str());
		getMan();
		checkNbr();
		findMinMan();
	}else{
		grid[currentX][currentY].type = 'o';
	}
	_path.remove(grid[intendedX][intendedY]);
	checkNbr();
	findMinEuc();	
}
void findMinMan(){//finding the minimum distance cell and assigning that as the new current node.
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator it;
	it = min_element(_path.begin(),_path.end());
	intendedX = (*it).localRow;
	intendedY = (*it).localCol;
	currentX = intendedX;
	currentY = intendedY;
	if(grid[currentX][currentY].type == 'g')
	{
		cout << "Manhattan" << endl;
		getTrail();
		print();
		_path.clear();
		init(temp.c_str());
		getEuc();
		checkNbr();
		findMinEucwithCost();
	}
	else{
		grid[currentX][currentY].type = 'o';
	}
	_path.remove(grid[intendedX][intendedY]);
	checkNbr();
	findMinMan();
}
void findMinEucwithCost(){//finding the minimum distance cell and assigning that as the new current node.
	mode = true;
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator it;
	it = min_element(_path.begin(), _path.end());
	intendedX = (*it).localRow;
	intendedY = (*it).localCol;
	currentX = intendedX;
	currentY = intendedY;
	if (grid[currentX][currentY].type == 'g')
	{
		cout << "Euclidian with Cost" << endl;
		getTrail();
		print();
		_path.clear();
		init(temp.c_str());
		getMan();
		checkNbr();
		findMinManwithCost();
	}else{
		grid[currentX][currentY].type = 'o';
	}
	_path.remove(grid[intendedX][intendedY]);
	checkNbr();
	findMinEucwithCost();	
}
void findMinManwithCost(){//finding the minimum distance cell and assigning that as the new current node.
	grid[currentX][currentY].visited = true;
	list<roboClass>::iterator it;
	it = min_element(_path.begin(),_path.end());
	intendedX = (*it).localRow;
	intendedY = (*it).localCol;
	currentX = intendedX;
	currentY = intendedY;
	if(grid[currentX][currentY].type == 'g')
	{
		cout << "Manhattan with Cost" << endl;
		getTrail();
		print();
		exit(0);
	}
	else{
		grid[currentX][currentY].type = 'o';
	}
	_path.remove(grid[intendedX][intendedY]);
	checkNbr();
	findMinManwithCost();
}
void checkNbr(){//checking the neighbors of the current cell while ignoring cells that are on the edge or have already been visited.
	if(currentX < size-1 && grid[currentX+1][currentY].type != '+' && !checkContains(currentX+1, currentY) && grid[currentX+1][currentY].visited != true){
		if(mode){
			grid[currentX+1][currentY].currCost = grid[currentX][currentY].currCost+1;
		}
		_path.push_back(grid[currentX+1][currentY]);
		grid[currentX+1][currentY].prev = &grid[currentX][currentY];
		grid2[currentX+1][currentY].prev = &grid2[currentX][currentY];		
	}

	if(currentX != 0 && grid[currentX-1][currentY].type != '+' && !checkContains(currentX-1, currentY) && grid[currentX-1][currentY].visited != true){
		if(mode){
			grid[currentX-1][currentY].currCost = grid[currentX][currentY].currCost+1;
		}
		_path.push_back(grid[currentX-1][currentY]);
		grid[currentX-1][currentY].prev = &grid[currentX][currentY];
		grid2[currentX-1][currentY].prev = &grid2[currentX][currentY];
	}

	if(currentY < size-1 && grid[currentX][currentY+1].type != '+' && !checkContains(currentX, currentY+1) && grid[currentX][currentY+1].visited != true){
		if(mode){
			grid[currentX][currentY+1].currCost = grid[currentX][currentY].currCost+1;
		}
		_path.push_back(grid[currentX][currentY+1]);
		grid[currentX][currentY+1].prev = &grid[currentX][currentY];
		grid2[currentX][currentY+1].prev = &grid2[currentX][currentY];
	}

	if(currentY != 0 && grid[currentX][currentY-1].type != '+' && !checkContains(currentX, currentY-1) && grid[currentX][currentY-1].visited != true){
		if(mode){
			grid[currentX][currentY-1].currCost = grid[currentX][currentY].currCost+1;
		}
		_path.push_back(grid[currentX][currentY-1]);
		grid[currentX][currentY-1].prev = &grid[currentX][currentY];
		grid2[currentX][currentY-1].prev = &grid2[currentX][currentY];
	}//push the node into the fringe that is used later to find the ideal distance in findMinEuc

}
bool checkContains(int x, int y){//checks if the node already exists and returns boolean, used to make sure no duplicates in list.
	return find(_path.begin(), _path.end(), grid[x][y]) != _path.end();
}
void print(){//printing out the final graph with correct backtracking.
	cout << "Success" <<endl;
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid2[i][j].type;
		}
		cout << endl;
	}
	cout << "Number of steps: " << stepCount << endl;
	cout << "Number of nodes: " << _path.size() << endl;
	stepCount = 0;
	
	cout << endl;
	cout << endl;
}
void getTrail(){//traces nodes backwards to root from goal therefore ignoring alternate paths
	roboClass *rawr = &grid2[goalX][goalY];
	while(rawr->prev!=NULL){
		rawr = rawr->prev;
		grid2[rawr->localRow][rawr->localCol].type = 'o';
		stepCount++;
	}
	grid2[rawr->localRow][rawr->localCol].type = 'i';
}