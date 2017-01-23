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

class TheNumberGameDivOne{
public:
	string find(long long n){
		if(n&1) return "Brus";
		int cnt=0;
		while(n%2==0) n/=2,cnt++;
		if(n==1&&(cnt&1)) return "Brus";
		return "John";
	}
};
