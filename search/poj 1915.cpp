#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct node
{
    int x;
    int y;
    int mark;
    int step;
}s[2];
int dir[8][2]={1,2,1,-2,-1,2,-1,-2,2,-1,2,1,-2,1,-2,-1};
int mark1[310][310];
int mark2[310][310];
queue<node>q;
int dbfs(int len)
{
    while(!q.empty())
    {
        node tt=q.front();
        q.pop();
        //cout<<tt.x<<' '<<tt.y<<' '<<tt.step<<' '<<tt.mark<<endl;
        node rr;
        for(int ii=0;ii<8;ii++)
        {
            rr.x=tt.x+dir[ii][0];
            rr.y=tt.y+dir[ii][1];
            rr.step=tt.step+1;
            rr.mark=tt.mark;
          //  cout<<rr.x<<' '<<rr.y<<' '<<rr.step<<' '<<rr.mark<<endl;
            if(rr.x<0||rr.x>=len||rr.y<0||rr.y>=len)continue;
            if(rr.mark==1&&mark1[rr.x][rr.y]!=-1)continue;
            else if(rr.mark==2&&mark2[rr.x][rr.y]!=-1)continue;
            if(rr.mark==1)mark1[rr.x][rr.y]=rr.step;
            else mark2[rr.x][rr.y]=rr.step;
            if(mark1[rr.x][rr.y]!=-1&&mark2[rr.x][rr.y]!=-1)return mark1[rr.x][rr.y]+mark2[rr.x][rr.y];
            q.push(rr);
        }
    }
    return 0;
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        while(!q.empty())q.pop();
        memset(mark1,-1,sizeof(mark1));
        memset(mark2,-1,sizeof(mark2));
        int ll;
        scanf("%d",&ll);
        node w;
        for(int ii=0;ii<=1;ii++)
         {
             scanf("%d%d",&s[ii].x,&s[ii].y);
             s[ii].step=0;
             if(ii==0)s[ii].mark=1;
             else s[ii].mark=2;
             q.push(s[ii]);
         }
        mark1[s[0].x][s[0].y]=0;
        mark2[s[1].x][s[1].y]=0;
        if(s[0].x==s[1].x&&s[0].y==s[1].y){printf("0\n");continue;}
        int ans=dbfs(ll);
        printf("%d\n",ans);
    }
    return 0;
}
