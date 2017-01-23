#include<bits/stdc++.h>
using namespace std;class IncrementAndDoubling{public:int getMin(vector<int>a){int maxv=0,ans=0,n=a.size();for(int i=0;i<n;i++){if(a[i]>maxv)maxv=a[i];ans+=__builtin_popcount(a[i]);}int l=0;for(;maxv;maxv>>=1,l++);if(l)l--;return ans+l;}} sol ; 


int a[] = {0, 0, 1, 0, 1} ; 

vector<int> g ; 
int main() { 
		for (int i = 0; i < 5; i ++) 
		g.push_back(a[i]) ; 
		printf("%d\n", sol.getMin(g)) ; 
}

