#include<bits/stdc++.h>
using namespace std;
int v[1010],i,j;
long long s=1;
class LittleElephantAndIntervalsDiv1
{
	public:
		long long getNumber(int n,vector<int>L,vector<int>R)
		{
			for(i=1;i<=n;i++)for(j=L.size()-1;~j;--j)if(i>=L[j]&&i<=R[j])
			{
				s<<=!v[j];
				v[j]=1;
				break;
			}
			return s;
		}
};
