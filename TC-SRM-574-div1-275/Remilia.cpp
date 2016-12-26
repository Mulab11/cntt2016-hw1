#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxn=15;
int n1[maxn],n2[maxn];
/*
胜利的充要条件是：
B或rev(B)是A的子串
*/
struct TheNumberGame{
	string determineOutcome(int a,int b){
		while (a) n1[++*n1]=a%10,a/=10;
		while (b) n2[++*n2]=b%10,b/=10;
		rep(i,1,*n1-*n2+1){
			bool f=1;
			rep(j,i,i+*n2-1) if (n2[j-i+1]!=n1[j]){f=0;break;}
			if (f) return "Manao wins"; 
		}
		rep(i,1,*n2/2) swap(n2[i],n2[*n2-i+1]);
		rep(i,1,*n1-*n2+1){
			bool f=1;
			rep(j,i,i+*n2-1) if (n2[j-i+1]!=n1[j]){f=0;break;}
			if (f) return "Manao wins"; 
		}
		return "Manao loses";
	}
};
