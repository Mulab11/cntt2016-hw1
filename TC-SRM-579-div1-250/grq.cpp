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

const int N=5005;
int a[N][26],cnt;

int ins(string s){
	int now=0,bx2k=0;
	for(int i=0;i<s.size();i++){
		if(!a[now][s[i]-'a']) a[now][s[i]-'a']=++cnt; else bx2k++;
		now=a[now][s[i]-'a'];
	}
	return bx2k;
}

class UndoHistory{
public:
	int minPresses(vector<string> lines){
		memset(a,0,sizeof(a));
		cnt=0;
		int ans=lines.size();
		ans+=lines[0].size()-ins(lines[0]);
		for(int i=1;i<lines.size();i++){
			int isok=0,res=10005;
			if(lines[i-1].size()>lines[i].size()) isok=1;
			for(int j=0;j<lines[i-1].size();j++)
				if(lines[i-1][j]!=lines[i][j]) isok=1;
			if(!isok) res=lines[i].size()-lines[i-1].size();
			ans+=min(res,(int)lines[i].size()-ins(lines[i])+2);
		}
		return ans;
	}
};

