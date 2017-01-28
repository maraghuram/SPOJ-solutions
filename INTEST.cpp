#include<stdio.h>
int main()
{
 int n,k;
 scanf("%d%d",&n,&k);
 int cnt=0;
 while(n--)
 {
  int num;
  scanf("%d",&num);
  if(num%k==0)cnt++;
 }   
 printf("%d",cnt);
 return 0;
}%d\n",&n,&k);
    while((c = fread(b,1,size,stdin))>0)
    {
               for(j=0;j<c;j++)
               {
                if(b[j]=='\n')
                {
                              if(t%k==0)cnt++;
                              t = 0;
                }
                else
                {
                              t = (t*10) + (b[j]-'0');               
                }             
               }
     }
    printf("%d\n",cnt);   
    return 0;
}