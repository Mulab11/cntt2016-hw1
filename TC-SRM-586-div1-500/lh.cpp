#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class History{
	private:
		static const int maxn=27,maxm=11;
		typedef pair<int,int> rec;
		int tim[maxn][maxm][2],num[maxn],n;
		rec mp[maxn][maxn];
		
		static void join(rec &a,rec b);
		
	public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries){
		n=dynasties.size();
		for (int i=0;i<n;++i){
			bool fl=false;
			for (int j=0;j<dynasties[i].length();++j){
				if (dynasties[i][j]==' '){
					if (fl) ++num[i];
				}
				else{
					fl=true;
					tim[i][num[i]][0]=tim[i][num[i]][0]*10+dynasties[i][j]-'0';
				}
			}
			while(tim[i][num[i]][0]==0) num[i]--;
			for (int j=0;j<num[i];++j) tim[i][j][1]=tim[i][j+1][0]-1;
		}
		for (int i=0;i<n;++i)
		for (int j=0;j<n;++j) if (i==j) mp[i][j]=rec(0,0);
		else mp[i][j]=rec(-300000000,300000000);
		
		string cc;
		for (int i=0;i<battles.size();++i) cc+=battles[i];
		for (int j=0;j<cc.length();++j) if (cc[j]!=' '){
			int a=cc[j]-'A',b=cc[j+1]-'0',
			c=cc[j+3]-'A',d=cc[j+4]-'0';
			
			int x=tim[a][b][0]-tim[c][d][1];
			int y=tim[a][b][1]-tim[c][d][0];
			join(mp[a][c],rec(x,y));
			join(mp[c][a],rec(-y,-x));
			
			j+=5;
		}
		
		for (int k=0;k<n;++k)
		for (int i=0;i<n;++i) if (i!=k)
		for (int j=0;j<n;++j) if (j!=i&&j!=k)
		join(mp[i][j],rec(mp[i][k].first+mp[k][j].first,mp[i][k].second+mp[k][j].second));
		
		string ret;
		for (int i=0;i<queries.size();++i){
			int a=queries[i][0]-'A',b=queries[i][1]-'0',c=queries[i][3]-'A',d=queries[i][4]-'0';
			rec tmp(tim[a][b][0]-tim[c][d][1],tim[a][b][1]-tim[c][d][0]);
			join(tmp,mp[a][c]);
			if (tmp.first<=tmp.second) ret+="Y";
			else ret+="N";
		}
		return ret;
	}
};

void History::join(rec &a,rec b){
	if (a.first<b.first) a.first=b.first;
	if (a.second>b.second) a.second=b.second;
	return;
}

