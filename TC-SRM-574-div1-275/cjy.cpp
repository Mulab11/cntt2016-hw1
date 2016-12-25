#include<bits/stdc++.h>
using namespace std;
int a[20],b[20],n,m;
class TheNumberGame
{
	public:
		int Win()//判断b是否是a的子串
		{
			for(int i=1;i+m-1<=n;i++)
			{
				for(int j=1;j<=m;j++)if(a[i+j-1]!=b[j])goto E;
				return 1;E:;
			}
			return 0;
		}
		string determineOutcome(int A, int B)
		{
			while(A)a[++n]=A%10,A/=10;
			while(B)b[++m]=B%10,B/=10;
			if(Win()||(reverse(b+1,b+m+1),Win()))return"Manao wins";
			return"Manao loses";
		}
};
