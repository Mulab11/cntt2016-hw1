#include<bits/stdc++.h>
using namespace std;
class KnightCircuit2
{
	public:
		int maxSize(int n,int m)
		{
			if(min(n,m)==1)return 1;
			if(min(n,m)==2)return max(n,m)+1>>1;
			if(n+m==6)return 8;
			return n*m;
		}
};
