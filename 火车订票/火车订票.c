#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#define HEADER1 " ---------------------------------�𳵶�Ʊ------------------------------------\n"
#define HEADER2 " |   ����   | ʼ������ | ������� | ʼ��ʱ��  | ����ʱ��  |Ʊ�� |  ʣ��Ʊ��  |\n"
#define HEADER3 " |----------|----------|----------|-----------|-----------|-----|------------|\n"
#define FORMAT  " |%-10s|%-10s|%-10s|%-10s |%-10s |%5d|  %5d     |\n"
#define DATA p->data.num,p->data.startcity,p->data.reachcity,p->data.takeofftime,p->data.receivetime,p->data.price,p->data.ticketnum
int saveflag=0;
/*����洢����Ϣ�Ľṹ��*/
struct train
{
    char num[10];/*�г���*/
    char startcity[10];/*��������*/
    char reachcity[10];/*Ŀ�ĳ���*/
    char takeofftime[10];/*����ʱ��*/
    char receivetime[10];/*����ʱ��*/
    int  price;/*Ʊ��*/
    int  ticketnum ;/*Ʊ��*/
};
/*��Ʊ�˵���Ϣ*/
struct man 
{
    char num[10];/*ID*/
    char name[10];/*����*/
    int  bookNum ;/*����Ʊ��*/
};
/*�������Ϣ����Ľ��ṹ*/
typedef struct node 
{
    struct train data ;
    struct node * next ;
}Node,*Link ;
/*���嶩Ʊ������Ľ��ṹ*/
typedef struct Man 
{
    struct man data ;
    struct Man *next ;
}book,*bookLink ;
/* ��ʼ����*/
void menu()
{
    puts("\n\n");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|      ��ƱԤ��ϵͳ ����ܲ ���� TM �� ��Ȩ���У�     |");
    puts("\t\t|------------------------------------------------------|");
    puts("\t\t|       0:�뿪                                         |");
    puts("\t\t|       1:����һ���µĻ�Ʊ��Ϣ������Ա��             |");
    puts("\t\t|       2:���һ�Ʊ                                   |");
    puts("\t\t|       3:Ԥ��/�����Ʊ                              |");
    puts("\t\t|       4:���Ļ�Ʊ��Ϣ������Ա��                     |");
    puts("\t\t|       5:��ʾ���л�Ʊ��Ϣ                           |");
    puts("\t\t|       6:������Ϣ                                     |");
    puts("\t\t|------------------------------------------------------|");
}
/*���һ������Ϣ*/
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
        printf("���복��(0-return)��");
        scanf("%s",num);
        if(strcmp(num,"0")==0)
          break ;
        /*�ж��Ƿ��Ѿ�����*/
        while(s)
        {
            if(strcmp(s->data.num,num)==0)
            {
                printf("�г� '%s'�Ѿ�����!\n",num);
                return ;
            }
            s = s->next ;
        }
        p = (struct node*)malloc(sizeof(struct node));
        strcpy(p->data.num,num);/*���복��*/
	 printf("�����������:");
        scanf("%s",p->data.startcity);/*�����������*/
        printf("���뵽վ����:");
        scanf("%s",p->data.reachcity);/*���뵽վ����*/
        printf("�������ʱ��:");
	scanf("%s",p->data.takeofftime);/*�������ʱ��*/
        printf("���뵽վʱ��:");
	scanf("%s",&p->data.receivetime);/*���뵽վʱ��*/
        printf("�����Ʊ��:");
        scanf("%d",&p->data.price);/*�����Ʊ��*/
        printf("�����Ԥ��Ʊ��:");
	scanf("%d",&p->data.ticketnum);/*����Ԥ��Ʊ��*/
        p->next=NULL ;
        r->next=p ;/*���뵽������*/
        r=p ;
       saveflag = 1 ;
    }
}
/*��ӡ��Ʊ��Ϣ*/
void printheader() /*��ʽ�������ͷ*/
{
printf(HEADER1);
printf(HEADER2);
printf(HEADER3);
}
void printdata(Node *q) /*��ʽ�������������*/
{
Node* p;
p=q;
printf(FORMAT,DATA);
}

/*��ѯ����Ϣ*/
void searchtrain(Link l)

{
    Node *s[10],*r;
    int sel,k,i=0 ;
    char str1[5],str2[10];
    if(!l->next)
    {
        printf("δ�ҵ��κο��õĻ���Ϣ !");
        return ;
    }
    printf("ѡ��һ�����ҷ�ʽ:\n1:�ӳ��Ų���(��ȷ����);\n2:��ǰ�����в���(ģ������)��:\n");
    scanf("%d",&sel);/*����ѡ������*/
    if(sel==1)
    {
        printf("�����복��:");
        scanf("%s",str1);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.num,str1)==0)/*�����Ƿ���������ĳ�����ƥ���*/
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
        printf("����������Ҫǰ���ĳ���:");
        scanf("%s",str2);
        r=l->next;
	while(r!=NULL)
        if(strcmp(r->data.reachcity,str2)==0)/*�����Ƿ���������ĳ�����ƥ��Ļ�*/
        {
            s[i]=r;
	    i++;
	    r=r->next;
        }
        else 
            r=r->next;
    }
    	if(i==0)
		printf("�Ҳ���ƥ����г�!");
	else
	{
		printheader();
    for(k=0;k<i;k++)
printdata(s[k]);
	}
}

/*��Ʊ��ģ��*/
void Bookticket(Link l,bookLink k)
{
    Node *r[10],*p ;
    char ch[2],tnum[10],str[10],str1[10],str2[10];
    book *q,*h ;
    int i=0,t=0,flag=0,dnum;
    q=k ;
    while(q->next!=NULL)
    q=q->next ;
    printf("��������Ҫǰ���ĳ���: ");
    scanf("%s",&str);/*����Ҫ����ĳ���*/
    p=l->next ;
    while(p!=NULL)
    {
        if(strcmp(p->data.reachcity,str)==0)
        {
            r[i]=p ;/*�����������ļ�¼�浽����r��*/
            i++;
        }
        p=p->next ;
    }
    printf("\n\n���ҵ� %d ��ƥ����г���\n",i);
       printheader();
    for(t=0;t<i;t++)
	    printdata(r[t]);
    if(i==0)
    printf("\nû���ҵ��κ�ƥ��Ļ�Ʊ��Ϣ��"); 
    {
        printf("\n���빺�����Ż�Ʊ��?<y/n>\n");
        scanf("%s",ch);
	if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0)/*�ж��Ƿ�Ʊ*/
        {
	    h=(book*)malloc(sizeof(book));
            printf("������������: ");
            scanf("%s",&str1);
            strcpy(h->data.name,str1);
            printf("�����������ID: ");
            scanf("%s",&str2);
            strcpy(h->data.num,str2);
	    printf("�����복��:");
	    scanf("%s",tnum);
	    for(t=0;t<i;t++)
	    if(strcmp(r[t]->data.num,tnum)==0)
	    {
	       if(r[t]->data.ticketnum<1)/*�ж�ʣ��Ĺ���Ʊ��Ʊ���Ƿ�Ϊ0*/
	       {
		       printf("������˼��û��ʣ��Ļ�Ʊ�ˣ�");
		       sleep(2);
		       return;
	       }
	      printf("ʣ�� %d �ų�Ʊ��\n",r[t]->data.ticketnum);
               flag=1;
	       break;
	    }
	    if(flag==0)
	    {
		    printf("�������");
		   sleep(2);
                    return;
	    }
	    printf("�������빺���Ʊ��: ");
            scanf("%d",&dnum);
            r[t]->data.ticketnum=r[t]->data.ticketnum-dnum;/*��Ʊ�ɹ���ɹ�����Ʊ����Ӧ����*/
	    h->data.bookNum=dnum ;
            h->next=NULL ;
	    q->next=h ;
	    q=h ;
            printf("\nԤ���ɹ���");
            getch();
            saveflag=1 ;
        }
    }
}
/*�޸Ļ���Ϣ*/
void Modify(Link l)
{
    Node *p ;
    char tnum[10],ch ;
    p=l->next;
    if(!p)
    {
        printf("\nû�пɹ����ĵ��г���Ϣ��\n");
        return ;
    }
    else
    {
	    printf("\n����Ҫ���Ĵ��г���Ϣ��?(y/n)\n");
            getchar();
            scanf("%c",&ch);
            if(ch=='y'||ch=='Y')
            {
                printf("\n�����복��:");
		scanf("%s",tnum);
	while(p!=NULL)
	if(strcmp(p->data.num,tnum)==0)/*����������ĳ�����ƥ��ļ�¼*/
	    break;
        else
            p=p->next;
                if(p)
                {
                    printf("�������³���:");
                    scanf("%s",&p->data.num);
		    printf("�������г���Ҫʼ�����³���:");
                    scanf("%s",&p->data.startcity);
                    printf("�������г���Ҫ������³���:");
                    scanf("%s",&p->data.reachcity);
                    printf("�������г���ʼ��ʱ��:");
		    scanf("%s",&p->data.takeofftime);
                    printf("�������г��µ���ʱ��:");
		    scanf("%s",&p->data.receivetime);
                    printf("�����г���Ʊ��:");
                    scanf("%d",&p->data.price);
                    printf("�����г��µĿ�Ԥ��Ʊ��:");
                    scanf("%d",&p->data.ticketnum);
                    printf("\n�޸ĳɹ���\n");
                    saveflag=1 ;
                }
                else
                printf("\t�Ҳ�����Ϣ��");
            }
    }
}
void showtrain(Link l)/*�Զ��庯����ʾ�г���Ϣ*/
{
Node *p;
p=l->next;
printheader();
if(l->next==NULL)
printf("�Ҳ����κ���Ϣ��");
else
 while(p!=NULL)
{
	printdata(p);
	p=p->next;
}
}
/*�������Ϣ*/
void SaveTrainInfo(Link l)
{
    FILE*fp ;
    Node*p ;
    int count=0,flag=1 ;
    fp=fopen("D:\\train.txt","wb");
    if(fp==NULL)
    {
        printf("�򲻿����ļ���");
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
        printf(" ������ %d ���г���Ϣ��\n",count);
        saveflag=0 ;
    }
    fclose(fp);
}
/*���涩Ʊ�˵���Ϣ*/
void SaveBookInfo(bookLink k)
{
    FILE*fp ;
    book *p ;
    int count=0,flag=1 ;
    fp=fopen("D:\\man.txt","wb");
    if(fp==NULL)
    {
        printf("�򲻿����ļ���");
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
        printf(" ������ %d ����Ʊ��Ϣ��\n",count);
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
    fp1=fopen("D:\\train.txt","ab+");/*�򿪴洢��Ʊ��Ϣ���ļ�*/
    if((fp1==NULL))
    {
        printf("�򲻿����ļ�!");
        return 0 ;
    }
    while(!feof(fp1))
    {
        p=(Node*)malloc(sizeof(Node));
        if(fread(p,sizeof(Node),1,fp1)==1)/*��ָ�������ļ���ȡ��¼*/
        {
            p->next=NULL ;
            r->next=p ;/*��������*/
            r=p ;
        }
    }
    fclose(fp1);
    fp2=fopen("D:\\man.txt","ab+");
    if((fp2==NULL))
    {
        printf("�򲻿����ļ�!");
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
        printf("\tѡ�� (0~6):  ");
        scanf("%d",&sel);
        system("CLS"); 
        if(sel==0)
        {
	    if(saveflag==1)/*���˳�ʱ�ж���Ϣ�Ƿ񱣴�*/
            {
                getchar();
                printf("\n��Ϣ�Ѿ����޸�!����Ҫ��������(y/n)?\n");
                scanf("%c",&ch1);
                if(ch1=='y'||ch1=='Y')
                {
		    SaveBookInfo(k);
                    SaveTrainInfo(l);
                }
            }
            printf("\n�ǳ���л��\n");
            break ;

        }
        switch(sel)/*���������selֵ��ͬѡ����Ӧ����*/
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
        printf("\n�밴���������...");
        getch();
    }
}
