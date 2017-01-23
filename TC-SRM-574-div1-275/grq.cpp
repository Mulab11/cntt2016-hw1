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

vi a,b;
int n,m;
vi calc(int n){
	vi a;a.clear();
	while(n) a.pb(n%10),n/=10;
	return a;
}

class TheNumberGame{
public:
	string determineOutcome(int A, int B){
		a=calc(A);b=calc(B);
		n=a.size();m=b.size();
		for(int i=0;i+m<=n;i++){
			bool isok=1;
			for(int j=0;j<m;j++)
				if(b[j]!=a[i+j]) isok=0;
			if(isok) return "Manao wins";
		}
		reverse(a.begin(),a.end());
		for(int i=0;i+m<=n;i++){
			bool isok=1;
			for(int j=0;j<m;j++)
				if(b[j]!=a[i+j]) isok=0;
			if(isok) return "Manao wins";
		}
		return "Manao loses";
	}
};
