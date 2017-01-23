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

bool vis[1055];

class LittleElephantAndIntervalsDiv1{
public:
	long long getNumber(int M, vector <int> L, vector <int> R){
		ll ans=1;
		memset(vis,0,sizeof(vis));
		for(int i=L.size()-1;i>=0;i--){
			bool isok=0;
			for(int j=L[i];j<=R[i];j++)
				if(!vis[j]) vis[j]=1,isok=1;
			if(isok) ans=ans<<1;
		}
		return ans;
	}
};
// BEGIN CUT HERE
