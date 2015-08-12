#include<iostream>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;
int rnd()
{
	return rand();
}
class node
{
	public:
	node* left;
	node* right;
	node* parent;
	bool leaf;
	int val;
	int pri;
	int lc,rc;
	node()
	{
		parent=NULL;
		left=NULL;
		right=NULL;
		lc=rc=0;
		leaf=1;
	}
};

class tree
{
	public:
	node* root;
	tree()
	{
		root=NULL;
	}
	node* search(int k)
	{
		node *p=root;
		while (1)
		{
			if (k<p->val)
			{
				if (p->left)	p=p->left;
				else	return NULL;
			}
			else if (k>p->val)
			{
				if (p->right)	p=p->right;
				else	return NULL;
			}
			else return p;
		}
	}
	node* rotateleft(node* p)
	{
		node *par=p->parent;
		if (par==NULL)	return p;
		else
		{
			par->right=p->left;
			if (par->right)
			par->right->parent=par;
			else if (par->left==NULL)
			par->leaf=1;
			par->rc=p->lc;
			if (par->parent==NULL)
			{
				p->left=root;
				p->left->parent=p;
				p->lc=1+root->lc+root->rc;
				root=p;
				root->parent=NULL;
				root->leaf=0;
				return root;
			}
			else
			{
				if (par==par->parent->right)      par->parent->right=p;
				else	par->parent->left=p;
				p->parent=par->parent;
				p->left=par;
				p->left->parent=p;
				p->lc=par->lc+par->rc+1;
				p->leaf=0;
			}
			return p;
		}
	}
	node* rotateright(node* p)
	{
		node *par=p->parent;
		if (par==NULL)	return p;
		else
		{
			par->left=p->right;
			if (par->left)
			par->left->parent=par;
			else if (par->right==NULL)
			par->leaf=1;
			par->lc=p->rc;
			if (par->parent==NULL)
			{
				p->right=root;
				p->right->parent=p;
				p->rc=1+root->lc+root->rc;
				root=p;
				root->parent=NULL;
				root->leaf=0;
				return root;
			}
			else
			{
				if (par==par->parent->right)	par->parent->right=p;
				else	par->parent->left=p;
				p->parent=par->parent;
				p->right=par;
				p->right->parent=p;
				p->rc=par->lc+par->rc+1;
				p->leaf=0;
			}
			return p;
		}
	}
	void pribal(node* p)
	{
		if (p->parent==NULL)	return;
		else
		{
			while (p->pri<p->parent->pri)
			{
				if (p==p->parent->left)
				p=rotateright(p);
				else
				p=rotateleft(p);
				if (p->parent==NULL) return;
			}
		}
		return ;
	}
	void pribaldel(node* p)
	{
		if (p->leaf) return;
		node *c1=p->left;
		node *c2=p->right;
		while (1)
		{
			if (c1&&c2)
			{
				if (p->pri<=c1->pri&&p->pri<=c2->pri)
				return;
				if (c1->pri>c2->pri)
				p=rotateleft(p->right);
				else
				p=rotateright(p->left);
			}
			else if (c1&&c2==NULL)
			{
				if (p->pri<=c1->pri)
				return;
				p=rotateright(p->left);
			}
			else if (c1==NULL&&c2)
			{
				if (p->pri<=c2->pri)
				return;
				p=rotateleft(p->right);
			}
			if (p->leaf) return;
			c1=p->left;
			c2=p->right;
		}
	}
	void insert(int k)
	{
		node *p=root;
		if (root==NULL)
		{
			root=new node;
			root->val=k;
			root->pri=rnd();
			return;
		}
		while (p!=NULL)
		{
			if (k<p->val)
			{
				if (p->left)
				{
					p->lc++;
					p=p->left;
				}
				else
				{
					p->left=new node;
					p->left->val=k;
					p->left->parent=p;
					p->left->pri=rnd();
					p->lc++;
					p->leaf=0;
					pribal(p->left);
					return;
				}
			}
			else if (k>p->val)
			{
				if (p->right)
				{
					p->rc++;	
					p=p->right;
				}
				else
				{
					p->right=new node;
					p->right->val=k;
					p->right->parent=p;
					p->leaf=0;
					p->rc++;
					p->right->pri=rnd();
					pribal(p->right);
					return ;
				}
			}
			else
			{
				cout<<"Value present"<<endl;
				return ;
			}
		}
		
	}
	void del(int k)
	{
		node* p=root;
		while (1)
		{
			if (k<p->val)
			{
				if (p->left)
				{
					p->lc--;
					p=p->left;
				}
				else
				{
					cout<<"Value not present";
					return ;
				}
			}
			else if (k>p->val)
			{
				if (p->right)
				{
					p->rc--;
					p=p->right;
				}
				else
				{
					cout<<"Value Not present";
					return;
				}
			}
			else
			{
				if (p->leaf)
				{
					if (p==p->parent->left)
					{
						p->parent->left=NULL;
						if (p->parent->right==NULL)
						p->parent->leaf=1;
					}
					else
					{
						p->parent->right=NULL;
						if (p->parent->left==NULL)
						p->parent->leaf=1;
					}
					delete p;
					return;
				}
				else if (p->right!=NULL&&p->left==NULL)
				{
					if (p==p->parent->left)
					{
						p->parent->left=p->right;
						p->right->parent=p->parent;
					}
					else
					{
						p->parent->right=p->right;
						p->right->parent=p->parent;
					}
					delete p;
					return;
				}
				else if (p->right==NULL&&p->left!=NULL)
				{
					p->left->parent=p->parent;
					if (p==p->parent->left)
					p->parent->left=p->left;
					else
					p->parent->right=p->left;
					delete p;
					return;
				}
				else
				{
					node* k=p->right;
					p->rc--;
					while (k->left)
					{
						k->lc--;
						k=k->left;
					}
					p->val=k->val;
					p->pri=k->pri;
					pribaldel(p);
					if (k->right==NULL)
					{
						if (k==k->parent->left)
						{
							k->parent->left=NULL;
							if (k->parent->right==NULL)
							k->parent->leaf=1;
							delete k;
						}
						else
						{
							k->parent->right=NULL;
							if (k->parent->left==NULL)
							k->parent->leaf=1;
							delete k;
						}
						return;
					}
					else if (k->right)
					{
						k->right->parent=k->parent;
						if (k==k->parent->left)
						k->parent->left=k->right;
						else
						k->parent->right=k->right;
						delete k;
						return;
					}
				}
			}
		}
	}
};
int select(int n,node * p)
{
	if (p->lc>=n)
	return select(n,p->left);
	else if (p->lc==n-1)
	return p->val;
	else
	return select(n-(p->lc)-1,p->right);
}
int main()
{
	tree t[10001];
	int n,i,j,x,y,z,tc,treen,k;
	string a;
	cin>>tc;
	node *p;
	for (i=0;i<tc;i++)
	{
		cin>>a;
		if (a=="insert")
		{
			cin>>treen>>n;
			while (n--)
			{
				cin>>k;
				t[treen].insert(k);
			}
		}
		if (a=="delete")
		{
			cin>>treen>>n;
			while (n--)
			{
				cin>>k;
				t[treen].del(k);
			}
		}
		if (a=="select")
		{
			cin>>treen>>n;
			cout<<select(n,t[treen].root)<<endl;
		}
		if (a=="join")
		{
			cin>>x>>k>>y>>z;
			t[z].root=new node;
			t[z].root->left=t[x].root;
			t[z].root->right=t[y].root;
			t[z].root->lc=t[x].root->lc+t[x].root->rc+1;
			t[z].root->rc=t[y].root->lc+t[y].root->rc+1;
			t[z].root->val=k;
			t[z].root->pri=rnd();
			t[z].pribaldel(t[z].root);
		}
		if (a=="split")
		{
			cin>>x>>k>>y>>z;
			if (t[x].search(k)==NULL)
			t[x].insert(k);
			p=t[x].search(k);
			p->pri=-1;
			t[x].pribal(p);
			t[y].root=t[x].root->left;
			t[y].root->parent=NULL;
			t[z].root=t[x].root->right;
			t[z].root->parent=NULL;
		}
	}
	return 0;
}
