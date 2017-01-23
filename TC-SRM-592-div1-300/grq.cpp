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

class LittleElephantAndBalls{
public:
	int getNumber(string S){
		int ans=0,r=0,g=0,b=0;
		for(int i=0;i<S.length();i++){
			ans+=min(2,r)+min(2,g)+min(2,b);
			if(S[i]=='R') r++; else if(S[i]=='G') g++; else b++;
		}
		return ans;
	}
};
