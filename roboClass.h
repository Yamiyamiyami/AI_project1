#ifndef ROBO_CLASS_H
#define ROBO_CLASS_H
using namespace std;

class roboClass{
	public:
		char type;
		int currCost;
		float Dist;
		int localRow;
		int localCol;
		roboClass* prev;
		bool visited;
		roboClass();
		bool operator==(const roboClass& right);
		bool operator<(const roboClass& right);
		bool operator>(const roboClass& right);
};
#endif