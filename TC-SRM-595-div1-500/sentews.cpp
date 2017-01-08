#include<algorithm>
#include<string>
#include<vector>
using namespace std;
int m,n;
char f[3333]={};int tot=0;
class LittleElephantAndRGB
{
public:
	long long getNumber(vector <string> list, int minGreen)
	{
		for(int i=0;i<list.size();i++)
			for(int j=0;j<list[i].size();j++)
				f[tot++]=list[i][j];
		int m=minGreen;
		long long codeforces=0;
		int last=-1,end=0;n=tot;
		for(int i=0;i<n-1;i++)
		{
			if(f[i]=='G')end++;
			else
				end=0;
			int next=n;
			if(end>=m)
				last=i-m+1;
			int s=0;
			for(int j=n-1;j>i;j--)
			{
				if(f[j]=='G')
					s++;
				else
					s=0;
				if(s>=m)
					next=j+m-1;
				int x=min(end,m-1),y=min(s,m-1);
				codeforces+=(last+1)*(n-j);
				int temp=last;
				int k=x+y-m;
				if(k>=0)
					codeforces+=(i-x+1-temp)*(n-j-m+x+1),codeforces+=k*(n-j-m+x+1)-k*(k+1)/2,temp=i-x+1+k;
				codeforces+=(i-temp)*(n-next);
			}
		}
		return codeforces;
	}
};
