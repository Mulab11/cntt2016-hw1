#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;

class LittleElephantAndIntervalsDiv1
{
	public:
	int c[1005],v[55];
	LL getNumber(int M,vector<int> L,vector<int> R)
	{
		//For each operation, if it can determine at least one ball in the last situation,
		//we have 2 choice for these balls, and the answer should multiply by 2
		//Therefore, let x be the number of operations described above, the answer is 2^x.
		for(int i=0;i<L.size();i++)
			for(int j=L[i];j<=R[i];j++)
				c[j]=i+1;
		//c[i]: the i-th ball is determined by operation i
		for(int i=1;i<=M;i++)
			v[c[i]]=1;
		int x=0;
		for(int i=1;i<=L.size();i++)
			x+=v[i];
		return 1LL<<x;
	}
};

