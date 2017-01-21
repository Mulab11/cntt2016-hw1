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

int d[55][55];

class ColorfulWolves{
public:
	int getmin(vector <string> go){
		int n=go.size();
		for(int i=0;i<n;i++){
			int now=0;
			for(int j=0;j<n;j++){
				if(go[i][j]=='Y') d[i][j]=now,now++;
				else d[i][j]=1e9;
			}
			
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		if(d[0][n-1]==1e9) return -1;
		return  d[0][n-1];
	}
};
