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

ll t;
int a;

class TheNumberGameDivOne{
public:
	string find(ll n){
		if (n%2==1) return "Brus";
		for (a=0,t=1;t<n;t<<=1,a++);
		return t==n&&a%2==1?"Brus":"John";	//ÅÐ¶ÏÊä³ö´ð°¸
	}
} T;