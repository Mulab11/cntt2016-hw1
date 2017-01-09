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

const int N=70;

int cnt[N];

class BitwiseAnd{
public:
	vector<ll> lexSmallest(vector<ll> S,int n){
		For(i,0,S.size())
			For(j,0,60){
				if (S[i]>>j&1)
					if (++cnt[j]>2) return {};
			}
		For(i,0,S.size())
			For(j,i+1,S.size())
				if (!(S[i]&S[j])) return {};
		while (S.size()<n){	//每次加入一个点，就将当前权值最小的挑出，然后加入最小的若干个二进位即可
			ll tmp=0;
			For(i,0,S.size()){
				For(j,0,60)
					if ((S[i]>>j&1)&&cnt[j]==1){
						tmp|=1ll<<j;
						cnt[j]++;
						break;
					}
				if (!(S[i]&tmp)) return {};
			}
			int rem=n-int(S.size())-1;
			for (int i=0;i<60&&rem;i++)
				if (cnt[i]==0){
					tmp|=1ll<<i;
					cnt[i]++;
					rem--;
				}
			if (rem) return {};
			S.pb(tmp);
		}
		sort(S.begin(),S.end());
		return S;
	}
} T;