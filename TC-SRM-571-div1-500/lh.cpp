#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class MagicMolecule{
	private:
		static const int maxn=55;
		int id[maxn],w[maxn],n;
		bool map[maxn][maxn],chos[maxn];
		int check(){
			int num=0,ret=0;
			for (int i=0;i<n;++i){
				chos[i]=true;
				for (int j=0;j<i;++j) if (chos[j]) if (!map[id[i]][id[j]]){
					chos[i]=false;
					break;
				}
				if (chos[i]){
					++num;
					ret+=w[id[i]];
				}
			}
			if (3*num<2*n) return -1;
			else return ret;
		}
	public:
		int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
			n=magicPower.size();
			for (int i=0;i<n;++i) w[i]=magicPower[i];
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (magicBond[i][j]=='Y') map[i][j]=true;
			for (int i=0;i<n;++i) id[i]=i;
			int ans=-1;
			if (n<=10){
				do{
					ans=max(ans,check());
				}while(next_permutation(id,id+n));
			}
			else{
				srand(2147482621);
				int cas=100000;
				while(cas--){
					random_shuffle(id,id+n);
					ans=max(ans,check());
				}
			}
			return ans;
		}
};
