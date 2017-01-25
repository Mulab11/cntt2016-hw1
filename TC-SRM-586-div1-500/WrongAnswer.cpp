#include <vector>
#include <string>
using namespace std;
class History{
public:
	void cmin(int&a,int b){b<a?a=b:1;}
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries){
		int n=dynasties.size(),t[n][11],G[n][n],c,x,y,p,q,d;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)G[i][j]=i==j?0:23333333;
			for(int j=0,m=t[i][0]=0;j<dynasties[i].length();j++)(c=dynasties[i][j])==' '?t[i][++m]=0:(t[i][m]*=10)+=c-'0';
		}
		for(int i=0,tot=0;i<battles.size();i++)
			for(int j=0;j<battles[i].length();j++)
				c=battles[i][j],++tot%6==1?x=c-'A':tot%6==2?p=c-'0':tot%6==4?y=c-'A':tot%6==5?
					cmin(G[x][y],t[x][p+1]-t[x][0]-t[y][q=c-'0']+t[y][0]-1),cmin(G[y][x],t[y][q+1]-t[y][0]-t[x][p]+t[x][0]-1),1:1;
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)cmin(G[i][j],G[i][k]+G[k][j]);
		string ans;
		for(int i=0;i<queries.size();i++){
			x=queries[i][0]-'A',y=queries[i][3]-'A',p=queries[i][1]-'0',q=queries[i][4]-'0',d=t[x][p]-t[x][0]-t[y][q]+t[y][0];
			ans.push_back(G[x][y]<=d-t[y][q+1]+t[y][q]||-G[y][x]>=d+t[x][p+1]-t[x][p]?'N':'Y');
		}
		return ans;
	}
};
