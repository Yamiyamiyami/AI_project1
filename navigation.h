#include <iostream>
#include <string>
#include <stdlib.h>
#include "roboClass.cpp"

using namespace std;
roboClass **grid;
int size;
string line;

void init(string x);
void setEuc();
void setMan();
void print();