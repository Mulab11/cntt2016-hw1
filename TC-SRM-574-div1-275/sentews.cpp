#include<iostream>
using namespace std;
class TheNumberGame
{
	public:
	string determineOutcome(int A, int B)
	{
		int size1=0,size2=0;
		int a[11]={},b[11]={},c[11]={};
		while(A)
			a[++size1]=A%10,A/=10;
		while(B)
			b[++size2]=B%10,B/=10;
		for(int i=1;i<=size2;i++)
			c[i]=b[size2-i+1];
		bool flag=0;
		if(size1<size2)
			return "Manao loses";
		for(int i=1;i<=size1-size2+1;i++)
		{
			flag=1;
			for(int j=i,k=1;k<=size2;j++,k++)
				if(a[j]!=b[k])
					{flag=0;break;}
			if(flag)
				return "Manao wins";
		}
		for(int i=1;i<=size1-size2+1;i++)
		{
			flag=1;
			for(int j=i,k=1;k<=size2;j++,k++)
				if(a[j]!=c[k])
					{flag=0;break;}
			if(flag)
				return "Manao wins";
		}
		return "Manao loses";
	}
};
