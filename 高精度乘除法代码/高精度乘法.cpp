#include<iostream>
#include<string>
using namespace std;
int a[301],b[301],c[601];
int init(int a[])
{
	string s;
	cin>>s;
	int len=s.size();
	for(int i=0;i<len;i++)
		a[i]=s[len-1-i]-'0';
	return len;
}
int main()
{
	int lena=init(a);
	int lenb=init(b);
	int lenc=lena+lenb;
	for(int i=0;i<lena;i++)
		for(int j=0;j<lenb;j++)
			c[i+j]+=a[i]*b[j];
	for(int i=0;i<lenc;i++)
		if(c[i]>=10)
		{
			c[i+1]+=c[i]/10;
			c[i]%=10;
		}
	while(c[lenc]==0 && lenc>0)
		lenc--;
	for(int i=lenc;i>=0;i--)
		cout<<c[i];
	return 0;
}
