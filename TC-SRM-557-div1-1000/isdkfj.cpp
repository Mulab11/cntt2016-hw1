#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
LL a[55];
int n;

class XorAndSum {
public:
	long long maxSum(vector<long long> number) {
		n=number.size();
		for(int i=0;i<n;++i)a[i+1]=number[i];
		int m=0;
		for(int d=50;d>=0;--d){//求线性基 
			int p=-1;
			for(int i=m+1;i<=n;++i)if((a[i]>>d)&1){p=i;break;}
			if(p==-1)continue;
			++m;swap(a[m],a[p]);
			for(int i=m+1;i<=n;++i)if((a[i]>>d)&1)a[i]^=a[m];
		}
		LL x=0;
		for(int i=1;i<=m;++i)if((x^a[i])>x)x^=a[i];//求出能异或出的最大的数 
		LL ret=x*(n-m);//除了基之外都是这个数 
		for(int i=1;i<=m;++i){//贪心 
			for(int j=1;j<=m;++j)if((a[i]^a[j])>a[i])a[i]^=a[j];
			ret+=a[i];
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
