// WAonSystemTest
#include <vector>
#include <string>
using namespace std;
class TPS{
public:
	int N,up[55],down[55],f[55]; // up[i]:i上方是否为链 down[i]:i下方是否为链 f[i]:i的父边被取的情况下i子树至少取多少个点
	vector<int> to[55],ch[55]; // to[i]:i的出边 ch[i]:i的子节点
	void cmin(int&a,int b){b<a?a=b:1;}
	void init(int i,int fa){ // 预处理up和ch
		for(int e=0,j;e<to[i].size();e++)
			if((j=to[i][e])!=fa)ch[i].push_back(j),init(j,i);
		down[i]=!ch[i].size()||ch[i].size()==1&&down[ch[i][0]];
	}
	void dfs(int i){ // 计算down和f
		for(int c=0,j;c<ch[i].size();c++){
			j=ch[i][c];
			if(i)up[j]=up[i]&&ch[i].size()==1;
			else up[j]=ch[i].size()==1||ch[i].size()==2&&down[ch[i][!c]];
			dfs(j);
		}
		if(down[i]){f[i]=1;return;}
		f[i]=1<<30;
		// 标记i，则i最多1个子树不选，且必须是链
		int fmax=0,fsum=0;
		for(int c=0;c<ch[i].size();fsum+=f[ch[i][c++]])if(down[ch[i][c]])cmin(fmax,-f[ch[i][c]]);
		cmin(f[i],fsum+(ch[i].size()<1)); // 所有子树都选
		cmin(f[i],fsum+fmax+(ch[i].size()<2)); // 1个子树不选
	}
	int minimalBeacons(vector <string> linked){
		if((N=linked.size())==1)return 0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(linked[i][j]=='Y')to[i].push_back(j);
		init(0,-1);dfs(0);
		int ans=1<<30;
		for(int i=1;i<N;i++)if(up[i]){ // 枚举树的根i，i的每个子树都必须取
			// 如果i不选，要求至少2个子树
			int sum=ch[i].size()<2;
			for(int c=0;c<ch[i].size();c++)sum+=f[ch[i][c]];
			cmin(ans,sum);
		}
		// 根为0，最多一个子树不选，且必须是链 
		int sum=0,fmax=0;
		for(int c=0;c<ch[0].size();sum+=f[ch[0][c++]])if(down[ch[0][c]])cmin(fmax,-f[ch[0][c]]);
		cmin(ans,sum+(ch[0].size()<2));
		cmin(ans,sum+fmax+(ch[0].size()<3));
		return ans;
	}
};
