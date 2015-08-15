#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;
int cst=0;
float gen_r()
{
	return ((1.0*rand())/RAND_MAX);
}

float gen_lam(float lambda)
{
	float p;
	p=((1.0*rand())/RAND_MAX);
	return (1/lambda)*(log(1/(1-p)));
}
class event
{
	public:
	int qno;
	float t;
};
class Heap
{
	public:
	int cap;
	int n,p,t;
	event a[100001];
	Heap()
	{
		n=0;
		cap=1;
	}
	void add(float v,int q)
	{
		if (n==cap)
		{
			cap=cap*2;
			a[n].t=v;
			a[n].qno=q;
		}
		else
		{
			a[n].t=v;
			a[n].qno=q;
		}
		p=(n-1)/2;
		t=n;
		while (p>=0&&a[p].t>v)
		{
			a[t].t=a[p].t;
			a[t].qno=a[p].qno;
			a[p].t=v;
			a[p].qno=q;
			t=p;
			p=(t-1)/2;
		}
		n=n+1;
	}
	event del()
	{
		int in,mi,c1,c2;
		event tp,temp;
		in=0;
		tp=a[in];
		n--;
		a[in].t=a[n].t;
		a[in].qno=a[n].qno;
		c1=2*in+1;
		c2=2*in+2;
		if (c1>=n) return tp;
		if (c2==n)
		{
			if (a[in].t>a[c1].t)
			{
				temp=a[c1];
				a[c1]=a[in];
				a[in]=temp;
			}
			return tp;
		}
		mi=(a[c1].t>a[c2].t)?c2:c1;
		while (a[in].t>a[mi].t)
		{
			temp=a[mi];
			a[mi]=a[in];
			a[in]=temp;
			in=mi;
			c1=2*in+1;
			c2=2*in+2;
			if (c1>=n) break;
			if (c2==n)
			{
				if (a[in].t>a[c1].t)
				{
					temp=a[c1];
					a[c1]=a[in];
					a[in]=temp;
				}
				break;
			}
			mi=(a[c1].t>a[c2].t)?c2:c1;
		}
		return tp;
	}
};
class customer
{
	public:
	int id;
	int qno;
	float in_time;
	customer* next;
	customer* pre;
	customer()
	{
		next=NULL;
		pre=NULL;
		static int i=0;
		id=i++;
	}
};
class queue
{
	public:
	int id,lambda;
	int pr,q[100],out;
	float pro[100];
	customer* a[100000];
	int front,rear,pre;
	int MAX;
	queue()
	{
		static int i=0;
		id=i++;
		front=rear=pre=0;
		int j;
		MAX=100000;
	}
	void enqueue(customer* k)
	{
		if ((rear+1)%MAX==front)
		cout<<"Queue Full";
		else
		{
			a[rear]=k;
			rear=(rear+1)%MAX;
		}
		pre++;
	}
	customer* dequeue()
	{
		pre--;
		if (front==rear)
		cout<<"Queue Empty";
		else
		{
			customer* tmp=a[front];
			front=(front+1)%MAX;
			return tmp;
		}
	}
};
int main()
{
	int tp,qn,iq,n,i,j,cstout=0;
	float t,totaltime,currentime,pos,timed=0;
	event temp;
	customer* tcst=new customer;
	customer* entered=NULL;
	cin>>totaltime;
	currentime=0;
	cin>>qn;
	cin>>iq;
	queue q[qn];
	Heap a;
	for (i=0;i<qn-1;i++)
	{
		cin>>q[i].lambda;
	}	
	for (i=0;i<qn-1;i++)
	{
		cin>>tp;
		q[i].out=tp;
		for (j=0;j<tp;j++)
		{
			cin>>q[i].q[j];
			cin>>q[i].pro[j];
			if (j>0)
			q[i].pro[j]=q[i].pro[j]+pos;
			pos=q[i].pro[j];
		}
	}
	pos=0;
	for (i=0;i<iq;i++)
	{
		t=currentime+gen_lam(q[i].lambda);
		a.add(t,i);
	}
	temp=a.del();
	currentime=temp.t;
	while (currentime<totaltime)
	{
		if (temp.qno<iq)
		{
			pos=gen_r();
			j=0;
			while (j<q[temp.qno].out)
			{
				if (pos<q[temp.qno].pro[j])
				break;
				j++;
			}
			if (j==q[temp.qno].out) j--;
			tp=q[temp.qno].q[j];
			customer* newcst=new customer;
			newcst->in_time=currentime;
			if (entered!=NULL) 
			{
				entered->next=newcst;
				newcst->pre=entered;
			}
			entered=newcst;
			if (q[tp].pre==0)
			{
				q[tp].enqueue(newcst);
				t=currentime+gen_lam(q[tp].lambda);
				a.add(t,tp);
				
			}
			else
			{
				q[tp].enqueue(newcst);
			}
			t=currentime+gen_lam(q[temp.qno].lambda);
			a.add(t,temp.qno);
		}
		else
		{
			tcst=q[temp.qno].dequeue();
			if (q[temp.qno].pre)          
			{
				t=currentime+gen_lam(q[temp.qno].lambda);
				a.add(t,temp.qno);
			}
			pos=gen_r();
			j=0;
			while (j<q[temp.qno].out)
			{
				if (pos<q[temp.qno].pro[j])
				break;
				j++;
			}
			if (j==q[temp.qno].out) j--;
			tp=q[temp.qno].q[j];
			if (tp==qn-1)
			{
				if (tcst->pre!=NULL&&tcst->next!=NULL)
				{
					tcst->pre->next=tcst->next;
					tcst->next->pre=tcst->pre;
				}
				else if (tcst->pre==NULL&&tcst->next!=NULL)
				tcst->next->pre=NULL;
				else if (tcst->pre!=NULL&&tcst->next==NULL)
				{
					tcst->pre->next=NULL;
					entered=tcst->pre;
				}
				else
				entered=NULL;
				delete tcst;
				timed=timed+(currentime-tcst->in_time);
				cstout++;
			}
			else
			{
				if (q[tp].pre==0)
				{
					q[tp].enqueue(tcst);
					t=currentime+gen_lam(q[tp].lambda);
					a.add(t,tp);
				}
				else
				{
					q[tp].enqueue(tcst);
				}
			}
		}
		temp=a.del();
		currentime=temp.t;
	}
	cout<<timed/cstout<<endl;
	return 0;
}
