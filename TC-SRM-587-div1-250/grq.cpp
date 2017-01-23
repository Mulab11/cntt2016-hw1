#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

class JumpFurther{
public:
	int furthest(int N, int badStep){
		bool isok=1;
		for(int i=1;i<=N;i++)
			if(i*(i+1)/2==badStep) isok=0;
		if(isok) return N*(N+1)/2;
		return N*(N+1)/2-1;
		//判断是否会达到badStep，判断从最大值减一 
	}
};

