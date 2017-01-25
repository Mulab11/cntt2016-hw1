#include <vector>
#include <algorithm>
#define MOD 1000000009
using namespace std;
class UnknownTree{
public:
	struct item{
		int x,y,z;
		bool operator<(const item&v)const{
			if(x!=v.x)return x<v.x;
			if(y!=v.y)return y<v.y;
			return z<v.z;
		}
		bool operator==(const item&v)const{
			return x==v.x&&y==v.y&&z==v.z;
		}
	}items[1000],*iter,V[1000],D[1000];
	void ins(int x,int y,int z){
		if(x>=0&&y>=0&&z>=0&&x+y>0&&y+z>0&&z+x>0)*(iter++)=(item){x,y,z};
	}
	int getCount(vector<int> a, vector<int> b, vector<int> c){
		// 离散化A,B,C到LCA的距离的所有情况
		int n=a.size();
		iter=items;
		for(int i=0;i<n;i++){
			ins(a[i],b[i],c[i]); // LCA为0~n-1的点i
			ins(0,b[i]+a[i],c[i]-a[i]); // LCA为A，且i在AB上
			ins(0,b[i]-a[i],c[i]+a[i]); // LCA为A，且i在AC上
			ins(a[i]+b[i],0,c[i]-b[i]); // LCA为B，且i在BA上
			ins(a[i]-b[i],0,c[i]+b[i]); // LCA为B，且i在BC上
			ins(a[i]+c[i],b[i]-c[i],0); // LCA为C，且i在CA上
			ins(a[i]-c[i],b[i]+c[i],0); // LCA为C，且i在CB上 
		}
		// 0在A子树内
		ins(0,b[0]-a[0],c[0]-a[0]); // B-A-C
		ins(b[0]-a[0],0,c[0]-b[0]); // A-B-C
		ins(c[0]-a[0],b[0]-c[0],0); // A-C-B
		// 0在B子树内
		ins(a[0]-b[0],0,c[0]-b[0]);
		ins(a[0]-c[0],c[0]-b[0],0);
		ins(0,a[0]-b[0],c[0]-a[0]);
		// 0在C子树内
		ins(a[0]-c[0],b[0]-c[0],0);
		ins(0,b[0]-a[0],a[0]-c[0]);
		ins(a[0]-b[0],0,b[0]-c[0]);
		std::sort(items,iter);
		iter=std::unique(items,iter);
		// 对每种情况计算方案数
		int ans=0;n+=3;
		for(int i=0;i<3;i++)a.push_back(0),b.push_back(0),c.push_back(0);
		for(item*T=items;T<iter;T++){
			bool flag=1; // flag表示是否合法 
			a[n-2]=b[n-3]=T->x+T->y;
			b[n-1]=c[n-2]=T->y+T->z;
			c[n-3]=a[n-1]=T->z+T->x;
			for(int i=0;i<n;i++)D[i]=(item){b[i]-c[i],c[i]-a[i],a[i]-b[i]};
			for(int i=0;i<n;i++){
				int&tp=V[i].x,&dis=V[i].y,&dep=V[i].z; // tp,dis,dep为每个点的类型、在A-B-C链上的位置、深度
				tp=(D[i].x==T->y-T->z)|(D[i].y==T->z-T->x)<<1|(D[i].z==T->x-T->y)<<2;
				if(tp==1||tp==7)dis=T->x-T->y-D[i].z,dep=a[i]+b[i]-T->x-T->y;
				else if(tp==2)dis=T->y-T->z-D[i].x,dep=b[i]+c[i]-T->y-T->z;
				else if(tp==4)dis=T->z-T->x-D[i].y,dep=c[i]+a[i]-T->z-T->x;
				else dis=1; // 无解情况 
				if(dis%2||dep%2||dis<0||dep<0){flag=0;break;}
				dis/=2;dep/=2;
			}
			if(!flag)continue;
			sort(V,V+n);
			int P=1;
			for(int l=0,r=0;l<n&&P;l=r){ // 对同一位置的点构树 
				while(r<n&&V[l].x==V[r].x&&V[l].y==V[r].y)r++;
				if(V[l].z||l+1<r&&!V[l+1].z)P=0; // 必须恰好一个根 
				else for(int p=l,q=l+1;q<r;q++){
					while(V[p].z<V[q].z)p++;
					P=1ll*P*(p-l)%MOD;
				}
			}
			ans=(ans+P)%MOD;
		}
		return ans; 
	}
};
