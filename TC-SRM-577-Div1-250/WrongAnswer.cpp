#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class EllysRoomAssignmentsDiv1{
public:
	int a[510];
	double getAverage(vector <string> ratings){
		int N=*a=0,R,q,r,x;
		for(int i=0;i<ratings.size();i++)
			for(int j=0;j<ratings[i].length();j++)ratings[i][j]==' '?a[++N]=0:a[N]=a[N]*10+ratings[i][j]-'0';
		R=N++/20+1;q=N/R;r=N%R;x=a[0];
		sort(a,a+N);reverse(a,a+N);
		for(int i=0;i<N;i++)if(a[i]==x){x=i;break;}
		double sum=0,ans;
		for(int i=0;i<q;i++){
			if(x/R==i)sum+=a[x];
			else for(int j=0;j<R;j++)sum+=a[i*R+j]*1.0/R;
		}
		if(x>=q*R)return(sum+a[x])/(q+1);
		ans=sum/q*(R-r)/R;
		for(int i=0;i<r;i++)ans+=(sum+a[q*R+i])/(q+1)/R;
		return ans;
	}
};
