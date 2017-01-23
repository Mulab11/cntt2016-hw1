#include<bits/stdc++.h>
using namespace std;const int MAXN=110;const int LIMIT=100;const int LIMIT2=300;int n,s,v[MAXN],i,j;class BinPacking{public:int minBins(vector<int>a){n=a.size();sort(a.begin(),a.end());for(i=n-1;~i;i--)if(a[i]>LIMIT&&!v[i]){v[i]=1;n--;s++;for(j=i;~j;j--)if(!v[j]&&a[i]+a[j]<=LIMIT2){v[j]=1;n--;break;}}return s+(n+2)/3;}} sol ;


int a[] = {100, 200, 100, 100, 100, 100, 200, 100, 200} ; 

int main() { 
		vector<int> g ; 
		for (int i = 0; i < 9; i ++) g.push_back(a[i]) ; 
		printf("%d\n", sol.minBins(g))  ;
}
