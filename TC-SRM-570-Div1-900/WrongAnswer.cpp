#include <vector>
#include <string>
#include <cstring>
using namespace std;
class CurvyonRails{
public:
	int R,C;
	struct edge{int to,cap,cost;edge*rev,*next;}E[9464],*ne,*first[2028];
	int P(int x,int y,int z){
		if(z<0)return-z-1;
		if(x<0||x>=R||y<0||y>=C)return-1;
		return(x+R*z)*C+y+2;
	}
	void link(int x1,int y1,int z1,int x2,int y2,int z2,int cap,int cost){
		int a=P(x1,y1,z1),b=P(x2,y2,z2);
		if(a<0||b<0)return;
		*ne=(edge){b,cap,cost,ne+1,first[a]};first[a]=ne++;
		*ne=(edge){a,0,-cost,ne-1,first[b]};first[b]=ne++;
	}
	int Q[4112784],D[2028];
	edge*fr[2028];
	bool inq[2028];
	void mincost(int&f,int&c){
		for(f=c=0;;){
			memset(D,63,sizeof(D));
			memset(inq,0,sizeof(inq));
			int head=*Q=0,tail=1,INF=*D;*D=0;
			for(int i;head<tail;head++){
				inq[i=Q[head]]=0;
				for(edge*e=first[i];e;e=e->next)if(e->cap&&D[i]+e->cost<D[e->to]){
					D[e->to]=D[i]+e->cost;
					fr[e->to]=e;
					if(!inq[e->to])inq[Q[tail++]=e->to]=1;
				}
			}
			if(D[1]==INF)return;
			int cap=INF;
			for(int i=1;i;i=fr[i]->rev->to)if(fr[i]->cap<cap)cap=fr[i]->cap;
			for(int i=1;i;i=fr[i]->rev->to)fr[i]->cap-=cap,fr[i]->rev->cap+=cap,c+=fr[i]->cost*cap;
			f+=cap;
		}
	}
	int getmin(vector <string> field){
		R=field.size();C=field[0].length();
		ne=E;memset(first,0,sizeof(first));
		int vx[4]={-1,0,0,1},vy[4]={0,-1,1,0},vz[4]={1,2,2,1},cnt=0;
		for(int i=0;i<R;i++)for(int j=0;j<C;j++)if(field[i][j]!='w'){
			if((i+j)%2){
				link(0,0,-1,i,j,0,2,0);
				for(int z=1;z<3;z++)for(int c=0;c<2;c++)link(i,j,0,i,j,z,1,c*(field[i][j]=='C'));
				for(int d=0;d<4;d++)link(i,j,vz[d],i+vx[d],j+vy[d],vz[d],1,0);
			}
			else{
				link(i,j,0,0,0,-2,2,0);
				for(int z=1;z<3;z++)for(int c=0;c<2;c++)link(i,j,z,i,j,0,1,c*(field[i][j]=='C'));
			}
			cnt++;
		}
		int f,c;mincost(f,c);
		return f==cnt?c:-1;
	}
};
