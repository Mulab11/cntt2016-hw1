// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorCards.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=70;
ll bin[maxn];

class XorCards{
	ll a[maxn];
	int s[maxn];
	public:
	long long numberOfWays(vector<long long> number, long long limit){
		for (int i=0;i<=50;++i) bin[i]=1LL<<i;
		memset(a,0,sizeof(a));
		int cnt=0;
		for (int i=0;i<number.size();++i){
			ll tmp=number[i];
			for (int j=50;j>=0;--j)if (tmp&bin[j]){
				if (a[j]) tmp^=a[j];
				else{a[j]=tmp;break;}
			}
			if (!tmp) ++cnt;
		}
//		printf("%d\n",cnt);
		s[0]=0;
		for (int i=1;i<=50;++i) s[i]=s[i-1]+(a[i-1]>0);
//		for (int i=0;i<=50;++i) printf("%d ",s[i]);puts("");
		ll ret=1,now=0;
		for (int i=50;i>=0;--i)if(a[i]>0){
			if (limit&bin[i]) ret+=bin[s[i]];
//			printf("%d %lld\n",i,ret);
			if ((now&bin[i])!=(limit&bin[i])) now^=a[i];
		}
		else if ((now&bin[i])>(limit&bin[i])){--ret;break;}
		else if ((now&bin[i])<(limit&bin[i])){ret+=bin[s[i]]-1;break;}
		return ret*bin[cnt];
	}
};

//this is for test
/*
int main(){
	XorCards test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
