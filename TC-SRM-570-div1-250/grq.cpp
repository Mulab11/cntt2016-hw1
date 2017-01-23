#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int u[4][2]={1,0,0,1,-1,0,0,-1};

int solve(vi a){
	int n=a.size();
	int x=0,y=0,dir=0;
	for(int i=0;i<n;i++){
		x+=a[i]*u[dir][0],y+=a[i]*u[dir][1];
		dir=(dir+a[i])%4;
	}
	return abs(x)+abs(y);
}

class RobotHerb{
public:
	long long getdist(int T, vector<int> a){
		int n=a.size(),sum=0;
		for(int i=0;i<n;i++) sum+=a[i];
		if(sum%4==0)
			return (ll)solve(a)*T;
		else if(sum%2==0){
			if(T%2==0) return 0;
			return solve(a);
		}
		else{
			vi b;b.clear();
			for(int i=1;i<=T%4;i++)
				for(int j=0;j<n;j++) b.pb(a[j]);
			return solve(b);
		}
//		return ;
	}
};
