#include<bits/stdc++.h>
using namespace std;
int n,a[666],i,m,j,f,g;
double ans;
string s;
class EllysRoomAssignmentsDiv1
{
	public:
		double getAverage(vector<string> A)
		{
			for(auto x : A)s+=x;
			for(auto x : s)x==' '?n++:a[n]=a[n]*10+x-48;
			for(i=n;~i;i--)a[i]*=2;
			for(a[0]++,m=n/20+1,sort(a,a+n+1),i=n;i>=0;i-=m)//暴力讨论每个组
			{
				for(f=g=0,j=i;~j&&j>i-m;j--)if(g+=a[j]/2,a[j]&1)f=a[j]/2;
				if(f)ans+=f;else if(i-m>-2)ans+=1.*g/m;else return 1.*(m-(n+1)%m)/m*ans/((n+1)/m)+1.*((n+1)%m)/m*(ans+1.*g/((n+1)%m))/(n/m+1);
			}
			return ans/(n/m+1);
		}
};
