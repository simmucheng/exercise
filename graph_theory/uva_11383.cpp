#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int MAXN=1e8;
int markx[510];
int marky[510];
int s[510][510];
int row[510];
int col[510];
int get_y[510];
int next[510];
int n;
bool find(int nn)
{
    markx[nn]=1;
    for(int ii=1;ii<=n;ii++)
    {
        if(!marky[ii])
        {
            int left=row[nn]+col[ii]-s[nn][ii];
            if(left==0)
            {
                marky[ii]=1;
                if(next[ii]==-1||find(next[ii]))
                {
                    next[ii]=nn;
                    return true;
                }
            }
            else get_y[ii]=min(get_y[ii],left);
        }
    }
    return false;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(next,-1,sizeof(next));
        for(int ii=1;ii<=n;ii++)
        for(int jj=1;jj<=n;jj++)
        {
            scanf("%d",&s[ii][jj]);
            row[ii]=max(s[ii][jj],row[ii]);
        }
        for(int jj=1;jj<=n;jj++)
        {
            while(1)
            {
                int get_ll=MAXN;
                memset(markx,0,sizeof(markx));
                memset(marky,0,sizeof(marky));
                for(int ii=1;ii<=n;ii++)get_y[ii]=MAXN;
                if(find(jj))break;
                for(int ii=1;ii<=n;ii++)if(!marky[ii])get_ll=min(get_y[ii],get_ll);
                for(int ii=1;ii<=n;ii++)if(markx[ii])row[ii]-=get_ll;
                for(int ii=1;ii<=n;ii++)if(marky[ii])col[ii]+=get_ll;
            }
        }
        for(int ii=1;ii<=n;ii++)
        {
            if(ii==1)printf("%d",row[ii]);
            else printf(" %d",row[ii]);
        }
        printf("\n");
        for(int ii=1;ii<=n;ii++)
        {
            if(ii==1)printf("%d",col[ii]);
            else printf(" %d",col[ii]);
        }
        printf("\n");
        int sum=0;
        for(int ii=1;ii<=n;ii++)
            sum+=s[next[ii]][ii];
        printf("%d\n",sum);
    }
    return 0;
}
