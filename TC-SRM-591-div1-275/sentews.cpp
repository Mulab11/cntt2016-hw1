#include<algorithm>
#include<string>
#include<vector>
using namespace std;
int f[2111]={};
class TheTree
{
public:
	int maximumDiameter(vector <int> cnt)
	{
		int n=cnt.size(),m=n;
		for(int i=0;i<n;i++)
			f[i]=cnt[i];
		for(int i=n,j=n;i>=1;i--)
		{
			if(f[i]<2)j=i;
			m=max(m,n+j-i-i);
		}
		for(int i=1;i<=n;i++)
			if(f[i-1]>=2)
				m=max(m,n+i);
		else break;
		return m;
	}
};
