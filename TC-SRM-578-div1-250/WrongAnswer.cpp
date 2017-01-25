// FST:队列长度应开50^2*101，两次FST都因队列长度开小，第一次只开了50^3，第二次只开了50^2*100
#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class GooseInZooDivOne{
public:
	struct item{int x,y,z;}Q[252510];
	bool vis[51][51][101];
	void push(int&t,item it){if(!vis[it.x][it.y][it.z])vis[it.x][it.y][it.z]=1,Q[t++]=it;}
	int count(vector <string> field, int dist){
		int R=field.size(),C=field[0].length(),tot,s=0,e=0;
		for(int x=0;x<R;x++)for(int y=0;y<C;y++)if(!vis[x][y][0]&&field[x][y]=='v'){
			Q[0]=(item){x,y,0};vis[x][y][0]=1;tot=0;
			for(int h=0,t=1;h<t;h++){
				item it=Q[h];
				if(it.z){
					push(t,(item){it.x,it.y,it.z-1});
					if(it.x)push(t,(item){it.x-1,it.y,it.z-1});
					if(it.y)push(t,(item){it.x,it.y-1,it.z-1});
					if(it.x+1<R)push(t,(item){it.x+1,it.y,it.z-1});
					if(it.y+1<C)push(t,(item){it.x,it.y+1,it.z-1});
				}
				else if(field[it.x][it.y]=='v')tot++,it.z+=dist,push(t,it);
			}
			s++;tot%2?e=1:1;
		}
		int S=0;
		for(e?--s:1;s--;)S=(S*2+1)%MOD;
		return S;
	}
};
