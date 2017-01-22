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

class KnightCircuit2{
public:
	int maxSize(int w, int h){
		if(w>h) swap(w,h);
		if(w==1) return 1;
		if(w==2) return (h+1)/2;
		if(w==3&&h==3) return 8;
		return w*h;
	}
};
