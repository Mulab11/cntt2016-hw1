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

int n,c;

class FoxAndChess{
public:
	string ableToMove(string s,string t){	//льеп
		n=s.length();
		For(i,0,n)
			if (isalpha(s[i])){
				while (c<n&&!isalpha(t[c])) c++;
				if (c==n) return "Impossible";
				if (s[i]!=t[c]) return "Impossible";
				if (s[i]=='L'&&c>i) return "Impossible";
				if (s[i]=='R'&&c<i) return "Impossible";
				c++;
			}
		while (c<n&&!isalpha(t[c])) c++;
		if (c!=n) return "Impossible";
		return "Possible";
	}
} T;