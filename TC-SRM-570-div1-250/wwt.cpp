#include <bits/stdc++.h>
#define fe first
#define se second

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pi;

const pi xy[4] = {{0,1},{1,0},{0,-1},{-1,0}};

pi operator +(pi a,pi b) {return pi(a.fe + b.fe,a.se + b.se);}
pi operator *(pi a,int b) {return pi(a.fe * b,a.se * b);}

class RobotHerb
{
public:
	long long getdist(int T, vector<int> a)
	{
		static pi len[4];
		static int go[4];
		for(int i = 0;i < 4;i ++)
		{
			go[i] = i;
			for(int j = 0;j < a.size();j ++) //simulate to get the transformation
			{
				len[i] = len[i] + xy[go[i]] * a[j];
				go[i] = (go[i] + a[j]) % 4;
			}
		}
		pi ans = {0,0},allen = {0,0};
		int dir = 0,l = 0;
		for(;;) //get the len and the number of nodes of the circle 
		{
			allen = allen + len[dir];
			dir = go[dir];
			l ++;
			if (dir == 0) break;
		}
		dir = 0;
		for(;T % l != 0;) //walk the left steps
		{
			ans = ans + len[dir];
			dir = go[dir];
			T --;
		}
		ans = ans + allen * (T / l); //entire circle walk
		return abs(ans.fe) + abs(ans.se);
	}
};
