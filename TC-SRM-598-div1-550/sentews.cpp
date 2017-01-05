#include<algorithm>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;
class FoxAndFencing
{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
	{
		if (d<=mov1+rng1) return "Ciel";
		int codeforces;
		if(mov1+rng1>mov2+rng2)
			if(mov1>mov2&&rng2+mov2+1+mov2<=rng1+mov1)
			codeforces=2;
			else
				codeforces=1;
		else if(mov1+rng1==mov2+rng2)
			codeforces=1;
		else if(mov1+d<=mov2+rng2||(mov2>mov1 && mov1+rng1+1+mov1<=rng2+mov2))
				codeforces=0;
        else
           codeforces=1;
		if(codeforces==2)
			return "Ciel";
		if(codeforces==1)
			return "Draw";
		if(codeforces==0)
			return "Liss";
	}
}
;
