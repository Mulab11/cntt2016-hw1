class HyperKnight{
public:
	long long countCells(int a, int b, int numRows, int numColumns, int k){
		if(a<b){int t=a;a=b;b=t;}
		if(k==2)return 4ll*b*b;
		if(k==3)return 8ll*b*(a-b);
		if(k==4)return 2ll*b*(numRows+numColumns-4ll*a)+4ll*(a-b)*(a-b);
		if(k==6)return 2ll*(a-b)*(numRows+numColumns-4ll*a);
		if(k==8)return (numRows-2ll*a)*(numColumns-2ll*a);
		return 0;
	}
};
