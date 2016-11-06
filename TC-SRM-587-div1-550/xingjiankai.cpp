#include <bits/stdc++.h>
using namespace std;
class TriangleXor
{
public:
	int theArea(int n)
	{
		double ans=1.0*(n+1)*n/2.0;
		for(int i=1;i<=n;i++)
		{
			if(i&1) ans-=1.0*(n+1-i)*n/(n+i)*n;
			else ans+=1.0*(n+1-i)*n/(n+i)*n;
		}
		return (int)ans;
	}
};
int main()
{
	TriangleXor a;
	printf("%d\n",a.theArea(62678));
}