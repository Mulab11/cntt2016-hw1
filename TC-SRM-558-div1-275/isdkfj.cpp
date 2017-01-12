#include <bits/stdc++.h>

using namespace std;


class Stamp {
public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
		int n=desiredColor.size(),f[55],ret=2147483647;
		for(int L=1;L<=n;++L){//枚举长度 
			memset(f,0x3f,sizeof f);
			f[0]=0;
			for(int i=L;i<=n;++i){
				for(int j=0;j<i;++j){
					if(i-j>L)continue;
					if(f[j]>1000000)continue;
					bool flag=1;char ch=0;
					if(j>=L&&i-j!=L)for(int k=j-1;k>=j-L;--k)if(desiredColor[k]!='*')ch=desiredColor[k];
					//上一个颜色 
					for(int k=i-L;k<i;++k)if(desiredColor[k]!='*'){
						if(!ch)ch=desiredColor[k];
						else if(ch!=desiredColor[k])flag=0;//是否有两种颜色 
					}
					if(flag)f[i]=min(f[i],f[j]+1);//dp
				}
			}
			if(f[n]<1000000)ret=min(ret,stampCost*L+pushCost*f[n]);//更新答案 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
