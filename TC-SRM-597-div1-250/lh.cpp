#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LittleElephantAndString{
	private:
	int cnt[28];
	public:
	int getNumber(string A, string B){
		int n=A.length();
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<n;++i){
			++cnt[A[i]-'A'];
			--cnt[B[i]-'A'];
		}
		for (int i=0;i<26;++i) if (cnt[i]!=0) return -1;
		int ll=n-1;
		for (int i=n-1;i>=0;--i) if (A[i]==B[ll]) --ll;
		return n-(n-(ll+1));
	}
};