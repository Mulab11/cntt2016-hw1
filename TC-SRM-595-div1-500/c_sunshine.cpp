#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn=2555;
class LittleElephantAndRGB
{
	public:
	int n;
	LL ans;
	string s;
	int tr[maxn],cntd;
	
	void Add(int x,int c)
	{
		for(;x<=n;x+=x&-x)
			tr[x]+=c;
	}
	
	int Sum(int x)
	{
		int s=0;
		for(;x;x^=x&-x)
			s+=tr[x];
		return s;
	} 
	
	LL getNumber(vector<string> list,int minGreen)
	{
		//We can pick c then pick d, and use data struct to find the number of (a,b)s which meet the conditions
		s=" ";
		for(int i=0;i<list.size();i++)
			s+=list[i];
		n=s.size()-1;
		for(int i=1;i<n;i++)
		{
			//fs : the length of longest suffix which contains 'G's only.
			//ns : the length of longest substring which contains 'G's only.
			//done : if there exists a substring whose length is no less than misGreen and contains 'G's only
			int fs=0,ns=0,done=0;
			for(int j=i;j;j--)
			{
				if(s[j]=='G')
				{
					if(fs==i-j)fs++;
					ns++;
				}
				else
					ns=0;
				done|=ns>=minGreen;
				if(done)cntd++;
				else
					Add(minGreen-fs,1);
			}
			//fs's meaning is similar but prefix here.
			fs=ns=done=0;
			for(int j=i+1;j<=n;j++)
			{
				if(s[j]=='G')
				{
					if(fs==j-i-1)fs++;
					ns++;
				}
				else
					ns=0;
				done|=ns>=minGreen;
				//string T = S[a..b] + S[c..d] is nice if the total length of the longest suffix of S[a..b] and prefix of S[c..d].
				//We can use Binary Indexed Tree to get the number fast.
				ans+=cntd;
				if(done)
					ans+=Sum(minGreen);
				else
					ans+=Sum(fs);
			}
		}
		return ans;
	}
};

