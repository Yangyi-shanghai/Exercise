#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#define HEADER1 " ---------------------------------火车订票------------------------------------\n"
#define HEADER2 " |   车号   | 始发城市 | 到达城市 | 始发时间  | 到达时间  |票价 |  剩余票数  |\n"
#define HEADER3 " |----------|----------|----------|-----------|-----------|-----|------------|\n"
#define FORMAT  " |%-10s|%-10s|%-10s|%-10s |%-10s |%5d|  %5d     |\n"
#define DATA p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketnum
int saveflag=0;
/*定义存储火车信息的结构体*/
struct train
{
    char num[10];/*列车号*/
    char startcity[10];/*出发城市*/
    char reachcity[10];/*目的城市*/
    char takeofftime[10];/*发车时间*/
    char receivetime[10];/*到达时间*/
    int  price;/*票价*/
    int  ticketnum ;/*票数*/
};
/*订票人的信息*/
struct man 
{
    char num[10];/*ID*/
    char name[10];/*姓名*/
    int  bookNum ;/*订的票数*/
};
/*定义火车信息链表的结点结构*/
typedef struct node 
{
    struct train data ;
    struct node * next ;
}Node,*Link ;
/*定义订票人链表的结点结构*/
typedef struct Man 
{
    struct man data ;
    struct Man *next ;
}book,*bookLink ;
/* 初始界面*/
void menu()
{
    puts("\n\n");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|      火车票预订系统 （杨懿 制作 TM 和 版权所有）     |");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|       0:离开                                         |");
    puts("\t\t|       1:创建一个新的火车票信息（管理员）             |");
    puts("\t\t|       2:查找火车票                                   |");
    puts("\t\t|       3:预订/购买火车票                              |");
    puts("\t\t|       4:更改火车票信息（管理员）                     |");
    puts("\t\t|       5:显示所有火车票信息                           |");
    puts("\t\t|       6:保存信息                                     |");
    puts("\t\t|------------------------------------------------------|");
}
/*添加一个火车信息*/
void Traininfo(Link linkhead)
{
    struct node *p,*r,*s ;
    char num[10];
    r = linkhead ;
    s = linkhead->next ;
    while(r->next!=NULL)
    r=r->next ;
    while(1)
    {
        printf("输入车号(0-return)：");
        scanf("%s",num);
        if(strcmp(num,"0")==0)
          break ;
        /*判断是否已经存在*/
        while(s)
        {
            if(strcmp(s->data.num,num)==0)
            {
                printf("列车 '%s'已经存在!\n",num);
                return ;
            }
            s = s->next ;
        }
        p = (struct node*)malloc(sizeof(struct node));
        strcpy(p->data.num,num);/*输入车号*/
	 printf("输入出发城市:");
        scanf("%s",p->data.startcity);/*输入出发城市*/
        printf("输入到站城市:");
        scanf("%s",p->data.reachcity);/*输入到站城市*/
        printf("输入出发时间:");
	scanf("%s",p->data.takeofftime);/*输入出发时间*/
        printf("输入到站时间:");
	scanf("%s",&p->data.receivetime);/*输入到站时间*/
        printf("输入火车票价:");
        scanf("%d",&p->data.price);/*输入火车票价*/
        printf("输入可预定票数:");
	scanf("%d",&p->data.ticketnum);/*输入预定票数*/
        p->next=NULL ;
        r->next=p ;/*插入到链表中*/
        r=p ;
       saveflag = 1 ;
    }
}
/*打印火车票信息*/
void printheader() /*格式化输出表头*/
{
printf(HEADER1);
printf(HEADER2);
printf(HEADER3);
}
void printdata(Node *q) /*格式化输出表中数据*/
{
Node* p;
p=q;
printf(FORMAT,DATA);
}

/*查询火车信息*/
void searchtrain(Link l)

{
    Node *s[10],*r;
    int sel,k,i=0 ;
    char str1[5],str2[10];
    if(!l->next)
    {
        printf("未找到任何可用的火车信息 !");
        return ;
    }
    printf("选择一个查找方式:\n1:从车号查找(精确查找);\n2:从前往城市查找(模糊查找)。:\n");
    scanf("%d",&sel);/*输入选择的序号*/
    if(sel==1)
    {
        printf("请输入车号:");
        scanf("%s",str1);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.num,str1)==0)/*检索是否有与输入的车号相匹配的*/
        {
            s[i]=r;
	    i++;
	    break;
        }
        else 
            r=r->next;
    }
    else if(sel==2)
    {
        printf("请输入您想要前往的城市:");
        scanf("%s",str2);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.reachcity,str2)==0)/*检索是否有与输入的城市相匹配的火车*/
        {
            s[i]=r;
	    i++;
	    r=r->next;
        }
        else 
            r=r->next;
    }
    	if(i==0)
		printf("找不到匹配的列车!");
	else
	{
		printheader();
    for(k=0;k<i;k++)
printdata(s[k]);
	}
}

/*订票子模块*/
void Bookticket(Link l,bookLink k)
{
    Node *r[10],*p ;
    char ch[2],tnum[10],str[10],str1[10],str2[10];
    book *q,*h ;
    int i=0,t=0,flag=0,dnum;
    q=k ;
    while(q->next!=NULL)
    q=q->next ;
    printf("输入您想要前往的城市: ");
    scanf("%s",&str);/*输入要到达的城市*/
    p=l->next ;
    while(p!=NULL)
    {
        if(strcmp(p->data.reachcity,str)==0)
        {
            r[i]=p ;/*将满足条件的记录存到数组r中*/
            i++;
        }
        p=p->next ;
    }
    printf("\n\n查找到 %d 辆匹配的列车。\n",i);
       printheader();
    for(t=0;t<i;t++)
	    printdata(r[t]);
    if(i==0)
    printf("\n没有找到任何匹配的火车票信息！"); 
    {
        printf("\n您想购买这张火车票吗?<y/n>\n");
        scanf("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*判断是否订票*/
        {
	    h=(book*)malloc(sizeof(book));
            printf("输入您的名字: ");
            scanf("%s",&str1);
            strcpy(h->data.name,str1);
            printf("输入您的身份ID: ");
            scanf("%s",&str2);
            strcpy(h->data.num,str2);
	    printf("请输入车号:");
	    scanf("%s",tnum);
	    for(t=0;t<i;t++)
	    if(strcmp(r[t]->data.num,tnum)==0)
	    {
	       if(r[t]->data.ticketnum<1)/*判断剩余的供订票的票数是否为0*/
	       {
		       printf("不好意思，没有剩余的火车票了！");
		       sleep(2);
		       return;
	       }
	      printf("剩余 %d 张车票。\n",r[t]->data.ticketnum);
               flag=1;
	       break;
	    }
	    if(flag==0)
	    {
		    printf("输入错误");
		   sleep(2);
                    return;
	    }
	    printf("输入您想购买的票数: ");
            scanf("%d",&dnum);
            r[t]->data.ticketnum=r[t]->data.ticketnum-dnum;/*定票成功则可供订的票数相应减少*/
	    h->data.bookNum=dnum ;
            h->next=NULL ;
	    q->next=h ;
	    q=h ;
            printf("\n预订成功！");
            getch();
            saveflag=1 ;
        }
    }
}
/*修改火车信息*/
void Modify(Link l)
{
    Node *p ;
    char tnum[10],ch ;
    p=l->next;
    if(!p)
    {
        printf("\n没有可供更改的列车信息！\n");
        return ;
    }
    else
    {
	    printf("\n您想要更改此列车信息吗?(y/n)\n");
            getchar();
            scanf("%c",&ch);
            if(ch=='y'||ch=='Y')
            {
                printf("\n请输入车号:");
		scanf("%s",tnum);
	while(p!=NULL)
	if(strcmp(p->data.num,tnum)==0)/*查找与输入的车号相匹配的记录*/
	    break;
        else
            p=p->next;
                if(p)
                {
                    printf("请输入新车号:");
                    scanf("%s",&p->data.num);
		    printf("请输入列车将要始发的新城市:");
                    scanf("%s",&p->data.startcity);
                    printf("请输入列车将要到达的新城市:");
                    scanf("%s",&p->data.reachcity);
                    printf("请输入列车新始发时间:");
		    scanf("%s",&p->data.takeofftime);
                    printf("请输入列车新到达时间:");
		    scanf("%s",&p->data.receivetime);
                    printf("输入列车新票价:");
                    scanf("%d",&p->data.price);
                    printf("输入列车新的可预订票数:");
                    scanf("%d",&p->data.ticketnum);
                    printf("\n修改成功！\n");
                    saveflag=1 ;
                }
                else
                printf("\t找不到信息！");
            }
    }
}
void showtrain(Link l)/*自定义函数显示列车信息*/
{
Node *p;
p=l->next;
printheader();
if(l->next==NULL)
printf("找不到任何信息！");
else
 while(p!=NULL)
{
	printdata(p);
	p=p->next;
}
}
/*保存火车信息*/
void SaveTrainInfo(Link l)
{
    FILE*fp ;
    Node*p ;
    int count=0,flag=1 ;
    fp=fopen("D:\\train.txt","wb");
    if(fp==NULL)
    {
        printf("打不开此文件！");
        return ;
    }
    p=l->next ;
    while(p)
    {
        if(fwrite(p,sizeof(Node),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf(" 保存了 %d 个列车信息。\n",count);
        saveflag=0 ;
    }
    fclose(fp);
}
/*保存订票人的信息*/
void SaveBookInfo(bookLink k)
{
    FILE*fp ;
    book *p ;
    int count=0,flag=1 ;
    fp=fopen("D:\\man.txt","wb");
    if(fp==NULL)
    {
        printf("打不开此文件！");
        return ;
    }
    p=k->next ;
    while(p)
    {
	if(fwrite(p,sizeof(book),1,fp)==1)
        {
            p=p->next ;
            count++;
        }
        else
        {
            flag=0 ;
            break ;
        }
    }
    if(flag)
    {
        printf(" 保存了 %d 个购票信息。\n",count);
        saveflag=0 ;
    }
    fclose(fp);
}

main()
{
    FILE*fp1,*fp2 ;
    Node *p,*r ;
    char ch1,ch2 ;
    Link l ;
    bookLink k ;
    book *t,*h ;
    int sel ;
    l=(Node*)malloc(sizeof(Node));
    l->next=NULL ;
    r=l ;
    k=(book*)malloc(sizeof(book));
    k->next=NULL ;
    h=k ;
    fp1=fopen("D:\\train.txt","ab+");/*打开存储车票信息的文件*/
    if((fp1==NULL))
    {
        printf("打不开此文件!");
        return 0 ;
    }
    while(!feof(fp1))
    {
        p=(Node*)malloc(sizeof(Node));
        if(fread(p,sizeof(Node),1,fp1)==1)/*从指定磁盘文件读取记录*/
        {
            p->next=NULL ;
            r->next=p ;/*构造链表*/
            r=p ;
        }
    }
    fclose(fp1);
    fp2=fopen("D:\\man.txt","ab+");
    if((fp2==NULL))
    {
        printf("打不开此文件!");
        return 0 ;
    }
    
    while(!feof(fp2))
    {
        t=(book*)malloc(sizeof(book));
        if(fread(t,sizeof(book),1,fp2)==1)
        {
            t->next=NULL ;
            h->next=t ;
            h=t ;
        }
    }
    fclose(fp2);
    while(1)
    {
        system("CLS");
        menu();
        printf("\t选择 (0~6):  ");
        scanf("%d",&sel);
        system("CLS"); 
        if(sel==0)
        {
	    if(saveflag==1)/*当退出时判断信息是否保存*/
            {
                getchar();
                printf("\n信息已经被修改!您想要保存它吗(y/n)?\n");
                scanf("%c",&ch1);
                if(ch1=='y'||ch1=='Y')
                {
		    SaveBookInfo(k);
                    SaveTrainInfo(l);
                }
            }
            printf("\n非常感谢！\n");
            break ;

        }
        switch(sel)/*根据输入的sel值不同选择相应操作*/
        {
            case 1 :
              Traininfo(l);break ;
            case 2 :
              searchtrain(l);break ;
            case 3 :
              Bookticket(l,k);break ;
            case 4 :
              Modify(l);break ;
	    case 5:
		    showtrain(l);break;
            case 6 :
	      SaveTrainInfo(l);SaveBookInfo(k);break ;
            case 0:
            return 0;
        }
        printf("\n请按任意键继续...");
        getch();
    }
}
