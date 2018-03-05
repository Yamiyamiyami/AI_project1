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
	return(this->Dist > right.Dist && this->Dist > right.Dist);
}
bool roboClass::operator<(const roboClass& right){
	return(this->Dist < right.Dist && this->Dist < right.Dist);
}
