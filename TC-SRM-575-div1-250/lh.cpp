#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheNumberGameDivOne{
	public:
		string find(long long n){
			if (n&1) return "Brus";
			if ((n&(-n))==n){
				int cnt=0;
				while(n>1){
					n>>=1;
					++cnt;
				}
				if (cnt&1) return "Brus";
				else return "John";
			}
			return "John";
		}
};
