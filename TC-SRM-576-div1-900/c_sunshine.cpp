#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
const int M=1000000009;
typedef long long LL;
class CharacterBoard
{
	public:
	int n,m;
	vector<string> s;
	int W;
	
	LL fpw(int a,int b)
	{
		int s=1;
		for(;b;b>>=1,a=(LL)a*a%M)
			if(b&1)s=(LL)s*a%M;
		return s;
	}
	
	LL calc(int len)
	{
		int cnt=0;
		map<int,char> alpha;
		alpha.clear();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				int k=((LL)W*i+j)%len;//get the position in the string
				if(!alpha.count(k))
					alpha[k]=s[i][j];
				else if(alpha[k]!=s[i][j])//check if there is a conflict at any positions in the string
					return 0;
			}
		return fpw(26,len-alpha.size());//|alpha| letters in the string have been already determined.
	}
	
	int countGenerators(vector<string> fragment,int W,int i0,int j0)
	{
		this->W=W;
		s=fragment;
		n=s.size();m=s[0].size();
		set<int> length;
		length.insert(1);
		//Find all possible lengths of the string that at least one letter in the string occurs twice in the given fragment.
		for(int i=1-n;i<n;i++)
			for(int j=1-m;j<m;j++)
			{
				LL k=(LL)i*W+j;
				if(k<=0)continue;
				for(int d=1;(LL)d*d<=k;d++)
					if(k%d==0)
					{
						if(d<=W)length.insert(d);
						if(k/d<=W)length.insert(k/d);
					}
			}
		LL ans=0;
		//Dismiss the fragment, and the answer is \sum[0<=k<=W-n*m] 26^k
		if(W>=n*m)ans=(LL)(fpw(26,W-n*m+1)-1)*fpw(25,M-2)%M;
		for(set<int>::iterator it=length.begin();it!=length.end();it++)
		{
			if(*it>=n*m)
				ans-=fpw(26,*it-n*m);//We now think about the fragment, so remove the preceding answer.
			ans+=calc(*it);
			ans%=M;
		}
		if(ans<0)ans+=M;
		return int(ans);
	}
};

