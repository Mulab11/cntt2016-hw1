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

int n,si;

class BinPacking{
public:
	int minBins(vector <int> item){
		n=item.size();si=0;
		sort(item.begin(),item.end());
		for(int i=0;i<n;i++)
			if(item[i]==100) si++;
		int ans=n+1;
		for(int i=0;i<=si;i+=3){
			int l=i,r=n-1,tmp=i/3;
			while(l<=r){
				tmp++;
				if(item[l]+item[r]<=300) l++;
				r--;
			}
			ans=min(ans,tmp);
		}
		return ans;
	}
};