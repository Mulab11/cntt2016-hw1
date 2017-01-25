#include <vector>
#include <string>
using namespace std;
class PastingPaintingDivOne{
public:
	int min(int a,int b){return a<b?a:b;}
	int max(int a,int b){return a>b?a:b;}
	int f(char c){return c=='R'?0:c=='G'?1:2;}
	void solve(string line,int T,vector<long long>&ans){
		int n=line.length();
		vector<int> next(n);next[n-1]=n-1;
		for(int i=n-2;i>=0;i--)next[i]=line[i]!='.'?i:next[i+1];
		if(line[next[0]]=='.')return;
		if(T>n){
			for(int i=0;i<n;i++)
				if(next[i]<n&&line[next[i]]!='.')ans[f(line[next[i]])]++;
			ans[f(line[next[0]])]+=T-next[0]-1;
		}
		else for(int i=0;i<n+T-1;i++){
			int l=max(i-T+1,0),r=min(i,n-1);
			if(next[l]<=r&&line[next[l]]!='.')ans[f(line[next[l]])]++;
		}
	}
	vector<long long> countColors(vector <string> clipboard, int T){
		vector<long long> ans;
		for(int i=0;i<3;i++)ans.push_back(0);
		for(int b=-clipboard[0].length()+1;b<(int)clipboard.size();b++){
			string line;
			for(int x=max(-b,0),y=x+b;x<clipboard[0].length()&&y<clipboard.size();x++,y++)
				line.push_back(clipboard[y][x]);
			solve(line,T,ans);
		}
		return ans;
	}
};
