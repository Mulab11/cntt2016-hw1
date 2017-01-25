#include <vector>
#include <string>
using namespace std;
class EllysChessboard{
public:
	int minCost(vector <string> board);
};
int n,a[64],b[64],S[16][16],f[15][15][15][15];
int min(int x,int y){return x<y?x:y;}
int max(int x,int y){return x>y?x:y;}
struct rect{
	int u,d,l,r;
	int sum(){return S[d+1][r+1]-S[d+1][l]-S[u][r+1]+S[u][l];}
	int cost(int i){return max(max(a[i]-u,d-a[i]),max(b[i]-l,r-b[i]));}
	bool inside(int i){return u<=a[i]&&a[i]<=d&&l<=b[i]&&b[i]<=r;}
	rect append(int i,int&c){
		rect p=(rect){min(u,a[i]),max(d,a[i]),min(l,b[i]),max(r,b[i])};
		for(c=i=0;i<n;i++)if(!inside(i)&&p.inside(i))c+=p.cost(i);
		return p;
	}
};
int dfs(rect b){
	if(b.sum()==n)return 0;
	int&s=f[b.u][b.d][b.l][b.r],c;
	if(s)return s-1;
	s=1<<30;
	for(int i=0,t;i<n;i++)if(!b.inside(i))t=dfs(b.append(i,c)),s=min(s,t+c);
	return s++;
}
int EllysChessboard::minCost(vector <string> board){
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(board[i][j]=='#')a[n]=i-j+7,b[n++]=i+j;
	if(n<2)return 0;
	for(int i=0;i<n;i++)S[a[i]+1][b[i]+1]=1;
	for(int i=1;i<=15;i++)
		for(int j=1;j<=15;j++)S[i][j]+=S[i][j-1]+S[i-1][j]-S[i-1][j-1];
	int ans=1<<30;
	for(int i=0;i<n;i++)ans=min(ans,dfs((rect){a[i],a[i],b[i],b[i]}));
	return ans;
}
