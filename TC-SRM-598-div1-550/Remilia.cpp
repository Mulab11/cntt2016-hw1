#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
using namespace std;

/*
一步打死就打死了
打不死的话，步子大的那个人一定可以控制在刚好不被打死的那个地方，判一下就好了
*/

class FoxAndFencing{
public:
	string WhoCanWin(int mov1,int mov2,int rng1,int rng2,int d){
		if (d<=mov1+rng1) return "Ciel";
		if (d+mov1<=mov2+rng2) return "Liss";
		if (mov1+rng1>mov2+rng2){
			if (mov1>mov2&&mov1+rng1>mov2*2+rng2) return "Ciel";
				else return "Draw"; 
		}
		else if (mov1+rng1==mov2+rng2) return "Draw";
		else{
			if (mov2>mov1&&mov2+rng2>mov1*2+rng1) return "Liss";
				else return "Draw";
		}
	}
};
