#include<string>
#include<algorithm>
using namespace std;
int a[111]={},b[111]={};
int ta=0,tb=0;
string codeforces="Impossible";
string codeforces2="Possible";
class FoxAndChess
{
public:
	string ableToMove(string begin, string target)
	{
		int n=begin.size();
		for(int i=0;i<n;i++)
		{
			if(begin[i]=='R')
				a[ta++]=i+1;
			else if(begin[i]=='L')
				a[ta++]=-i-1;
			if(target[i]=='R')
				b[tb++]=i+1;
			else if(target[i]=='L')
				b[tb++]=-i-1;
		}
		if(ta!=tb)return codeforces;
		n=ta;
		for(int i=0;i<n;i++)
			if(a[i]>0^b[i]>0)
				return codeforces;
			else if(a[i]>b[i])
				return codeforces;
		return codeforces2;
	}
};
