#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
int f[111111]={};int nn;
using namespace std;
class FoxAndMountainEasy
{
public:
	string possible(int n, int h0, int hn, string history)
	{
		nn=history.size();
		int d=0,minn=0,maxx=0;
		for(int i=0;i<history.size();i++)
		{
			if(history[i]=='U')
				d++;
			else
				d--;
			if(d>maxx)
				maxx=d;
			if(d<minn)
				minn=d;
		}
		int dd=h0;
		n=n-history.size();
		if(dd<-minn)
			dd=-minn,n-=(-minn-dd);
		dd+=d;
		dd=abs(hn-dd);
		return dd>n||(n&1)?"NO":"YES";
	}
};
