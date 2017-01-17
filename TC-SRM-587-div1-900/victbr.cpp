#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class ThreeColorability{
	public:
		vector<string> ans,noanswer;
		string ss[N];
		int a[N][N],b[N][N],first[N],efn,n,m,dis[N];
		bool vist[N];
    	vector<string> lexSmallest(vector<string> s){
    		n = s.size();
    		m = s[0].size();
			memset(b,-1,sizeof(b));
    		for (int i = 0;i < n;i++)//a数组中，1为N，2为Z；b数组中，0为相同，1为不同。 
				for (int j = 0;j < m;j++){
					if (s[i][j] == 'N') a[i][j] = 1; 
					if (s[i][j] == 'Z') a[i][j] = 2;
				}
			for (int i = 0;i < n;i++)
				for (int j = i+1;j < n;j++)
					for (int k = 0;k < m;k++){
						if (a[i][k] == a[j][k] && a[i][k] != 0){
							if (b[i][j] == 1) return noanswer;
							b[i][j] = 0;
							b[j][i] = 0;		
						}
						if (a[i][k]+a[j][k] == 3){
							if (b[i][j] == 0) return noanswer;
							b[i][j] = 1;
							b[j][i] = 1;
						}
					}
			if (!check()) return noanswer;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < m;j++){
					if (a[i][j] == 0){//每新填一个字母，都要跟之前判断有无关系。 
						for (int k = 0;k < n;k++)
							if (b[i][k] != -1){
								if (b[i][k] == 0 && a[k][j] != 0) 
									a[i][j] = a[k][j];
								else if (b[i][k] == 1 && a[k][j] != 0)
									a[i][j] = (a[k][j] == 1 ? 2 : 1);
							}
						if (a[i][j] == 0){
							a[i][j] = 1;
							for (int k = 0;k < n;k++)
								if (i != k){
									if (a[k][j] == 1){b[i][k] = 0;b[k][i] = 0;}
									if (a[k][j] == 2){b[i][k] = 1;b[k][i] = 1;} 
								}
							if (!check()) {
								a[i][j] = 2;
								for (int k = 0;k < n;k++)
									if (i != k){
										if (a[k][j] == 2){b[i][k] = 0;b[k][i] = 0;}
										if (a[k][j] == 1){b[i][k] = 1;b[k][i] = 1;} 
									}							
							}
						}
						else{
							for (int k = 0;k < n;k++)
								if (i != k){
									if (a[k][j] == a[i][j]){b[i][k] = 0;b[k][i] = 0;}
									if (a[k][j] != a[i][j] && a[k][j] != 0){b[i][k] = 1;b[k][i] = 1;} 
								}								
						}
					}
					else{
						for (int k = 0;k < n;k++)
							if (i != k){
								if (a[k][j] == a[i][j]){b[i][k] = 0;b[k][i] = 0;}
								if (a[k][j] != a[i][j] && a[k][j] != 0){b[i][k] = 1;b[k][i] = 1;} 
							}								
					}			
						
					if (a[i][j] == 1) ss[i] = ss[i]+'N';
					else ss[i] = ss[i]+'Z';
					
				}
			for (int i = 0;i < n;i++) ans.push_back(ss[i]);
			return ans;
    	}
    	bool check(){
    		memset(dis,0,sizeof(dis));
    		bool flag = 1;
    		for (int i = 0;i < n;i++)
    			if (dis[i] == 0){
					flag &= dfs(i,1);
				}
			return flag;
    	}
    	bool dfs(int x,int y){
    		dis[x] = y;
    		bool flag = 1;
    		for (int i = 0;i < n;i++)
    			if (b[x][i] != -1){
					if (dis[i] == 0)
						flag &= dfs(i,y+b[x][i]);
					else{
						if (abs(dis[x]-dis[i]+b[x][i])&1) return 0;
					}
				}
			return flag;
    	}
};
