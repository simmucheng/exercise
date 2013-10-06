#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<climits>
#include<vector>
#define inf 1<<30
using namespace std;
struct node
{
    int next;
    int value;
    int sister;
};
vector<node>w[1100];
int path[1100],mark[1100],s[1100],sis[1100];
void addedge(int xx,int yy,int zz)
{
    node ee;
    ee.next=yy;
    ee.value=zz;
    w[xx].push_back(ee);
    ee.next=xx;
    w[yy].push_back(ee);
}
bool judge(int nn,int mm,int vv)
{
    if(path[nn]>path[mm]+vv||((path[nn]==path[mm]+vv)&&sis[nn]<sis[mm]+s[nn]))return true;
    return false;
}
int find_sister(int nn)
{
    path[1]=0;
    sis[1]=s[1];
    int rr=1,sum=s[1];
    while(rr!=-1)
    {
        rr=-1;
        int get_max=inf,sister=0;
        for(int ii=1;ii<=nn;ii++)
        {
            if(!mark[ii])
            {
                if(get_max>path[ii]||(get_max==path[ii]&&sister<sis[ii]))
                {
                    sister=sis[ii];
                    get_max=path[ii];
                    rr=ii;
                }
            }
        }
        if(rr==-1)break;
        mark[rr]=1;
        int len=w[rr].size();
        for(int ii=0;ii<len;ii++)
        {
            int son=w[rr][ii].next;
            if(judge(son,rr,w[rr][ii].value)&&!mark[son]){path[son]=path[rr]+w[rr][ii].value;sis[son]=sis[rr]+s[son];}
        }
    }
    if(path[nn]==inf)return -1;
    return sis[nn];
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(mark,0,sizeof(mark));
        memset(sis,0,sizeof(sis));
        for(int ii=1;ii<=n;ii++){path[ii]=inf;w[ii].clear();}
        for(int ii=1;ii<=n;ii++)scanf("%d",&s[ii]);
        for(int ii=1;ii<=m;ii++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            addedge(x,y,z);
        }
        int ans=find_sister(n);
        printf("%d\n",ans);
    }
    return 0;
}
/*
两种方法：
1.可以分优先级，如果地点距离较短的话，就选这个点，如果一样短的话，那么就选学妹多的点。
2.设置偏移量，将一个点拆成两个点，这两个点的距离设置成这个点的学妹数量的相反数，并且将其他形式的连线的权值乘以一个大于学妹
总数的值，因为只有这样才能使得距离的优先级比学妹的数量大，并且学妹的数量不会影响到距离的选择，然后就是求单源最短路
了，之后再处理一下就可以了。
*/
