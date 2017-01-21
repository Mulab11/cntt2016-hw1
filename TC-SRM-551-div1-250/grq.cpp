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
#define fore(i,x,y) for(int i=head[(x)];i!=(y);i=p[i].next)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,x,y) for(int i=(x);i>=(y);i--)
#define REP(i,x,y) for(int i=(x);i<(y);i++)
#define PER(i,x,y) for(int i=(x);i>(y);i--)
using namespace std;

int n,g[1005];
string s;

class ColorfulChocolates{
public:
	int maximumSpread(string chocolates, int maxSwaps){
		n=chocolates.size();s=chocolates;
		cout<<s<<endl;
		per(ans,n,1){
			rep(a,0,25){
				int tot=0;
				REP(i,0,n) if(s[i]==a+'A') g[++tot]=i;
				REP(i,0,n){
					int l=i,r=i+ans-1;
					if(r>=n) break;
					rep(j,1,tot){
						if(j+ans-1>tot) break;
						int tmp=0;
						REP(k,j,j+ans) tmp+=abs(g[k]-(l-j+k));
						printf("%d\n",tmp);
						if(tmp<=maxSwaps) return ans;
					}
				}
			}
		}
		return 0;
	}
};
