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

bool check(vi a,int x){
	int n=a.size();
	a[0]=max(a[0]-x,1);
	for(int i=1;i<n;i++)
		if(a[i]<=a[i-1]){
			if(a[i]+x<=a[i-1]) return 0;
			a[i]=a[i-1]+1;
		}
		else a[i]=max(a[i-1]+1,a[i]-x);
	return 1;
}

class KingdomAndTrees{
public:
	int minLevel(vector <int> heights){
		int l=0,r=1e9;
		while(l<r){
			int mid=l+r>>1;
			if(check(heights,mid)) r=mid; else l=mid+1;
		}
		return r ;
	}
};
