#include<cstdio>
#include<algorithm>
using namespace std;
class TheBrickTowerEasyDivOne 
{
    public:
        int find(int redCount, int redHeight, int blueCount, int blueHeight)
        {
            int a=redCount,b=redHeight,c=blueCount,d=blueHeight;
			if(a>c)swap(a,c),swap(b,d);
			int kk,k;
			if(b==d)kk=2;else kk=3;
			if(a!=c)k=1;else k=0;
			return kk*a+k;
        }
};
