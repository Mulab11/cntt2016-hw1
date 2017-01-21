// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndRGB.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 2505


class LittleElephantAndRGB{
	int a[N],n;
	int lcnt[N],lclosest[N];
	int rcnt[N],rclosest[N];
	public:
	long long getNumber(vector <string> list, int minGreen){
		ll ret=0;
		n=0;
		for (int i=0;i<list.size();++i)
			for (int j=0;j<list[i].length();++j)
				a[++n]=list[i][j]=='G';
		lcnt[0]=lclosest[0]=0;
		for (int i=1;i<=n;++i){
			lcnt[i]=a[i]*(a[i]+lcnt[i-1]);
			if (lcnt[i]>=minGreen) lclosest[i]=i-minGreen+1;
			else lclosest[i]=lclosest[i-1];
		}
		rcnt[n+1]=0;rclosest[n+1]=n+1;
		for (int i=n;i;--i){
			rcnt[i]=a[i]*(a[i]+rcnt[i+1]);
			if (rcnt[i]>=minGreen) rclosest[i]=i+minGreen-1;
			else rclosest[i]=rclosest[i+1];
		}

#define llen (i-lclosest[i])
#define rlen (rclosest[j]-j)
		for (int i=1;i<=n;++i)
			for (int j=i+1;j<=n;++j){
//				printf("%d %d %lld\n",i,j,ret);
//				printf("%d %d %d %d\n",lclosest[i],i,(n-j+1),(n-rclosest[j]+1));
				ret+=lclosest[i]*(n-j+1)+i*(n-rclosest[j]+1)-lclosest[i]*(n-rclosest[j]+1);
				int lc=min(lcnt[i],llen),rc=min(rcnt[j],rlen);
				if (lc+rc<minGreen) continue;
				ret+=(lc+rc-minGreen+1)*(lc+rc-minGreen+2)/2;
				ret+=(llen-lc+rlen-rc)*(lc+rc-minGreen+1);
				ret+=(llen-lc)*(rlen-rc);
			}
		return ret;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndRGB test;
	vector<string> a;
	a.push_back("BGGBGRRGBBBGRGBGBRRRRBRGGRBBBBRBRRGBGGRBRBRBRGBGBBGRRGBRGGGBBRRGGBGGBRBRGBRRBRBRGRBGBBGRRBGBGBRRBRBGRRRRBBRBBBGRRBRRRGRBBBRGBGBGRGGGRBGRGBRRBBGBBRBGBGRBRBRBGRBBRGRBBGBGRRRRRGGRBGRBRBGBBGRGBRRBGBBBRBBGBGRBGRGBRGRRGRGBRRRRBBBBBGGRRGGBBGBBBRGGRBRBRRBGBBBGRRRBRBRGBBRGBBBBRGBRRRRGGGBGGGRRGBBRBBBGRBGBGGBGRGRBRGGGGGGRGGBRGBGBGRRGBGBBGRGRBBBBRGGRGGRBGGRBGBBBRRRBRBBRGRGBBBGBRBBGBBRRBRBGBBGRBGBBBBRBBGBGBRGGGBBRGRRRBBGBBBGBBRBBGGBGBBBGGBBGRBGBGBGGBGRGBGRBGGRRGBGBRBGRRRGRGRBRGGBGBBGRBBGGBGGGGBGGRRBRGRBGBGBBRGGGGBBRRGBGGBRBBGGBRRRRGRGRGGRGGGBRRRGRRRBBGBRRBBRRGBGGRBBRBRGGBBBRBBGBRGBRBRGGRRBBBRBGGRGGRGBBRGRGBRBRGRGRBBBGRBRBRGBGBBBGRGBBBBRBGRRGGRRRGRBBBBRGGRGRGRRBRGGBRBGRBRBGGBRRGRRGGGGRRGBRRBBGRBGGRRBRBRGBRGRBGRRGBRRGGBBBBBRBGBBBBRRGGRGRRGBGGRRBBBBBRGRRRRGRRGGBBBBRBGRBRGRGGRBBRBRGRGGRBGGRRBBGGRBGGBBRBBRBRGBBGRGRGGGRBGRBGRRGBGGBRRBRRGRGGRGGRRBRGBRRGBBGRBGGGGRGBBBRBGRBGRGRGRBRBBRGBRRBGRRGBRBBRBGBBRRGGBGRRGRGRRBRRRRRRBBBGBGGRGGGGGBGRBGRGRGRBGGRGBGRGGBRBGBRBBGBRRRGRBRRRGRGRBRRGRGBRBGRGRGBRGBRGRGGRGRGBGRGGBRGGRBBBGGGBBRBGRBBBGBBRGBRRGBGGGBBGRBBGRGBRBRBRRGRRGRBRGGBGGRBBRBGGGBGRGBBRBBRGBRBRRRBGGRBGRBBRRGBRRRRRBBBRGGRRGRRGBGRBBBGGRGRBBGBGRRGRRRRGGRRGRGGGGGBRGRRRRRRGRBGRRGGRRGGBBRGGBGGBRRGGBGRRRRRBGRGBRRBRRRBRRGBBBGBGRGRGBGBRBGBRRBBRRGGGGGRBRGRRRRGBRRGRGGBBGBBGBBGRGRGGGRRBGRBBBRRBGBGBBRGBBBRRRGRRBGGBRBRBRRRGBBBGBGGRRBRBRRBBGRRBG");
	printf("%lld\n",test.getNumber(a,15));
//	test.run_test(-1);
	return 0;
}
*/
//test end
