#include <bits/stdc++.h>

using namespace std;


class TheBrickTowerEasyDivOne {
public:
	int find(int redCount, int redHeight, int blueCount, int blueHeight) {
		if(redHeight==blueHeight)return 2*min(redCount,blueCount)+(redCount!=blueCount);//高度相等 
		else return 3*min(redCount,blueCount)+(redCount!=blueCount);//高度不相等，三种情况 
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
