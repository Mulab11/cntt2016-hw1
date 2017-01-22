#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class FoxAndChess{
	public:
	string ableToMove(string a, string b){
		if (a.length()!=b.length()) return "Impossible";
		int n=a.length(),j=0;
		
		for (int i=0;i<n;++i) if (a[i]!='.'){
			while(j<n&&b[j]=='.') ++j;
			if (j==n) return "Impossible";
			if (a[i]!=b[j]) return "Impossible";
			//printf("i=%d,j=%d,%c\n",i,j,a[i]);
			if (a[i]=='L'){
				if (i<j) return "Impossible";
			}
			else{
				if (i>j) return "Impossible";
			}
			++j;
		}
		//puts("xxxxxxxxxx");
		while(j<n&&b[j]=='.') ++j;
		//printf("j=%d\n",j);
		if (j!=n) return "Impossible";
		return "Possible";
    }
};