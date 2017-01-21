// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndAvatar.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class FoxAndAvatar{
	#define X(u) (((u)-1)/width)
	#define Y(u) (((u)-1)%width)
	bool ans_is_t(int n,int width,int x,int t){
		if (t==0) return n==1;
		if (t==1){
			if (width==1&&x==1) return 1;//down
			if (x==n&&Y(x)==0) return 1;//up
			if (x==1&&n<=width) return 1;//right
			if (x==n&&x<width||x==width&&n<width*2) return 1;//left
			return 0;
		}
		for (int i=X(x);i;--i)for (int j=width;j;--j)
			if (ans_is_t(n-i*j,width,x-i*j,t-1)) return 1;
		int z=(width-x%width)%width;
		if (ans_is_t(n-z*(n/width-X(x))-max(0,n%width+z-n),width,x,t-1)) return 1;
		if (X(x)!=X(n)&&ans_is_t(width*(X(x)+1),width,x,t-1)) return 1;
		for (int i=X(x);i>=0;--i)for (int j=Y(x);j;--j)
			if (ans_is_t(n-(n/width-i)*j-min(n%width,j),width,x-(X(x)+1-i)*j,t-1)) return 1;
		for (int i=X(x)-1;i>=0;--i)for (int j=width-Y(x)-1;j;--j)
			if (ans_is_t(n-(n/width-i)*j-min(max(0,n%width-X(x)-1),j),width,x-(X(x)-i)*j,t-1)) return 1;
		return 0;
	}
	public:
	int minimalSteps(int n, int width, int x){
		for (int i=0;i<4;++i) if (ans_is_t(n,width,x,i)) return i;
		return 4;
	}
};

//this is for test
/*
int main(){
	FoxAndAvatar test;
	printf("%d\n",test.minimalSteps(36,4,14));
//	test.run_test(-1);
	return 0;
}
*/
//test end
