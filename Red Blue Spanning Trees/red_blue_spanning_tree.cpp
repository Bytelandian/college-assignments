#include<iostream>
#include<stdio.h>

using namespace std;
int ans[1000][1000];
class unions
{
	public:
	unions* parent;
	int height;
	int id;
	unions(int i)
	{
		id=i;
		height=0;
		parent=NULL;
	}
};

unions* find(unions *a)
{
	if (a->parent==NULL) return a;
	return find(a->parent);
}

int add(unions *a,unions *b)
{
	a=find(a);
	b=find(b);
	if (a==b)
	return 0;
	else
	{
		if (a->height>b->height)
		{
			b->parent=a;
		}
		else if (a->height<b->height)
		{
			a->parent=b;
		}
		else
		{
			a->parent=b;
			b->height++;
		}
		return 1;
	}
}


int maxred(int a[1000][1000],unions *un[1000],int n,int an[1000][1000])
{
	int red=0,edge=0,i,j;
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j]==0)
			{
				if (add(un[i],un[j]))
				{
					red++;
					edge++;
					an[i][j]=1;
					if (edge==n-1)
					{
						return red;
					}
				}
			}
		}
	}
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j]==1)
			{
				if (add(un[i],un[j]))
				{
					an[i][j]=1;
					edge++;
					if (edge==n-1)
					{
						return red;
					}
				}
			}
		}
	}
}

int minred(int a[1000][1000],unions *un[1000],int n)
{
	int red=0,edge=0,i,j;
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j]==1)
			{
				if (add(un[i],un[j])==1)
				{
					ans[i][j]=1;
					edge++;
					if (edge==n-1)
					{
						return red;
					}
				}
			}
		}
	}
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j]==0)
			{
				if (add(un[i],un[j])==1)
				{
					ans[i][j]=1;
					red++;
					edge++;
					if (edge==n-1)
					{
						return red;
					}
				}
			}
		}
	}
}


void f(int a[1000][1000],unions *un[1000],int n,int red,int red_req)
{
	if (red==red_req) return ;
	static int arr[1000][1000],i,j,k,l,tt[1000][1000];
	unions *tmp[1000];
	for (i=0;i<n;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (a[i][j]==0&&ans[i][j]==-1)
			{
				for (k=0;k<1000;k++)
				{
					for (l=0;l<1000;l++)
					{
						tt[k][l]=-1;
						if (ans[k][l]==1)
						arr[k][l]=a[k][l];
						else
						arr[k][l]=-1;
					}
				}
				arr[i][j]=0;
				for (k=0;k<1000;k++) tmp[k]=new unions(k);
				if (maxred(arr,tmp,n,tt)==red+1)
				{
					ans[i][j]=1;
					for (k=0;k<1000;k++) un[k]=tmp[k];
					for (k=0;k<1000;k++)
					for (l=0;l<1000;l++)
					ans[k][l]=tt[k][l];
					red++;
					if (red==red_req)
					return;
				}
			}
		}
	}
}
int main()
{
	int red,n,i,j,color,a[1000][1000],edge,min_red,max_red,temp[1000][1000];
	unions *un[1000];
	
	for (i=0;i<1000;i++)
	{
		for (j=0;j<1000;j++)
		a[i][j]=ans[i][j]=temp[i][j]=-1;
	}
	
	for (i=0;i<1000;i++) un[i]=new unions(i);

	cin>>red;
	cin>>n;
	for (i=0;i<n;i++)
	{
		while (1)
		{
			cin>>edge;
			if (edge==-1)
			break;
			else
			{
				cin>>color;
				a[i][edge-1]=color;  //0 red
			}
		}
	}
	max_red=maxred(a,un,n,temp);
	for (i=0;i<n;i++)
	{
		un[i]->parent=NULL;
	}
	min_red=minred(a,un,n);
	if (red<min_red||red>max_red)
	cout<<"NO"<<endl;
	else
	{
		cout<<"YES"<<endl;
		f(a,un,n,min_red,red);
		for (i=0;i<n;i++)
		{
			for (j=i+1;j<n;j++)
			{
				if (ans[i][j]==1)
				{
					cout<<i+1<<" "<<j+1<<endl;
				}
			}
		}
	}
	return 0;
}
