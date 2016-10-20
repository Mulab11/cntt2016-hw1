// BEGIN CUT HERE

// END CUT HERE
#line 5 "DefectiveAddition.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int P=1000000007;
int inv[33];

class DefectiveAddition{
	public:
	int count(vector <int> cards, int n){
		inv[0]=1;
		for (int i=inv[0]=1;i<=29;++i) inv[i]=(ll)inv[i-1]*((P+1)>>1)%P;//calc inv of 2^i
		int ret=0;
		for (int i=29;i>=0;--i){
			int bit=1<<i,cnt=0;
			ll s0=1,s1=0;//s0->bit i is 0. s1->bit i is 1.
			for (int j=0;j<cards.size();++j)if (cards[j]&bit){//calc s0&s1
				cnt^=bit;
				cards[j]^=bit;
				ll tmps0=s0;
				s0=(s0*bit+s1*(cards[j]+1))%P;
				s1=(s1*bit+tmps0*(cards[j]+1))%P;
			}
			else (s0*=cards[j]+1)%=P,(s1*=cards[j]+1)%=P;
			ll res=(n&bit)?s1:s0;
			if (cnt==(n&bit)&&i){//if no element can be ranged from[0,2^i),remove the invalid part.
				int s=1;
				for (int j=0;j<cards.size();++j)
					s=(ll)s*(cards[j]+1)%P;
				(res+=P-s)%=P;
			}
			(res*=inv[i])%=P;//if one element can be ranged from[0,2^i),the other all element can will be free.
			(ret+=res)%=P;
			if (cnt!=(n&bit)) break;//there must be one element ranged from[0,2^i)
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	DefectiveAddition test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
