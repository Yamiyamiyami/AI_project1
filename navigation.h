#include <iostream>
#include <string>
#include <stdlib.h>
#include "roboClass.cpp"

using namespace std;
roboClass **grid;
int size;
string line;
int goalX;
int goalY;


void init(string x);
void getEuc();
void getMan();
void print();