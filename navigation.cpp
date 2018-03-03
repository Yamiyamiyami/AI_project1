#include "navigation.h"
#include <math.h>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]){
	string temp = argv[1];//takes command line input as argument
	init(temp.c_str());
	print();
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
		for (int i = 1; i < size; ++i)//going throuh the grid and adding the contents of the text file to the array
		{
			getline(temPlate, line);
			for (int j = 1; j < size; ++j)
			{
				grid[i][j].type = line[j];
				grid[i][j].localRow = i;
				grid[i][j].localCol = j;
				if (grid[i][j].type == 'g')
				{
					goalX = i;
					goalY = j;
				}
				if (grid[i][j].type == 'i')
				{
					currentX = i;
					currentY = j;
				}
				
			}	

		}
	}
	getEuc();
	getMan();
}
void getEuc(){
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (grid[i][j].type == '+')
			{
				grid[i][j].eucDist = 1000;
			}else{	
				grid[i][j].eucDist = sqrt(pow(i-goalX, 2)+ pow(j-goalY, 2));
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
				grid[i][j].manDist = 1000;
			}else{
				grid[i][j].manDist = abs(i-goalX) + abs(j-goalY);
			}
		}
	}
}
void findMinEuc(){
	list<roboClass>::iterator it;
	for(it = _path.begin(); it != _path.end(); ++it){
    	cout<<(*it).eucDist<<endl;
	}
	it = min_element(_path.begin(), _path.end());
	int tempX = (*it).localRow;
	int tempY = (*it).localCol;
	intendedX = tempX;
	intendedY = tempY;
	cout << intendedX << "," << intendedY << endl;
	
}
void traverse(){
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			
		}
	}
}
void checkNbr(){
	cout<<_path.size();
	if(grid[currentX+1][currentY].type != '+' && !checkContains(currentX+1, currentY) && currentX < size-1){
		_path.push_back(grid[currentX+1][currentY]);
		cout<<"hi"<<endl;
		cout<<_path.size() <<endl;
	}
	if(grid[currentX-1][currentY].type != '+' && !checkContains(currentX-1, currentY) && currentX != 0){
		_path.push_back(grid[currentX-1][currentY]);
		cout<<"bye"<<endl;
	}
	if(grid[currentX][currentY+1].type != '+' && !checkContains(currentX, currentY+1) && currentY < size-1){
		_path.push_back(grid[currentX][currentY+1]);
		cout<<"ok"<<endl;
	}
	if(grid[currentX][currentY-1].type != '+' && !checkContains(currentX, currentY-1) && currentY != 0){
		_path.push_back(grid[currentX][currentY-1]);
		cout<<"ty"<<endl;
	}

}
bool checkContains(int x, int y){
	return find(_path.begin(), _path.end(), grid[x][y]) != _path.end();
}
void print(){
	checkNbr();
	findMinEuc();
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].type;
		}
		cout << endl;
	}
	
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].eucDist << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].manDist << " ";
		}
		cout << endl;
	}
}