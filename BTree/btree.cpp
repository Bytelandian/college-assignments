#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int order;
class treenode
{
	public:
	int key[10000],height,n;
	treenode* child[10000],*parent;
	int childcount[10000];
	treenode()
	{
		parent=NULL;
		height=0;
		n=0;
		int i;
		for (i=0;i<10000;i++)
		{
			child[i]=NULL;
			childcount[i]=0;
		}
	}
};

class tree
{
	public:
	treenode* root;
	int tno;
	tree()
	{
		root=NULL;
	}
}t[10000];

int* searchs(treenode* p,int k)      
{
	int i=0,n=p->n;
	while (i<n&&k>p->key[i])
	++i;
	if (i==n&&p->child[n]==NULL) return NULL;    
	
	else if (i==n&&p->child[n]!=NULL) return searchs(p->child[n],k);
	
	if (i!=n&&k==p->key[i])
	{
		return &(p->key[i]);
	}
	
	else if (p->child[i]==NULL)
	{
		return NULL;
	}
	
	else
	{
		return searchs(p->child[i],k);
	}
}

int* search(int treen,int k)
{
	if (t[treen].root==NULL) return NULL;
	else return searchs(t[treen].root,k);
}

treenode* searchin(treenode* p,int k)      
{
	int i=0,n=p->n;
	while (i<n&&k>p->key[i])
	++i;
	if (i==n&&p->child[n]==NULL) return p;    
	
	else if (i==n&&p->child[n]!=NULL)
	{
		p->childcount[n]++;
		return searchin(p->child[n],k);
	}
	
	if (i!=n&&k==p->key[i])
	{
		return NULL;
	}
	
	else if (p->child[i]==NULL)
	{
		return p;
	}
	
	else
	{
		p->childcount[i]++;
		return searchin(p->child[i],k);
	}
}

void insert(int treen,int k)
{
	treenode* p;
	int i,x,n,cno,pos,y;   // cno=child no of parent
	if (t[treen].root==NULL)
	{
		t[treen].root=new treenode;
		t[treen].root->key[0]=k;
		t[treen].root->n=1;
	}
	else
	{
		if (search(treen,k)) printf("Key already present\n");
		else 
		{
			p=searchin(t[treen].root,k);
			
			n=p->n;
			i=0;
			while (i<n&&k>p->key[i])
			++i;
			x=n;
			while (x>i)
			{
				p->child[x+1]=p->child[x];
				p->childcount[x+1]=p->childcount[x];
				p->key[x]=p->key[x-1];
				x--;
			}
			p->child[i+1]=NULL;
			p->childcount[i+1]=0;
			pos=i;
			p->key[i]=k;
			p->n=p->n+1;
			n=n+1;
			if (n<(2*order))
			{
				return;
			}
			else 
			{	
				treenode* right,*par;
				while(1)
				{
					right=new treenode;
					if (p->parent!=NULL)
					{
						par=p->parent;
						cno=0;
						while (cno<=(par->n)&&par->child[cno]!=p) ++cno;
						if (cno==(par->n+1)) 
						{
							printf("error\n");
							exit(0);
						}
						for (i=0;i<order-1;i++)
						{
							right->child[i]=p->child[order+1+i];
							if (right->child[i]!=NULL)
							right->child[i]->parent=right;
							right->childcount[i]=p->childcount[order+1+i];
							right->key[i]=p->key[order+1+i];
						}
						right->height=p->height;
						right->child[i]=p->child[order+1+i];
						if (right->child[i]!=NULL)
						right->child[i]->parent=right;
						right->childcount[i]=p->childcount[order+1+i];
						x=par->n;
						while (x>cno)
						{
							par->child[x+1]=par->child[x];
							par->childcount[x+1]=par->childcount[x];
							par->key[x]=par->key[x-1];
							x--;
						}
						par->child[cno+1]=right;
						par->childcount[cno+1]=order-1;
						for (y=0;y<order;y++)
						par->childcount[cno+1]=par->childcount[cno+1]+right->childcount[y];
						par->childcount[cno]=order;
						for (y=0;y<order+1;y++)
						par->childcount[cno]=par->childcount[cno]+p->childcount[y];
						par->key[cno]=p->key[order];
						right->parent=par;
						p->n=order;
						right->n=order-1;
						par->n=par->n+1;
					}
					else
					{
						for (i=0;i<order-1;i++)
						{
							right->child[i]=p->child[order+1+i];
							if (right->child[i]!=NULL)
							right->child[i]->parent=right;
							right->childcount[i]=p->childcount[order+1+i];
							right->key[i]=p->key[order+1+i];
						}
						right->child[i]=p->child[order+1+i];
						right->height=p->height;
						if (right->child[i]!=NULL)
						right->child[i]->parent=right;
						right->childcount[i]=p->childcount[order+1+i];
						t[treen].root=new treenode;
						t[treen].root->height=p->height+1;
						t[treen].root->key[0]=p->key[order];
						t[treen].root->n=1;
						t[treen].root->child[0]=p;
						t[treen].root->childcount[1]=order-1;
						for (y=0;y<order;y++)
						t[treen].root->childcount[1]=t[treen].root->childcount[1]+right->childcount[y];
    						t[treen].root->childcount[0]=order;
						for (y=0;y<order+1;y++)
						t[treen].root->childcount[0]=t[treen].root->childcount[0]+p->childcount[y];
						t[treen].root->child[1]=right;
						p->n=order;
						p->parent=t[treen].root;
						right->parent=t[treen].root;
						right->n=order-1;
						break;
					}
					p=par;
					if (p->n<2*order) break;
				}
			}
		}
	}
}

treenode* searchdel(treenode* p,int k)      
{
	int i=0,n=p->n;
	while (i<n&&k>p->key[i])
	++i;
	if (i==n&&p->child[n]==NULL) return NULL;    
	
	else if (i==n&&p->child[n]!=NULL)
	{
		p->childcount[n]--;
		return searchdel(p->child[n],k);
	}
	
	if (i!=n&&k==p->key[i])
	{
		return p;
	}
	
	else if (p->child[i]==NULL)
	{
		return NULL;
	}
	
	else
	{
		p->childcount[i]--;
		return searchdel(p->child[i],k);
	}
}
void merge(treenode* p,int treen)
{
	treenode* par,*right,*left;
	int cno,x,n;
	if (p->parent==NULL)
	{
		if (p->n>0)   return;
		else
		{
			t[treen].root=p->child[0];          //CHECK HERE 
			delete p; 
		}
	}
	par=p->parent;
	cno=0;
	while (cno<=par->n&&par->child[cno]!=p) cno++;
	if (cno==par->n+1) printf("error");
	if (cno!=par->n)   //not last child
	{
		right=par->child[cno+1];
		if (right->n==order-1)
		{
			n=p->n;
			p->key[n]=par->key[cno];
			x=0;
			n++;
			while (n<2*order-2)
			{
				p->child[n]=right->child[x];
				p->key[n]=right->key[x];
				p->childcount[n]=right->childcount[x];
				if (p->child[n]) p->child[n]->parent=p;
				x++;
				n++;
			}
			p->child[n]=right->child[x];
			p->childcount[n]=right->childcount[x];
			if (p->child[n]) p->child[n]->parent=p;
			p->n=2*order-2;
			par->childcount[cno]=par->childcount[cno]+par->childcount[cno+1]+1;
			x=cno;
			par->key[cno]=par->key[cno+1];
			x++;
			while (x<par->n-1)
			{
				par->child[x]=par->child[x+1];
				par->childcount[x]=par->childcount[x+1];
				par->key[x]=par->key[x+1];
				x++;
			}
			par->child[x]=par->child[x+1];
			par->childcount[x]=par->childcount[x+1];
			par->n=par->n-1;
			if (par->n==order-2)
			merge(par,treen);
		}
		else     //rotation
		{
			p->key[p->n]=par->key[cno];
			p->child[p->n+1]=right->child[0];
			if (p->child[p->n+1]) p->child[p->n+1]->parent=p;
			p->childcount[p->n+1]=right->childcount[0];
			par->key[cno]=right->key[0];
			par->childcount[cno]=par->childcount[cno]+1+right->childcount[0];
			par->childcount[cno+1]=par->childcount[cno+1]-1-right->childcount[0];
			p->n=p->n+1;
			x=0;
			right->n=right->n-1;
			while (x<right->n)
			{
				right->key[x]=right->key[x+1];
				right->child[x]=right->child[x+1];
				right->childcount[x]=right->childcount[x+1];
				x++;
			}
			right->child[x]=right->child[x+1];
			right->childcount[x]=right->childcount[x+1];
		}
	}
	else   //last child
	{
		left=par->child[cno-1];
		if (left->n==order-1)
		{
			right=p;
			p=left;
			n=p->n;
			p->key[n]=par->key[cno-1];
			x=0;
			n++;
			while (n<2*order-2)
			{
				p->child[n]=right->child[x];
				p->key[n]=right->key[x];
				p->childcount[n]=right->childcount[x];
				if (p->child[n]) p->child[n]->parent=p;
				x++;
				n++;
			}
			p->child[n]=right->child[x];
			p->childcount[n]=right->childcount[x];
			if (p->child[n]) p->child[n]->parent=p;
			p->n=2*order-2;
			par->childcount[cno-1]=par->childcount[cno-1]+par->childcount[cno]+1;
			x=cno-1;
			par->key[cno-1]=par->key[cno];
			x++;
			while (x<par->n-1)
			{
				par->child[x]=par->child[x+1];
				par->childcount[x]=par->childcount[x+1];
				par->key[x]=par->key[x+1];
				x++;
			}
			par->child[x]=par->child[x+1];
			par->childcount[x]=par->childcount[x+1];
			par->n=par->n-1;
			if (par->n==order-2)
			merge(par,treen);
		}
		else
		{
			x=p->n;
			p->child[x+1]=p->child[x];
			p->childcount[x+1]=p->childcount[x];
			while (x>0)
			{
				p->child[x]=p->child[x-1];
				p->childcount[x-1]=p->childcount[x-1];
				p->key[x]=p->key[x-1];
				x--;
			}
			p->key[x]=par->key[cno-1];
			p->child[x]=left->child[left->n];
			if (p->child[x]) p->child[x]->parent=p;
			p->childcount[x]=left->childcount[left->n];
			par->key[cno-1]=left->key[left->n-1];
			par->childcount[cno-1]=par->childcount[cno-1]-1-left->childcount[left->n];
			par->childcount[cno]=par->childcount[cno]+1+left->childcount[left->n];
			left->n=left->n-1;
			p->n=p->n+1;
		}
	}
}
void del(int treen,int k)
{
	treenode *p,*par;
	int x,n,cno;
	if (search(treen,k)==NULL) printf("Key not present\n");
	else
	{
		p=searchdel(t[treen].root,k);
		if (p->child[0]==NULL)				//leaf
		{
			x=0;
			n=p->n;
			while (x<n&&p->key[x]!=k) x++;
			while (x<n-1)
			{
				p->key[x]=p->key[x+1];
				p->child[x]=p->child[x+1];
				p->childcount[x]=p->childcount[x+1];
				x++;
			}
			n--;
			p->n=p->n-1;
			if (n<(order-1))
			{
				merge(p,treen);
			}
			else return;
		}
		else
		{				//non leaf
			treenode *ch;
			x=0;
			n=p->n;
			while (x<n&&p->key[x]!=k) x++;
			ch=p->child[x+1];
			p->childcount[x+1]=p->childcount[x+1]-1;
			while (ch->child[0]!=NULL)
			{
				ch->childcount[0]=ch->childcount[0]-1;
				ch=ch->child[0];
			}
			int temp=ch->key[0];
			p->key[x]=temp;
			ch->key[0]=k;
			p=ch;
			x=0;
			n=p->n;
			while (x<n-1)
			{
				p->key[x]=p->key[x+1];
				p->child[x]=p->child[x+1];
				p->childcount[x]=p->childcount[x+1];
				x++;
			}
			n--;
			p->n=p->n-1;
			if (n<(order-1))
			{
				merge(p,treen);
			}
			else return;
		}
	}
}


int select(treenode* p,int k)
{
	int i=0;
	while (1)
	{
		if (k<=p->childcount[i])
		{
			return select(p->child[i],k);
		}
		else if (k==p->childcount[i]+1)
		return p->key[i];
		else
		{
			k=k-p->childcount[i]-1;
			i++;
		}
	}
}

void split(treenode* p,int treen)
{
	int n,m,x,tp,tr,y,cno,i;
	treenode *par,*right;
	right=new treenode;
	m=p->n;
	tp=m/2;
	tr=m-m/2-1;
	if (p->parent!=NULL)
	{
		par=p->parent;
		cno=0;
		while (cno<=(par->n)&&par->child[cno]!=p) ++cno;
		if (cno==(par->n+1)) 
		{
			printf("error\n");
			exit(0);
		}
		for (i=0;i<tr;i++)
		{
			right->child[i]=p->child[tp+1+i];
			if (right->child[i]!=NULL)
			right->child[i]->parent=right;
			right->childcount[i]=p->childcount[tp+1+i];
			right->key[i]=p->key[tp+1+i];
		}
		right->height=p->height;
		right->child[i]=p->child[tp+1+i];
		if (right->child[i]!=NULL)
		right->child[i]->parent=right;
		right->childcount[i]=p->childcount[tp+1+i];
		x=par->n;
		while (x>cno)
		{
			par->child[x+1]=par->child[x];
			par->childcount[x+1]=par->childcount[x];
			par->key[x]=par->key[x-1];
			x--;
		}
		par->child[cno+1]=right;
		par->childcount[cno+1]=tr;
		for (y=0;y<=tr;y++)
		par->childcount[cno+1]=par->childcount[cno+1]+right->childcount[y];
		par->childcount[cno]=tp;
		for (y=0;y<=tp;y++)
		par->childcount[cno]=par->childcount[cno]+p->childcount[y];
		par->key[cno]=p->key[tp];
		right->parent=par;
		p->n=tp;
		right->n=tr;
		par->n=par->n+1;
	}
	else
	{
		for (i=0;i<tr;i++)
		{
			right->child[i]=p->child[tp+1+i];
			if (right->child[i]!=NULL)
			right->child[i]->parent=right;
			right->childcount[i]=p->childcount[tp+1+i];
			right->key[i]=p->key[tp+1+i];
		}
		right->child[i]=p->child[tp+1+i];
		right->height=p->height;
		if (right->child[i]!=NULL)
		right->child[i]->parent=right;
		right->childcount[i]=p->childcount[tp+1+i];
		t[treen].root=new treenode;
		t[treen].root->height=p->height+1;
		t[treen].root->key[0]=p->key[tp];
		t[treen].root->n=1;
		t[treen].root->child[0]=p;
		t[treen].root->childcount[1]=tr;
		for (y=0;y<=tr;y++)
		t[treen].root->childcount[1]=t[treen].root->childcount[1]+right->childcount[y];
		t[treen].root->childcount[0]=tp;
		for (y=0;y<=tp;y++)
		t[treen].root->childcount[0]=t[treen].root->childcount[0]+p->childcount[y];
		t[treen].root->child[1]=right;
		p->n=tp;
		p->parent=t[treen].root;
		right->parent=t[treen].root;
		right->n=tr;
	}
	p=p->parent;
	if (p->n>2*order-1)
	split(p,treen);
}

void join(treenode *p,int k,treenode *r,int treen)
{
	int n,x;
	if (p->height>=r->height)
	{
		t[treen].root=p;
		while (p->height>r->height)
		{
			p->childcount[p->n]=p->childcount[p->n]+1+r->n;
			p=p->child[p->n];
		}
		n=p->n;
		x=0;
		p->key[n]=k;
		n++;
		while (x<r->n)
		{
			p->child[n]=r->child[x];
			p->childcount[n]=r->childcount[x];
			if (p->child[n]) p->child[n]->parent=p;
			p->key[n]=r->key[x];
			x++;
			n++;
		}
		p->child[n]=r->child[x];
		p->childcount[n]=r->childcount[x];
		if (p->child[n]) p->child[n]->parent=p;
		p->n=n;
		if (p->n>2*order-1) split(p,treen);
	}
	else
	{
		t[treen].root=r;
		while (p->height<r->height)
		{
			r->childcount[0]=r->childcount[0]+1+p->n;
			r=r->child[0];
		}
		n=p->n+1;
		x=r->n;
		while (x>0)
		{
			r->child[n+x]=r->child[x];
			r->childcount[n+x]=r->childcount[x];
			r->key[n+x-1]=r->key[x-1];
			x--;
		}
		r->child[n]=r->child[x];
		r->childcount[n]=r->childcount[x];
		x=0;
		n=0;
		while (x<p->n)
		{
			r->child[x]=p->child[n];
			r->childcount[x]=p->childcount[n];
			if (r->child[x]) r->child[x]->parent=r;
			r->key[x]=p->key[n];
			n++;
			x++;
		}
		r->child[x]=p->child[n];
		r->childcount[x]=p->childcount[n];
		if (r->child[x]) r->child[x]->parent=r;
		r->key[x]=k;
		r->n=r->n+p->n+1;
		if (r->n>2*order-1) split(r,treen);
	}
}

treenode* searchsplit(treenode* p,int k)      
{
	int i=0,n=p->n;
	while (i<n&&k>p->key[i])
	++i;
	if (i==n&&p->child[n]==NULL) return p;    
	
	else if (i==n&&p->child[n]!=NULL)
	{
	
		return searchsplit(p->child[n],k);
	}
	
	if (i!=n&&k==p->key[i])
	{
		
		return p;
	}
	
	else if (p->child[i]==NULL)
	{
		return p;
	}
	
	else
	{
		return searchsplit(p->child[i],k);
	}
}

void splittree(int a,int k,int y,int z)
{
	treenode *p,*par,*big,*small,*r;
	p=searchsplit(t[a].root,k);
	int i=0,x,tp,cno;
	while (i<p->n&&k>=p->key[i]) i++;
	t[z].root=new treenode;
	t[z].root->parent=NULL;
	x=i;
	tp=0;
	while (x<p->n)
	{
		t[z].root->child[tp]=p->child[x];
		t[z].root->childcount[tp]=p->childcount[x];
		if (t[z].root->child[tp]) t[z].root->child[tp]->parent=t[z].root;
		t[z].root->key[tp]=p->key[x];
		tp++;
		x++;		
	}
	t[z].root->child[tp]=p->child[x];
	t[z].root->childcount[tp]=p->childcount[x];
	if (t[z].root->child[tp]) t[z].root->child[tp]->parent=t[z].root;
	t[z].root->n=tp;
	t[z].root->height=p->height;
	par=p;
	r=p;
	while (par->parent!=NULL)
	{
		par=par->parent;
		cno=0;		
		while (cno<=par->n&&par->child[cno]!=r) cno++;
		if (cno==par->n+1) cout<<"Error"<<endl;
		if (cno==par->n)
		{
			r=r->parent;
			continue;
		}	
		else
		{
			x=cno+1;
			big=new treenode;
			tp=0;
			if (x==par->n)
			{
				big=par->child[x];
				big->height=par->height-1;
				big->n=par->child[x]->n;
				big->parent=NULL;
			}
			else
			{
				while (x<par->n)
				{
					big->child[tp]=par->child[x];
					big->childcount[tp]=par->childcount[x];
					if (big->child[tp]) big->child[tp]->parent=big;
					big->key[tp]=par->key[x];
					x++;
					tp++;
				}
				big->child[tp]=par->child[x];
				big->childcount[tp]=par->childcount[x];
				if (big->child[tp]) big->child[tp]->parent=big;
				big->height=par->height;
				big->n=tp;
			}
			big->parent=NULL;
			join(t[z].root,par->key[cno],big,z);
		}
		r=r->parent;
	}
	
	i=0;
	while (i<p->n&&k>p->key[i]) i++;
	t[y].root=new treenode;
	x=0;
	tp=0;
	while (x<i)
	{
		t[y].root->child[tp]=p->child[x];
		t[y].root->childcount[tp]=p->childcount[x];
		if (t[y].root->child[tp]) t[y].root->child[tp]->parent=t[y].root;
		t[y].root->key[tp]=p->key[x];
		tp++;
		x++;		
	}
	t[y].root->child[tp]=p->child[x];
	t[y].root->childcount[tp]=p->childcount[x];
	if (t[y].root->child[tp]) t[y].root->child[tp]->parent=t[y].root;
	t[y].root->n=tp;
	t[y].root->height=p->height;
	t[y].root->parent=NULL;
	par=p;
	r=p;
	while (par->parent!=NULL)
	{
		par=par->parent;
		cno=0;		
		while (cno<=par->n&&par->child[cno]!=r) cno++;	
		if (cno==par->n+1) cout<<"Errors"<<endl;
		if (cno==0)
		{
			r=r->parent;
			continue;
		}	
		else
		{
			x=0;
			small=new treenode;
			tp=0;
			if (cno==1)
			{
				small=par->child[0];
				small->height=par->height-1;
				small->n=par->child[0]->n;
				small->parent=NULL;
			}
			else
			{
				while (x<cno-1)
				{
					small->child[tp]=par->child[x];
					small->childcount[tp]=par->childcount[x];
					if (small->child[tp]) small->child[tp]->parent=small;
					small->key[tp]=par->key[x];
					x++;
					tp++;
				}
				small->child[tp]=par->child[x];
				small->childcount[tp]=par->childcount[x];
				if (small->child[tp]) small->child[tp]->parent=small;
				small->height=par->height;
				small->n=tp;
				small->parent=NULL;
			}
			join(small,par->key[cno-1],t[y].root,y);
		}
		r=r->parent;
	}
}

void print(treenode*p)
{
	int i;
	for (i=0;i<p->n;i++)
	{
		if (p->child[i])
		print(p->child[i]);
		cout<<p->key[i]<<endl<<"("<<p->childcount[i]<<")"<<endl;
	}
	if (p->child[i])
	print(p->child[i]);
}
int ncount=0;
void printsum(treenode*p)
{
	int i;
	ncount+=p->n;
	for (i=0;i<p->n;i++)
	{
		if (p->child[i])
		printsum(p->child[i]);
		cout<<p->key[i]<<"("<<p->childcount[i]<<")"<<endl;
	}
	if (p->child[i])
	printsum(p->child[i]);
}
int main()
{
	int i,n,tr,j,nnode,k,m,x,y,z;
	string a;
	cin>>order;
	cin>>n;
	for (i=0;i<n;i++)
	{
		cin>>a;
		if (a=="insert")
		{
			cin>>tr;
			cin>>nnode;
			for (j=0;j<nnode;j++)
			{
				cin>>k;
				insert(tr,k);
			}
		}
		else if (a=="delete")
		{
			cin>>tr;
			cin>>nnode;
			for (j=0;j<nnode;j++)
			{
				cin>>k;
				del(tr,k);
			}
		}
		else if (a=="select")
		{
			cin>>tr;
			cin>>m;
			cout<<select(t[tr].root,m)<<endl;
		}
		else if (a=="split")
		{
			cin>>x>>k>>y>>z;
			splittree(x,k,y,z);
		}
		else if (a=="join")
		{
			cin>>x>>k>>y>>z;
			join(t[x].root,k,t[y].root,z);
		}
	}
	return 0;
}
