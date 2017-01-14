#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
class TheSwapsDivOne
{
	public:
	int n;
	
	double posi(int p)//the possibility that position p is in the range.
	{return (double)(p+1)*(n-p)/(n*(n+1)/2);}
	
	double find(vector<string> sequence,int k)
	{
		string s;
		for(int i=0;i<int(sequence.size());i++)
			s+=sequence[i];
		n=s.size();
		//If an element is swapped, it may be at any other p-1 positions
		int total=(n*(n-1))/2;
		int total0=(n-1)*(n-2)/2;
		double p0=(double)total0/total;//p0 is the possibility that an element is not swapped.
		double p=(1.0-p0)/(n-1);//p is the possibility that an element is swapped with a known other element.
		p0=1.0-p*n;//let p0=1-pn, and now an element has possibility p0 to stay and p to be swapped with any element including itself.
		double pw=1;
		for(int b=k;b;b>>=1,p0=p0*p0)
			if(b&1)pw*=p0;
		//pw is the possibility for an element to stay during all operations.
		//Otherwise it will be on each position at the equal possibility.
		double ans=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				ans+=(double)(s[i]-'0')*((i==j?pw:0)+(1.0-pw)/n)*posi(j);
		return ans;
	}
};

