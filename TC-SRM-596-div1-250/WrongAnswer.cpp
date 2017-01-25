#include <vector>
using namespace std;
class IncrementAndDoubling{
public:
	int getMin(vector <int> desiredArray){
		int s=0,m=0;
		for(int i=0;i<desiredArray.size();i++)
			for(int a=desiredArray[i],t=0;a;t>m?m=t:1,a>>=1,t++)s+=a%2;
		return s+m;
	}
};
