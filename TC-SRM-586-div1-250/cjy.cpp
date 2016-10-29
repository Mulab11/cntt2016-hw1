#include<bits/stdc++.h>
using namespace std;
class PiecewiseLinearFunction
{
	public:
		int maximumSolutions(vector<int> y)
		{
			map<int,int>S;
			int n=y.size(),i,t,s=0,r=0;
			for(i=0;i<n;i++)
			{
				t=0;
				if(i>0)
				{
					if(y[i]==y[i-1])return -1;
					t+=1-2*(y[i]>y[i-1]);
				}
				if(i<n-1)t+=1-2*(y[i]>y[i+1]);
				if(t>0)S[2*y[i]]++,S[2*y[i]+1]+=(t>1);
				if(t<0)S[2*y[i]+1]--,S[2*y[i]]-=(t<-1);
			}
			for(map<int,int>::iterator x=S.begin();x!=S.end();x++)
			{
				r+=x->second;
				s=max(s,r);
			}
			return s;
		}
};
