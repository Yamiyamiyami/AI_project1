#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include "roboClass.cpp"

using namespace std;
roboClass **grid;
string temp;
int size;
string line;
int goalX;
int goalY;
int currentX;
int currentY;
int intendedX;
int intendedY;
int intentX;
int intentY;
int eucCount;
int manCount;
int stepCount;
list<roboClass> _path;

void init(string x);
void getEuc();
void getMan();
void print();
void traverse();
void findMinEuc();
void findMinMan();
void checkNbr();
bool checkContains(int x, int y);