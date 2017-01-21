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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

string C="Ciel",D="Draw",L="Liss";

class FoxAndFencing{
public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
		rng1+=mov1;rng2+=mov2;
		if(d<=rng1) return C;
		if(rng1<rng2){
			if(mov1+d<=rng2) return L;
			if(mov1<mov2&&mov1+rng1<rng2) return L;
			return D;
		}
		if(rng1==rng2) return D;
		if(mov2<mov1&&mov2+rng2<rng1) return C;
		return D;
	}
};