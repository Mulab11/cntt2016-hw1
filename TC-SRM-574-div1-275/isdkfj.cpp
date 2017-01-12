#include <bits/stdc++.h>

using namespace std;

int s1[55],s2[55],n,m;

bool work(){//判断是否是子串 
	for(int i=1;i<=n-m+1;++i){
		bool flag=1;
		for(int j=i;j<=i+m-1;++j)if(s1[j]!=s2[j-i+1])flag=0;
		if(flag)return 1;
	}
	return 0;
}

class TheNumberGame {
public:
	string determineOutcome(int A, int B) {
		while(A)s1[++n]=A%10,A/=10;
		while(B)s2[++m]=B%10,B/=10;
		if(n<m)return "Manao loses";
		if(work())return "Manao wins";
		reverse(s2+1,s2+m+1);//反转 
		if(work())return "Manao wins";
		return "Manao loses";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
