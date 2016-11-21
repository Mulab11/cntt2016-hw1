#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class ColorfulChocolates{
	public:
		int maximumSpread(string cho, int m){
			int ans=1;
			int n=cho.length();
			for (int i=0;i<n;++i){
				int su=0,ps=i;
				for(int j=i;j>=0&&su<=m;--j){
					if (cho[j]==cho[i]){
						su+=ps-j;
						--ps;
					}
					int sum=su,pos=i;
					for (int k=i;k<n;++k){
						if (cho[k]==cho[i]){
							sum+=k-pos;
							++pos;
						}
						if (sum>m) break;
						ans=max(ans,pos-ps-1);
					}
				}
			}
			return ans;
		}
};

