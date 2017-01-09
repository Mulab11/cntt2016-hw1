//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

int cnt[3],res=0;

class LittleElephantAndBalls{
public:
	int getNumber(string s){
		For(i,0,s.length()){
			int c;
			if (s[i]=='R') c=0;
			if (s[i]=='G') c=1;
			if (s[i]=='B') c=2;
			For(j,0,3) res+=cnt[j];
			cnt[c]=min(cnt[c]+1,2);
		}	//直接计算答案
		return res;
	}
} T;