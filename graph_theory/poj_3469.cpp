#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#define inf INT_MAX>>1
using namespace std;
const int MAXN=20100;
struct node
{
    int value;
    int next;
    int xx;
};
vector<node>w[MAXN];

int mark[MAXN],m,n;
int step[MAXN],q[MAXN];

bool bfs(int nn)
{
    memset(mark,0,sizeof(mark));
    memset(step,0,sizeof(step));
    q[0]=nn;
    mark[nn]=1;
    int start=0,en=1;
    while(start<en)
    {
        int tt=q[start++];
        int len=w[tt].size();
        for(int ii=0;ii<len;ii++)
        {
            int son=w[tt][ii].next;
            if(!mark[son]&&w[tt][ii].value>0)
            {
                step[son]=step[tt]+1;
                mark[son]=1;
                q[en++]=son;
            }
        }
    }
    /*for(int ii=0;ii<=2*m+1;ii++)
        cout<<step[ii]<<' ';
    cout<<endl;*/
    if(mark[m+1]==1)return true;
    return false;
}

int dinic(int nn,int get_min)
{
    if(nn==m+1)return get_min;
    int len=w[nn].size(),total=0;
    for(int ii=0;ii<len&&get_min-total>0;ii++)
    {
        int son=w[nn][ii].next;
        if(step[nn]!=step[son]-1||w[nn][ii].value<=0)continue;
      //  cout<<nn<<' '<<son<<' '<<w[nn][ii].value<<endl;
        int left=dinic(son,min(get_min-total,w[nn][ii].value));
       // cout<<"left = "<<left<<endl;
        if(left==0)step[son]=-1;
        else
        {
        total+=left;
        w[nn][ii].value-=left;
        int rr=w[nn][ii].xx;
        w[son][rr].value+=left;
        }
    }
    return total;
}
void addedge(int nn,int mm,int vv)
{
    node ee;
    ee.value=vv;
    ee.next=mm;
    ee.xx=w[mm].size();
    w[nn].push_back(ee);
    ee.value=0;
    ee.next=nn;
    ee.xx=w[nn].size()-1;
    w[mm].push_back(ee);
}
void init(int nn)
{
    for(int ii=0;ii<=nn;ii++)
    w[ii].clear();
    return ;
}
int main()
{
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        init(m+1);
        for(int ii=1;ii<=m;ii++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            addedge(0,ii,x);
            addedge(ii,m+1,y);
        }
        for(int ii=1;ii<=n;ii++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            addedge(x,y,z);
            addedge(y,x,z);
        }
       /* for(int ii=0;ii<=2*m+1;ii++)
        {
            for(int jj=0;jj<w[ii].size();jj++)
                cout<<w[ii][jj].next<<' ';
            cout<<endl;
        }*/
        int uu=0;
        int ans=0;
        while(bfs(0))
            while(uu=dinic(0,inf))ans+=uu;
        printf("%d\n",ans);
    }
    return 0;
}
/*
另外一种将一个点划分为两个点的我的做法有问题；
假如是有三个点的话
1—>2,2->3
那么按照我的做法需要：
1->2',2->1',2->3',3->2'
但是，这样的话第一种可以从1走到3，但是第二种方法就不能从1走到3了。
*/
