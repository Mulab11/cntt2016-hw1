#include <vector>
#include <string>
using namespace std;
class YetAnotherBoardGame{
public:
	int N,M,popc[1<<13],a[13],x[13];
	int calc(int S){
		int s=popc[*x];
		for(int i=1;i<N;s+=popc[x[i++]])
			if(((x[i]=(a[i-1]^x[i-1]<<1^x[i-1]>>1^(i>1?x[i-2]:0)^(x[i-1]&S))&((1<<M)-1))&S)&&(x[i]&S)!=x[i])return 233;
		return a[N-1]==((x[N-1]<<1^x[N-1]>>1^(N>1?x[N-2]:0)^(x[N-1]&S))&((1<<M)-1))?s:233;
	}
	int minimumMoves(vector <string> board){
		N=board.size();M=board[0].length();
		for(int i=0;i<(1<<M);i++)popc[i]=i?popc[i&(i-1)]+1:0;
		for(int i=0;i<N;i++)
			for(int j=a[i]=0;j<M;j++)if(board[i][j]=='W')a[i]|=1<<j;
		int ans=233,tmp;
		for(int S=0,T=(1<<M)-1;S<(1<<M);S++,T--){
			for(*x=S;;(--*x)&=S){
				if((tmp=calc(S))<ans)ans=tmp;
				if(!*x)break;
			}
			for(*x=T;;(--*x)&=T){
				if((tmp=calc(S))<ans)ans=tmp;
				if(!*x)break;
			}
		}
		return ans==233?-1:ans;
	}
};
