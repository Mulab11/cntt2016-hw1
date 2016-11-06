#include <bits/stdc++.h>
using namespace std;
class JumpFurther
{
public:
	int furthest(int n,int m)
	{
		int tmp=0,ans=n*(n+1)/2;
		for(int i=1;i<=n;i++) 
		{
			tmp+=i;
			if(tmp==m) return ans-1;
		}
		return ans;
	}
}a;
int main()
{
	printf("%d\n",a.furthest(3,3));
}