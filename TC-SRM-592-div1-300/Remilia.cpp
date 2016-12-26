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
int ans=0;
char ball[55];
int count(int l,int r){
	int R=0,G=0,B=0;
	rep(i,l,r){
		if (ball[i]=='R') R=1;
		if (ball[i]=='G') G=1;
		if (ball[i]=='B') B=1;
	}
	return R+G+B;
}
int v;

/*
设c相距最远的位置是i,j，则将(i,j)之间的间隔都加上1
因此可以贪心，画一条线，每次在这条线的一段加字符，如果c已经在两端出现或者没有出现，就随意
只有一端出现，就在另一端加上这个字符
*/

class LittleElephantAndBalls{
public:
	int getNumber(string s){
		int n=s.size();
		ball[0]=s[0];
		rep(i,1,n-1){
			int pos=0,mx=count(0,i-1);
			rep(j,1,i-1) if ((v=count(0,j-1)+count(j,i-1))>mx) mx=v,pos=j;
			ans+=mx;
			drp(j,i,pos+1) ball[j]=ball[j-1];
			ball[pos]=s[i];
		}
		return ans;
	}
};
