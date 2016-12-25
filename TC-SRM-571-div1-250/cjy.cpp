#include<bits/stdc++.h>
using namespace std;
int k,n;
vector<string> a;
void dfs(string x){if(x.size()){if(k>=min(n,50)||stoll(x)>n)return;a.push_back(x+".mp3");k++;}for(char c=48;c<58;c++)if(c!=48||x.size())dfs(x+c);}
class FoxAndMp3
{
	public:
		vector<string> playList(int N){n=N;dfs("");return a;}
};
