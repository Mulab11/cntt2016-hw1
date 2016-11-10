#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>

const int MAXN(2333);
const int ten[4]={1000,100,10,1};
inline bool cmp(int a,int b){
	return a>b;
}
class EllysRoomAssignmentsDiv1{
private:
	int rt[MAXN],n,elly;
public:
	double getAverage(std::vector<std::string> ratings){
		std::string& s=ratings[0];
		for(unsigned int i=1;i<ratings.size();i++)
			s=s+ratings[i];//将string进行拼接
		for(unsigned int i=0;i<s.size();i+=5,n++)//将字符串转换为数字
			for(int j=0;j<4;j++)
				rt[n]+=(s[i+j]-'0')*ten[j];
		/*for(int i=0;i<n;i++)
			fprintf(stderr,"%d ",rt[i]);*/
		elly=rt[0];//记录Elly分数
		std::sort(rt,rt+n,cmp);//从大到小排序
		
		int rms=(n+19)/20,num=n/rms,rem=n-rms*num;//房间数，每个房间的人数，剩下的散人数
		double sum=0.0;//Elly房间期望分数和
			
		for(int i=0;i<num;i++){//每一次给每个房间分一个
			int st=i*rms,ed=st+rms-1;
			if(rt[st]>=elly&&elly>=rt[ed])//如果Elly在这组，
				sum+=elly;//则这组分进Elly房间的期望分数就是Elly自己的分数
			else{//否则是这组分数的平均数
				int temp=0;
				for(int j=st;j<=ed;j++)
					temp+=rt[j];
				sum+=double(temp)/rms;
			}
		}
		
		if(!rem)return sum/num;//如果没有散人直接返回期望分数和除以房间人数
		else if(rt[num*rms]>=elly)return (sum+elly)/(num+1);//如果Elly在散人中则直接计算
		else{
			double p=double(rem)/rms,temp=0;//Elly房间分到散人的概率以及散人平均分数
			for(int i=num*rms;i<n;i++)
				temp+=rt[i];
			temp/=rem;
			return p*(sum+temp)/(num+1)+(1-p)*sum/num;
		}
	}
};



EllysRoomAssignmentsDiv1 test;
#define FILE "250pts"
#define gc() getchar()
std::vector<std::string> map;
void init(){
	char c=gc();
	do{
		std::string s;
		while(c!='"')
			c=gc();
		c=gc();
		while(c!='"')
			s=s+c,c=gc();
		c=gc();
		map.push_back(s);
	}while(c!='}');
}
int main(){
	freopen(FILE".in","r",stdin);
	freopen(FILE".out","w",stdout);
	init();
	printf("%.8lf\n",test.getAverage(map));
	return 0;
}
