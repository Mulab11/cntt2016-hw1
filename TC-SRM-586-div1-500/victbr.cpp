#include <bits/stdc++.h>

using namespace std;

const int N = 30;

class History{
	public:
		int a[N][N],b[N],f[N][N];
		string s,ans;
		string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries){
			memset(f,0x3f,sizeof(f));
			for (int i = 0;i < dynasties.size();i++){
				int tot = 0;
				for (int j = 0;j < dynasties[i].size();j++)
					if (dynasties[i][j] == ' '){
						b[i]++;
						a[i][b[i]] = tot; tot = 0;
					}
					else tot = tot*10+dynasties[i][j]-'0';
				b[i]++;
				a[i][b[i]] = tot;
				/*
				for (int j = 1;j <= b[i];j++)
					printf("%d ",a[i][j]);
				printf("\n");
				*/
				for (int j = 1;j <= b[i];j++)//注意第i个人的时间是ai~a(i+1)-1而不是时间长度为ai 
					a[i][j-1] = a[i][j]-1;
			}
			for (int i = 0;i < battles.size();i++)
				s = s + battles[i];
			bool flag = 0;
			int c1,c2,tot = 0,p1,p2;
			for (int i = 0;i < s.size();i++){
				if (s[i] == '-') {flag = 1;p1 = tot;tot = 0;}
				if (s[i] == ' ') {flag = 0;
					p2 = tot;tot = 0;
					f[c1][c2] = min(f[c1][c2],a[c1][p1+1]-a[c2][p2]-1);
					f[c2][c1] = min(f[c2][c1],a[c2][p2+1]-a[c1][p1]-1);	
				}
				if ('A' <= s[i] && s[i] <= 'Z')
					if (flag) c2 = s[i]-'A';
					else c1 = s[i]-'A';
				if ('0' <= s[i] && s[i] <= '9') tot = tot * 10 + s[i]-'0';
			}
			p2 = tot;
			f[c1][c2] = min(f[c1][c2],a[c1][p1+1]-a[c2][p2]-1);
			f[c2][c1] = min(f[c2][c1],a[c2][p2+1]-a[c1][p1]-1);
//			printf("%d %d\n",c1,c2);
			for (int k = 0;k < 26;k++)
				for (int i = 0;i < 26;i++)
					for (int j = 0;j < 26;j++)
						f[i][j] = min(f[i][j],f[i][k]+f[k][j]);
/*
			for (int i = 0;i < 26;i++){
				for (int j = 0;j < 26;j++)
					if (f[i][j] < 1000000)
						printf("%d %d %d\n",i,j,f[i][j]);
				printf("\n");	
			}*/
			for (int i = 0;i < queries.size();i++){
				int c1,c2,tot = 0,p1,p2;
				bool flag = 0;
				for (int j = 0;j < queries[i].size();j++){
					if (queries[i][j] == '-') {flag = 1;p1 = tot;tot = 0;}
					if (queries[i][j] == ' ') {flag = 0;p2 = tot;tot = 0;}
					if ('A' <= queries[i][j] && queries[i][j] <= 'Z')
						if (flag) c2 = queries[i][j]-'A';
						else c1 = queries[i][j]-'A';
					if ('0' <= queries[i][j] && queries[i][j] <= '9') tot = tot * 10 + queries[i][j]-'0';
				}
				p2 = tot;
//				printf("%d %d\n",p1,p2);
//				printf("%d %d %d %d\n",c1,c2,f[c1][c2],f[c2][c1]);
//				printf("%d %d %d %d\n",a[c1][p1],a[c1][p1+1],a[c2][p2],a[c2][p2+1]);
				if (f[c1][c2] < a[c1][p1]+1-a[c2][p2+1]) ans = ans + 'N';
				else if (f[c2][c1] < a[c2][p2]+1-a[c1][p1+1]) ans = ans + 'N';
				else ans = ans + 'Y';
				
			}
			return ans;		
		}
}A;


