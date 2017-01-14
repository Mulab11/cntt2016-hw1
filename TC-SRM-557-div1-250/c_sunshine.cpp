#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class FoxAndMountainEasy
{
	public:
	
	string possible(int n,int h0,int hn,string history)
	{
		if(h0+hn+n&1)return "NO";
		int L=0,R=0,M=0,len=history.size();
		//Get minimum height in the sequence.
		for(int i=0;i<len;i++)
		{
			if(history[i]=='U')R++;
			else R--;
			M=min(M,R);
		}
		L-=M,R-=M;
		if(h0+n-len+R-L<hn)return "NO";//target height is too high.
		if(h0-n+len+R-L>hn)return "NO";//target height is too low.
		int u=max(0,L-h0),v=max(0,R-hn);
		if(u+v+len>n)return "NO";//Do not have enough steps to keep the height always nonegative.
		return "YES";
	}
	
};

