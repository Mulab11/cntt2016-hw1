#include <bits/stdc++.h>

using namespace std;

int nd[55][55],gs[55],f[55][55],n;

class History {
public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {
		memset(f,0x3f,sizeof f);
		n=dynasties.size();
		for(int i=0;i<n;++i)f[i][i]=0;
		for(int i=0;i<dynasties.size();++i){
			stringstream s(dynasties[i]);
			int tmp;
			while(s>>tmp)nd[i][gs[i]++]=tmp;
		}//读入 
		string str;
		for(int i=0;i<battles.size();++i)str+=battles[i];
		for(int i=0;i<str.size();i+=6){
			int x=str[i]-'A',xx=str[i+1]-'0';
			int y=str[i+3]-'A',yy=str[i+4]-'0';
			f[y][x]=min(f[y][x],nd[y][yy+1]-1-nd[x][xx]);
			f[x][y]=min(f[x][y],nd[x][xx+1]-1-nd[y][yy]);
			//建图 
		}
		for(int k=0;k<n;++k)
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);//floyd
		string ret;
		for(int i=0;i<queries.size();++i){
			str=queries[i];
			int x=str[0]-'A',xx=str[1]-'0';
			int y=str[3]-'A',yy=str[4]-'0';
			if(f[x][y]+nd[y][yy+1]-1-nd[x][xx]>=0&&f[y][x]+nd[x][xx+1]-1-nd[y][yy]>=0)ret+="Y";
			else ret+="N";//根据最短路的结果判断不等式是否合法 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
