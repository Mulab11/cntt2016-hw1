#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<iostream>
#include<set>

#define N 10005

using namespace std;
const int inf=(int)1e9;
int n,i,a[N],ans,j,k,rest,sumt;
multiset<int>st;
class BinPacking{
public:
int minBins(vector<int> v)
{
	  int n=v.size();
	  for (i=0;i<n;++i) a[v[i]]++;
	  ans+=a[100]/3; a[100]%=3;
	  rest=ans; 
	  for (i=100;i<=300;++i) 
	    for (j=1;j<=a[i];++j) st.insert(i);
	  for (;st.size();)
	  {
	        int x=*--st.end();
	        ++ans;
			st.erase(--st.end());
			multiset<int>::iterator it=st.upper_bound(300-x);
			if (it==st.begin()) 
			{
			   if (x<=200) ++sumt; 
			   continue; 
			} 
			st.erase(--it);
	  }
	  while (sumt>=3&&rest) { ans--; rest--; sumt-=3; } 
	  return ans;
}
};
