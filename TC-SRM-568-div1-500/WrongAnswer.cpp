#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class EqualSums{
public:
	int count(vector <string> board){
		int N=board.size();
		for(int c=0,r1,r2;c<N;c++){
			for(r1=0;r1<board.size()&&board[r1][c]=='-';r1++);
			for(r2=r1+1;r2<board.size()&&board[r2][c]=='-';r2++);
			if(r2<board.size()){
				int p=r1,q=r2;
				if(board[r1][c]>board[r2][c])p=r2,q=r1;
				char a=board[p][c],b=board[q][c];
				for(int i=0;i<N;i++){
					char&x=board[p][i],&y=board[q][i];
					if(x!='-'&&y!='-'&&x-y!=a-b)return 0;
					if(x=='-'&&y!='-'&&(x=y+a-b)<'0')return 0;
				}
				board[q]=board[board.size()-1];board.pop_back();c--;
			}
		}
		int a[51],pre=1,pos[51],n=0,ans;
		for(int i=0;i<board.size();i++){
			int m=20;
			for(int j=0;j<N;j++)if(board[i][j]!='-'&&board[i][j]-'0'<m)m=board[i][j]-'0';
			a[n++]=m;
		}
		pos[n-1]=1;for(int i=n-1;i;i--)pos[i-1]=1ll*pos[i]*(a[i]+1)%MOD;
		ans=pos[0];for(int i=1;i<n;i++)ans=(ans+1ll*pre*pos[i]%MOD*a[0])%MOD,pre=1ll*pre*a[i]%MOD;
		return ans;
	}
};
