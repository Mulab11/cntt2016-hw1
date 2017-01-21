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


class LittleElephantAndString {
public:
	int cnt[26];
	int getNumber(string A, string B) {
		int n=A.size(),k=n-1;
		memset(cnt,0,sizeof(cnt));
		for(int i=n-1;i>=0;i--){
			if(A[i]==B[k]) k--;
			cnt[A[i]-'A']++;cnt[B[i]-'A']--;
		}//寻找B串最长的是A串的子序列的后缀 
		for(int i=0;i<26;i++) if(cnt[i]) return -1;
		return k+1;
	}
};
