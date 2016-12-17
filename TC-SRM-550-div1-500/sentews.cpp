#include<cstdio>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
char slove(long long a,long long x0,long long y0,long long j,long long i,long long t)
{
	if(a>=(t<<1)||((x0^i^y0^j)&1)||((a>>1)&y0+j)!=y0+j)return '.';
	else if(a&3)return 'B';
	else return 'A';
}
class CheckerExpansion
{
	public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)
	{
		vector<string> ans;
		for(int i=0;i<h;i++)
		{
			string temp;
			for(int j=0;j<w;j++)
				temp+=slove(x0+y0+i+j,x0,y0,i,j,t);
			ans.push_back(temp);
		}
		reverse(ans.begin(),ans.end());
		return ans;
	}
};
