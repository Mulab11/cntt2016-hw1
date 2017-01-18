#include<bits/stdc++.h>
using namespace std;
int n,i,j,x=99,k;
vector<int> s;
class TheBrickTowerMediumDivOne
{
	public:
		vector<int> find(vector<int> a)
		{
			for(n=a.size();i<n;i++,a[k]=99,s.push_back(k))
			{
				for(k=0;k<n&&a[k]>x;k++);
				if(k<n)x=a[k];else for(k=j=0;j<n;j++)if(a[j]<a[k])k=j;
			}
			return s;
		}
};
