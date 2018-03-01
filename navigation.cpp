#include "navigation.h"
#include <math.h>
#include <fstream>

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
		for (int i = 0; i < size; ++i)//going throuh the grid and adding the contents of the text file to the array
		{
			getline(temPlate, line);
			for (int j = 0; j < size; ++j)
			{
				grid[i][j].type = line[j];
				if (grid[i][j].type == 'g')
				{
					goalX = i;
					goalY = j;
				}
			}	

		}
	}
}
void getEuc(){
	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			grid[i][j].eucDist = sqrt(pow(i-goalX, 2)+ pow(j-goalY, 2));
		}
	}
}
void getMan(){
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			grid[i][j].manDist = abs(i-goalX) + abs(j-goalY);
		}
	}
}
void print(){
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].type;
		}
		cout << endl;
	}
	getEuc();
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].eucDist << " ";
		}
		cout << endl;
	}
	cout << endl;
	getMan();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << grid[i][j].manDist << " ";
		}
		cout << endl;
	}
}