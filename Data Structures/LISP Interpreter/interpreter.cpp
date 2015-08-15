#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<stdlib.h>
using namespace std;
class genlist
{
	public:
		int flag;
		string val;
		genlist* down;
		genlist* next;
};
class Value
{
	public:
		int tag;
		float val;
		genlist* link;
};
class Env
{
	public:
		Env* parent;
		Value* table[26];
	Env()
	{
		int i;
		for (i=0;i<26;i++)
		table[i]=NULL;
		parent=NULL;
	}
};
class list
{
	public:
	genlist* create()
	{
		genlist* head,*tp;
		tp=new genlist;
		head=NULL;
		string c;
		while (1)
		{
			cin>>c;
			while (c.compare(")")!=0&&c.compare("(")!=0)
			{
				if (head==NULL)
				{
					head=new genlist;
					head->flag=0;
					head->val=c;
					head->down=NULL;
					head->next=NULL;
					tp=new genlist;
					tp=head;
				}
				else
				{
					genlist* p;
					p=new genlist;
					p->flag=0;
					p->val=c;
					p->down=NULL;
					p->next=NULL;
					tp->next=p;
					tp=tp->next;
				}
				cin>>c;
			}
			if (c.compare(")")==0)
			{
				return head;
			}
			else
			{
				if (head==NULL)
				{
					head=new genlist;
					head->flag=1;
					head->val=c;
					head->down=create();
					head->next=NULL;
					tp=new genlist;
					tp=head;
				}
				else
				{
					genlist* p;
					p=new genlist;
					p->flag=1;
					p->val=c;
					p->down=create();
					p->next=NULL;
					tp->next=p;
					tp=tp->next;
				}
			}
		}
	}
	Value find (char c,Env &e)
	{
		if (e.table[c-97]==NULL)
		{
			if (e.parent==NULL)
			cout<<"Not Found.";
			else
			return find(c,*(e.parent));
		}
		else
		return *(e.table[c-97]);
	}
	void add(char c,Value new_val,Env& e)
	{
		Value* v=new Value;
		v->tag=new_val.tag;
		v->val=new_val.val;
		v->link=new_val.link;
		e.table[c-97]=v;
	}
	Value evalnode(genlist*p,Env& e)
	{
		if (p->flag==0)
		{
			if (p->val<="z"&&p->val>="a")
			{
				Value v=find(p->val.at(0),e);
				return v;
			}
			else
			{
				Value v;
				v.tag=0;
				v.val=atof(p->val.c_str());
				v.link=NULL;
				return v;
			}
		}
		else if (p->flag==1)
		{
			return evallist(p->down,e);
		}
	}
	Value evallist(genlist* p,Env& e)
	{
		if (p->flag==1)
		{
			Env e1;
			e1.parent=&e;
			genlist* q=p->next;
			genlist* m=p->down->next->down;
			while (m!=NULL)
			{
				add(m->val.at(0),evalnode(q,e),e1);
				m=m->next;
				q=q->next;
			}
			return evalnode(p->down->next->next,e1);
		}
		else
		{
			//operator
			if (p->val=="+"||p->val=="-"||p->val=="*"||p->val=="/"||p->val=="%"||p->val=="=="||p->val=="<="||p->val=="<"||p->val==">")
			{
				Value *val_new;
				val_new=new Value;
				val_new->tag=0;
				val_new->link=NULL;
				if (p->val=="+")
					val_new->val=evalnode(p->next,e).val + evalnode(p->next->next,e).val ;
				else if (p->val=="-")
					val_new->val=evalnode(p->next,e).val - evalnode(p->next->next,e).val ;
				else if (p->val=="*")
					val_new->val=evalnode(p->next,e).val * evalnode(p->next->next,e).val ;
				else if (p->val=="/")
					val_new->val=evalnode(p->next,e).val / evalnode(p->next->next,e).val ;
				else if (p->val=="%")
					val_new->val=(int)evalnode(p->next,e).val % (int)evalnode(p->next->next,e).val ;
				else if (p->val=="==")
					val_new->val=evalnode(p->next,e).val == evalnode(p->next->next,e).val ;
				else if (p->val=="<=")
					val_new->val=evalnode(p->next,e).val <= evalnode(p->next->next,e).val ;
				else if (p->val=="<")
					val_new->val=evalnode(p->next,e).val < evalnode(p->next->next,e).val ;
				else if (p->val==">=")
					val_new->val=evalnode(p->next,e).val >= evalnode(p->next->next,e).val ;
				else if (p->val==">")
					val_new->val=evalnode(p->next,e).val > evalnode(p->next->next,e).val ;
				return *val_new;
			}
			//keyword
			else if (p->val=="if")
			{
				if (evalnode(p->next,e).val)
				return evalnode(p->next->next,e);
				else
				return evalnode(p->next->next->next,e);
			}
			else if (p->val=="define")
			{
				add(p->next->val.at(0),evalnode(p->next->next,e),e);
				return *e.table[p->next->val.at(0)-97];
			}
			else if (p->val=="set")
			{
				add(p->next->val.at(0),evalnode(p->next->next,e),e);
				return *e.table[p->next->val.at(0)-97];
			}
			else if (p->val=="begin")
			{
				p=p->next;
				while (p->next!=NULL)
				{
					evalnode(p,e);
					p=p->next;
				}
				return evalnode(p,e);
			}
			else if (p->val=="while")
			{
				Value tp;
				while (evalnode(p->next,e).val)
				{
					tp=evalnode(p->next->next,e);
				}
				return tp;
			}
			else if (p->val=="lambda")
			{
				Value v;
				v.tag=1;
				v.val=0;
				v.link=p;
				return v;
			}
			else
			{
				Value v=evalnode(p,e);
				if (v.tag==0) return v;
				Env e1;
				e1.parent=&e;
				genlist* q=find(p->val.at(0),e).link;
				genlist* m=q;
				q=q->next->down;
				p=p->next;
				while (q!=NULL)
				{
					add(q->val.at(0),evalnode(p,e),e1);
					p=p->next;
					q=q->next;
				}
				return evalnode(m->next->next,e1);
			}
		}
	}
};
int main()
{
	list a;
	string c;
	cin>>c;
	genlist* head,*p;
	head=new genlist;
	p=new genlist;
	if (c.compare("(")==0)
	head=a.create();
	Env e;
	cout<<a.evallist(head,e).val<<endl;
	return 0;
}
