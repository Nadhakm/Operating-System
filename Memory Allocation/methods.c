#include <stdio.h>

void firstfit(int p,int pblock[],int m,int mblock[]) 
{
    printf("\t\tFIRST FIT\n");
    int i,j,p_block[100],m_block[100];
    for(i=0;i<p;i++)
    {
        p_block[i]=pblock[i];
    }
    for(i=0;i<m;i++)
    {
        m_block[i]=mblock[i];
    }
    
    for(i=0;i<p;i++)
    {
        int flag=0;
        for(j=0;j<m;j++)
        {
            if(m_block[j]>=p_block[i])
            {
                printf("%d allocated to %d block ",p_block[i],m_block[j]);
                m_block[j]-=p_block[i];
                flag=1;
                printf("=> %d left\n",m_block[j]);
                break;
            }
        }
        if(flag==0)
        {
            printf("%d cannot be allocated\n",p_block[i]);
        }
    }
}

void bestfit(int p,int pblock[],int m,int mblock[])
{
    printf("\t\tBEST FIT\n");
    int i,j,p_block[100],m_block[100];
    for(i=0;i<p;i++)
    {
        p_block[i]=pblock[i];
    }
    for(i=0;i<m;i++)
    {
        m_block[i]=mblock[i];
    }
    
    for(i=0;i<p;i++)
    {
        int loc=-1;
        for(j=0;j<m;j++)
        {
            if(m_block[j]>=p_block[i])
            {
                if(loc==-1)
                {
                    loc=j;
                }
                else if(m_block[loc]>m_block[j])
                {
                    loc=j;
                }
            }
        }
        if(loc!=-1)
        {
            printf("%d allocated to %d block ",p_block[i],m_block[loc]);
            m_block[loc]-=p_block[i];
            printf("=> %d left\n",m_block[loc]);
        }
        else
        {
            printf("%d cannot be allocated\n",p_block[i]);
        }
    }
}

void worstfit(int p,int pblock[],int m,int mblock[])
{
    printf("\t\tWORST FIT\n");
    int i,j,p_block[100],m_block[100];
    for(i=0;i<p;i++)
    {
        p_block[i]=pblock[i];
    }
    for(i=0;i<m;i++)
    {
        m_block[i]=mblock[i];
    }
    
    for(i=0;i<p;i++)
    {
        int max=m_block[0];
        int loc=0;
        for(j=0;j<m;j++)
        {
            if(m_block[j]>max)
            {
                max=m_block[j];
                loc=j;
            }
        }
        if(m_block[loc]>=p_block[i])
        {
            printf("%d allocated to %d block ",p_block[i],m_block[loc]);
            m_block[loc]-=p_block[i];
            printf("=> %d left\n",m_block[loc]);
        }
        else
        {
            printf("%d cannot be allocated\n",p_block[i]);
        }
    }
}

int main()
{
    int process,processblock[100],memory,memoryblock[100],i;
    printf("Enter number of process: ");
    scanf("%d",&process);
    printf("Enter array of process: ");
    for(i=0;i<process;i++)
    {
        scanf("%d",&processblock[i]);
    }
    printf("Enter number of block: ");
    scanf("%d",&memory);
    printf("Enter array of block: ");
    for(i=0;i<memory;i++)
    {
        scanf("%d",&memoryblock[i]);
    }
    
    firstfit(process,processblock,memory,memoryblock);
    bestfit(process,processblock,memory,memoryblock);
    worstfit(process,processblock,memory,memoryblock);
    
    return 0;
}
