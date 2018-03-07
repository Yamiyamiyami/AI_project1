#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <list>
#include "roboClass.cpp"

using namespace std;
roboClass **grid;
roboClass **grid2;
string temp;
int size;
string line;
int goalX;
int goalY;
int currentX;
int currentY;
int intendedX;
int intendedY;
bool mode;
int stepCount;
int nodeCount;
ofstream output;
list<roboClass> _path;

void init(string x);
void getEuc();
void getMan();
void print();
void traverse();
void findMinEuc();
void findMinMan();
void findMinEucwithCost();
void findMinManwithCost();
void checkNbr();
bool checkContains(int x, int y);
void getTrail();