#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#include<string>
using namespace std;
int n,m;int codeforces=0;
class IncrementAndDoubling
{
public:
	int getMin(vector <int> desiredArray)
	{
		int f[66]={};
		int n=desiredArray.size();
		for(int i=0;i<n;i++)
			f[i]=desiredArray[i];
		while(true)
		{
			int flag=0;
			for(int i=0;i<n;i++)
				if(f[i]&1)
				{flag=1;f[i]--;codeforces++;break;}
				else if(f[i]>0)
					flag=2;
			if(flag==2)
			{
				codeforces++;
				for(int i=0;i<n;i++)
					f[i]/=2;
			}
			if(!flag)
				break;
		}
		return codeforces;
	}
};
