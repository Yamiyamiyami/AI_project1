#include "roboClass.h"
using namespace std;

roboClass::roboClass(){
	type = ' ';
	currCost = 0;
	eucDist = 0;
	manDist = 0;
	localRow = 0;
	localCol = 0;
	visited = false;
}
bool roboClass::operator==(const roboClass& right){
	return(this->localRow==right.localRow && this->localCol == right.localCol);
}
bool roboClass::operator>(const roboClass& right){
	return(this->eucDist > right.eucDist && this->eucDist > right.eucDist);
}
bool roboClass::operator<(const roboClass& right){
	return(this->eucDist < right.eucDist && this->eucDist < right.eucDist);
}
