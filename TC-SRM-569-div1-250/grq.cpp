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

int n,m,a[55][2];

class TheDevice{
public:
	int minimumAdditional(vector<string> plates){
		n=plates.size();m=plates[0].size();
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(plates[i][j]=='0') a[j][0]++; else a[j][1]++;
		int ans=0;
		for(int j=0;j<m;j++)
			ans=max(ans,max(0,1-a[j][0])+max(0,2-a[j][1]));
		return ans;
	}
};
