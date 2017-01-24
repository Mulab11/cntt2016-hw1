#include <vector>
using namespace std;
class KeyDungeonDiv1{
public:
	int n,dR[12],dG[12],rR[12],rG[12],rW[12],f[1<<12][132];
	bool vis[1<<12][132];
	struct item{int S,R,G,W,cnt;}Q[132<<12],*H,*T;
	int bfs(int R,int G,int W){
		int ans=0;H=Q;T=Q+1;*H=(item){0,R,G,f[0][R]=W,0};vis[0][R]=1;
		for(;H<T;H++){
			H->G-=f[H->S][H->R]-H->W;
			H->W=f[H->S][H->R];
			if(H->R+H->G+H->W>ans)ans=H->R+H->G+H->W;
			for(int i=n;i--;)if(!(H->S>>i&1)){
				*T=(item){H->S|1<<i,H->R-dR[i],H->G-dG[i],H->W,H->cnt+1};
				if(T->R<0)T->W+=T->R,T->R=0;
				if(T->G<0)T->W+=T->G,T->G=0;
				if(T->W>=0){
					T->R+=rR[i];T->G+=rG[i];T->W+=rW[i];
					if(!vis[T->S][T->R])vis[T->S][T->R]=1,f[T->S][T->R]=T->W,T++;
					else if(T->W>f[T->S][T->R])f[T->S][T->R]=T->W;
				}
			}
		}
		return ans;
	}
	int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys){
		for(int i=n=doorR.size();i--;)dR[i]=doorR[i],dG[i]=doorG[i],rR[i]=roomR[i],rG[i]=roomG[i],rW[i]=roomW[i];
		return bfs(keys[0],keys[1],keys[2]);
	}
};
