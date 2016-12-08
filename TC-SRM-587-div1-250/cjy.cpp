#include<bits/stdc++.h>
using namespace std;
class JumpFurther
{
	public:
		int furthest(int n,int b)
		{
			int i,s=0;
		 	for(i=1;i<=n&&i*(i+1)/2<=b;i++)if(i*(i+1)/2==b)s--;
		 	return s+n*(n+1)/2;
		}
};
