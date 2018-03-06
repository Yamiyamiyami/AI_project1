#include "roboClass.h"
using namespace std;

roboClass::roboClass(){
	type = ' ';
	currCost = 0;
	Dist = 0;
	localRow = 0;
	localCol = 0;
	prev = NULL;
	visited = false;
}
bool roboClass::operator==(const roboClass& right){
	return(this->localRow==right.localRow && this->localCol == right.localCol);
}
bool roboClass::operator>(const roboClass& right){
	return(this->Dist+this->currCost > right.Dist + right.currCost);
}
bool roboClass::operator<(const roboClass& right){
	return(this->Dist+this->currCost < right.Dist + right.currCost);
}
