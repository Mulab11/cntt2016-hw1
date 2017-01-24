#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class CheckerFreeness{
public:
	string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY);
};
int A,ax[222],ay[222],B,bx[222],by[222];
void read(vector<string>&str,int&n,int*a){
	n=*a=0;
	for(int i=0;i<str.size();i++)
		for(int j=0;j<str[i].length();j++)
			str[i][j]==' '?a[++n]=0:a[n]=a[n]*10+str[i][j]-'0';
	n++;
}
int ai,aj,L[444],len;
double PI,ang[222][444],X1[222],Y1[222],X2[222],Y2[222];
bool cmp(int i,int j){return ang[ai][i]<ang[ai][j];}
double Ang(int i,int j,int k){
	double t=ang[j][k]-ang[j][i];
	if(t<0)t+=2*PI;if(t>=2*PI)t-=2*PI;
	return t;
}
string CheckerFreeness::isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY){
	PI=acos(-1);
	read(whiteX,A,ax);read(whiteY,A,ay);
	read(blackX,B,bx);read(blackY,B,by);
	if(A<2||B<2)return"YES";
	for(int i=0;i<A;i++)
		for(int j=0;j<A+B;j++)ang[i][j]=j<A?atan2(ay[j]-ay[i],ax[j]-ax[i]):atan2(by[j-A]-ay[i],bx[j-A]-ax[i]);
	for(ai=0;ai<A;ai++){
		for(int i=len=0;i<A+B;i++)if(i<ai||i>=A)L[len++]=i;
		sort(L,L+len,cmp);
		for(int j=0;j<len;j++)if((aj=L[j])<ai){
			int cnt1=0,cnt2=0;
			bool type=1;
			for(int i=(j+1)%len;i!=j;i=(i+1)%len)if(L[i]>=A){
				if(type&&Ang(aj,ai,L[i])>PI)type=0;
				if(type)X1[cnt1]=Ang(aj,ai,L[i]),Y1[cnt1++]=Ang(L[i],aj,ai);
				else X2[cnt2]=Ang(L[i],ai,aj),Y2[cnt2++]=Ang(ai,aj,L[i]);
			}
			double miny=PI;
			for(int p=0,q=0;p<cnt2;p++){
				for(;q<cnt1&&X1[q]+X2[p]<PI;q++)if(Y1[q]<miny)miny=Y1[q];
				if(miny+Y2[p]<PI)return"NO";
			}
		}
	}
	return"YES";
}
p]<PI)return"NO";
			}
		}
	}
	return"YES";
}
�选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(Q(i,j),P(x,y),INF);
					ans+=dec(benefit[i][j]),link(P(i,j),Q(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
			}
		}
		return ans-maxflow();
	}
};
g ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C){
			v[s]=rot[s];
			for(int i=0;i<=spl[s][3];i++)(v[s]*=C-i)%=MOD;
			w[P(s,dig[s])]=1;
		}
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)
			for(int k=0;k<=K;k++)
				for(int i=0;i<A.N;i++)(ans+=S.a[P(s,k)][i]*w[i]%MOD*v[s])%=MOD;
		return ans; 
	}
};
ight;
	}
};
�的一层
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// i放同一层
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			else G[i]=0,cnt+=count_graph(i,rest-(1<<i));
			L[top]-=1<<i;
		}
		return cnt;
	}
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		N=blockTypes.size();Min=minWays;Max=maxWays;
		for(int i=0;i<N;i++)cnt[i]=blockTypes[i],G[i]=0;
		*L=top=0;
		return count_graph(-1,(1<<N)-1);
	}
};
