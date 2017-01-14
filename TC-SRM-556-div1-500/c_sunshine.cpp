#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class LeftRightDigitsGame2
{
	public:
	int n;
	string D,LB;
	string f[55][55][3][3];
	bool mem[55][55][3][3];
	
	int cmp(const char &a,const char &b)
	{return a<b?0:(a>b?2:1);}
	
	string dp(int l,int r,int cl,int cr)
	{
		//The remaining cards need to be filled in range[1+l,n-r],
		//and the size relationship is cl for the first l digits and cr for the last r digits.
		if(mem[l][r][cl][cr])return f[l][r][cl][cr];
		string &res=f[l][r][cl][cr],tmp;
		mem[l][r][cl][cr]=1;
		if(l+r==n)
			return res=(cl==2||cl==1&&cr>=1?"":"!");//greater than or equal to than lowerbound
		res="!";
		int c_;
		//put on left
		c_=cl;
		if(c_==1)c_=cmp(D[l+r],LB[l]);//maintain the relationship
		tmp=dp(l+1,r,c_,cr);
		if(tmp!="!")res=D[l+r]+tmp;
		//put on right
		c_=cr;
		if(D[l+r]!=LB[n-r-1])c_=cmp(D[l+r],LB[n-r-1]);//maintain the relationship
		tmp=dp(l,r+1,cl,c_);
		if(tmp!="!")
		{
			tmp=tmp+D[l+r];
			if(res=="!"||tmp<res)res=tmp;
		}
		return res;
	}
	
	string minNumber(string digits,string lowerBound)
	{
		D="";n=digits.size();
		for(int i=0;i<n;i++)D=digits[i]+D;
		LB=lowerBound;
		memset(mem,0,sizeof(mem));
		string res=dp(0,0,1,1);
		return res=="!"?"":res;
	}
};


