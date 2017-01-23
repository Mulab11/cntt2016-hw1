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

ld w;
ld solve(int n,ld l,ld h){
	if(!n) return 0;
	ld tmp=(ld)((n-1)*l+w)*h/2-(n-1)*h*l/(w+l)/2-solve(n-1,w*l/(w+l),h*w/(w+l));
	return tmp;
}//表示层数为n，两个点宽度为l，高度h构成图形的答案 
class TriangleXor{
public:
	int theArea(int W){
		w=W;
		return (int)solve(w+1,1,1);
	}
};

