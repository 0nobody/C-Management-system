#include<stdio.h>
#include<stdlib.h>//exit()、malloc()
#include<conio.h>//gtetch()：该函数可以不回显函数值
#include<windows.h>//清屏
#include<string.h>
#define LEN sizeof(struct Drug)
struct Drug
{	
 char Mname[20];//名称
 char manufacturers[30];//厂家
 char Mtype[10];//类别
 double Mprice;//价格
 double Mstock;//库存
 struct Drug*next;//指针变量
};



void regist()//注册
{
   void login();
   FILE *fp;//指向文件的指针变量
   int la,lb;
   char a[20],b[20],c[20];
   if((fp=fopen("zh.txt","r"))!=NULL)
   {
	   printf("抱歉该系统只能注册一个管理员账户，若要重新注册请登陆后格式化。\n");
       printf("按任意键登录");
	   fclose(fp);
       getch();
	   login();
   }

   system("cls");
   while(1)
   {
    printf("请输入注册账号（不得超过10位）：");
    scanf("%s",a);
    la=strlen(a);
    if(la>10)
	   printf("输入账号过长，请重新输入。");
    else 
    break;
   }
   while(1)
   {
    printf("请输入注册密码（不得超过10位）：");
    scanf("%s",b);
	lb=strlen(b);
    if(lb>10)
	   printf("输入密码过长，请重新输入。");
    else 
    break;
   }
   while(1)
   {
    printf("请再次输入注册密码：");
    scanf("%s",c);
    if(strcmp(b,c))
	   printf("两次密码不同，请重新输入。\n");
    else 
    break;
   }
   fp=fopen("zh.txt", "w");
   fprintf(fp,"%s %s",a,b);
   fclose(fp);
   printf("注册成功！\n");
   printf("按任意键返回登录界面");
   getch();
}



void login()//登录
{
	FILE *fp;
	char a[20],b[20],d[20],e[20];
	if((fp=fopen("zh.txt","r"))==NULL)
    {
	printf("抱歉该系统未注册管理员账户，请先注册。\n");
    printf("按任意键注册");
    getch();
	regist();
	}
	fclose(fp);
	system("cls");
    printf("请输入登录账号：");
    scanf("%s",d);
	printf("请输入登录密码：");
    scanf("%s",e);
	fp=fopen("zh.txt","r");
	fscanf(fp,"%s %s",&a,&b);
	fclose(fp);
	if(!strcmp(a,d)&&!strcmp(b,e))
	{
		printf("登录成功！");
		printf("按任意键进入系统");
        getch();
	}
	else
	{
		printf("账号或密码错误，登陆失败，请重试！");
		getch();
		login();
	}
}



void start()//登录界面
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************药品信息管理系统********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 《注册》：                                                  *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 《登录》：                                                  *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 《退出》：                                                  *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~3）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:regist();break;
	case 2:login();break;
    case 3:exit(0);
    default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
	if(x==2)
		break;
	}
}



struct Drug *creat()//初始化信息
{
	struct Drug *head,*p1,*p2;
    int flag=0;
	char a[]="over";
	printf("请输入药品的信息(药名为over时结束):\n");
	p1=p2=(struct Drug*)malloc(LEN);
	memset(p1,0,LEN);//初始化结构体
	scanf("%s%s%s%lf%lf",p1->Mname,p1->manufacturers,p1->Mtype,&p1->Mprice,&p1->Mstock);
	head=NULL;
	while(strcmp(p1->Mname,a))
	{
		flag++;
		if(flag==1) 
			head=p1;
		else 
		p2->next=p1;
		p2=p1;
        p1=(struct Drug*)malloc(LEN);
		memset(p1,0,LEN);
	    scanf("%s%s%s%lf%lf",p1->Mname,p1->manufacturers,p1->Mtype,&p1->Mprice,&p1->Mstock);
	}
	p2->next=NULL;
	printf("药品信息输入已完成\n");
    printf("按任意键键继续");
    getch();
	return(head);
}



void save(struct Drug *head)//函数内保存
{  
	FILE *fp;
    struct Drug *p;
	if((fp=fopen("drug.txt","wb"))==NULL)
	{
		printf("打开文件失败 ！\n");
		exit(0); 
	}
	p=head;
	while (p!=NULL) 
	{
	fwrite(p,LEN,1,fp);
	p=p->next;
	}
	fclose(fp);
}



void display(struct Drug *head)//显示信息
{
	FILE *fp;
	struct Drug *p;
    printf("*药品名称*          *药品厂家*                    *药品类别*          *药品的价格*        *库存*\n");
    if((fp=fopen("drug.txt","rb"))==NULL)
	{
	 printf("打开文件失败！\n");
	 exit(0);
	}
 	p=head;
	while(p!=NULL) 
	{
	fread(p,LEN,1,fp);
	printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
	p=p->next;
	}
    fclose(fp);
    printf("药品信息显示已完成\n");
    printf("按任意键键继续");
    getch();
}



struct Drug *again()//加载信息
{
	FILE *fp;
	struct Drug *head,*p1,*p2;
	struct Drug temp;
	int flag=0;
	p1=p2=(struct Drug*)malloc(LEN);
	memset(p1,0,LEN);
	head=NULL;
	fp=fopen("drug.txt","rb");
	while(fread(&temp,LEN,1,fp)!=0)
	{
        p1=(struct Drug*)malloc(LEN);
		memset(p1,0,LEN);
		strcpy(p1->Mname,temp.Mname);
		strcpy(p1->manufacturers,temp.manufacturers);
		strcpy(p1->Mtype,temp.Mtype);
		p1->Mprice=temp.Mprice;
		p1->Mstock=temp.Mstock;
		flag++;
		if(flag==1)
			head=p1;
		else
			p2->next=p1;
		p2=p1;
	}
	p2->next=NULL;
    save(head);
	fclose(fp);
	return (head);
}



void add(struct Drug *head)//添加信息
{
 FILE *fp;
 struct Drug*p1,*p2=NULL,*p3;
 if((fp=fopen("drug.txt","ab+"))==NULL)
 {
	 printf("打开文件失败！\n");
	 exit(0);
 }
 printf("药品信息添加\n");
 p1=head;
 p3=(struct Drug*)malloc(LEN);
 memset(p3,0,LEN);
 scanf("%s%s%s%lf%lf",p3->Mname,p3->manufacturers,p3->Mtype,&p3->Mprice,&p3->Mstock);
 if(p1->next==NULL)
 {
	 p1->next=p3;
	 p3->next=NULL;
 }
 else
while(p1->next!=NULL)
	 {
		 p2=p1;
		 p1=p1->next;
	 }
p1->next=p3;
p3->next=NULL;
save(head);
fclose(fp);
printf("药品信息添加已完成\n");
printf("按任意键继续");
getch();
}



void dele(struct Drug *head)//删除信息
{
 struct Drug *p1,*p2;
 char a[20];
 printf("药品信息删除\n");
 printf("请输入要删除的药品名:");
 scanf("%s",&a);
 p1=head;
 while(strcmp(p1->Mname,a)&&p1->next!=NULL)
 {
	 p2=p1;
	 p1=p1->next;
 }
 if(!strcmp(p1->Mname,a))
 {
	 if(p1==head)
		 head=p1->next;
	 else
		 p2->next=p1->next;
 }
 else 
	 printf("该药品不在药品库中！\n");
save(head);
printf("药品信息删除已完成\n");
printf("按任意键继续");
getch();
}



void change(struct Drug *head)//修改信息
{
 struct Drug *p;
 char mNAME[20];
 int x;
 double y;
 printf("药品信息修改\n");
 printf("请输入要修改的药品名:");
 scanf("%s",&mNAME);
 p=head;
 while(p!=NULL)
 { 
	 if(!strcmp(p->Mname,mNAME))
      break;
	p=p->next;
 }
 if(p==NULL)
 { 
	 printf("该药品不在药品库中！\n");
	 printf("按任意键继续");
     getch();
     return;
 }
 	while(1)
	{
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~************************输入修改药品信息********************~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               1 《修改药名》：                                              *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               2 《修改厂家》：                                              *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 《修改类型》：                                              *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               4 《调整价格》：                                              *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               5 《药品进出库》：                                            *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               6 《返回上一层》：                                            *\n");
    printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~6）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
      case 1:printf("原名为：%s\n",p->Mname);printf("请输入修改后的药名：");scanf("%s",p->Mname);break;
      case 2:printf("原厂家为：%s\n",p->manufacturers);printf("请输入修改后的厂家：");scanf("%s",p->manufacturers);break;
      case 3:printf("原类型为：%s\n",p->Mtype);printf("请输入修改后的类型：");scanf("%s",p->Mtype);break;
      case 4:printf("原价格为：%.2lf\n",p->Mprice);printf("请输入调整后的价格：");scanf("%lf",&p->Mprice);break;
      case 5:printf("库存为：%.0lf\n",p->Mstock);printf("请输入进出库数量（正数代表入库，负数代表出库）：");scanf("%lf",&y);p->Mstock+=y;break;
      case 6:break;
      default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
    if(x==6)
	  break;
	}
 save(head);
printf("药品信息修改已完成\n");
printf("按任意键继续");
getch();
}
 


void find1(struct Drug *head)//按药品名称查询信息
{   
struct Drug *p;
char a[20];
 p=head;
 printf("请输入要查找的药品名:");
 scanf("%s",a);
 system("cls");
 printf("*药品名称*          *药品厂家*                    *药品类别*          *药品的价格*        *库存*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->Mname,a))
  printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
  p=p->next;
 }
 if(p==NULL)
printf("没有找到该药品信息\n");
printf("药品信息查找已完成\n");
printf("按任意键继续");
getch();
}



void find2(struct Drug *head)//按厂家名称查询信息
{   
struct Drug *p;
char a[20];
 p=head;
 printf("请输入要查找的厂家名:");
 scanf("%s",a);
 system("cls");
 printf("*药品名称*          *药品厂家*                    *药品类别*          *药品的价格*        *库存*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->manufacturers,a))
	printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
 p=p->next;
 }
 if(p==NULL)
printf("没有找到该厂家信息\n");
printf("药品信息查找已完成\n");
printf("按任意键继续");
getch();
}



void find3(struct Drug *head)//按类型查询信息
{   
struct Drug *p;
char a[20];
 p=head;
 printf("请输入要查找的类型:");
 scanf("%s",a);
 system("cls");
 printf("*药品名称*          *药品厂家*                    *药品类别*          *药品的价格*        *库存*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->Mtype,a))
	printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
 p=p->next;
 }
 if(p==NULL)
printf("没有找到该类型药品信息\n");
printf("药品信息查找已完成\n");
printf("按任意键继续");
getch();
} 



void find(struct Drug *head)//查询
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************输入查询药品信息********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 《根据药品名称查询》：                                      *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 《根据药品出厂地查询》：                                    *\n");
    printf("*                                                                                                             *\n");
	printf("*                                               3 《根据药品类型查询》：                                      *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               4 《返回上一层》：                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~4）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:find1(head);break;
	case 2:find2(head);break;
	case 3:find3(head);break;
	case 4:break;
    default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
    if(x==4)
	  break;
	}
        printf("按任意键继续");
        getch();
}



void statistic1(struct Drug *head)//按厂家名称统计信息
{   
struct Drug *p;
char a[20];
int k=0;
double c=0;
 p=head;
 printf("请输入要查找的厂家名:");
 scanf("%s",a);
 while(p!=NULL)
 {
  if(!strcmp(p->manufacturers,a))
    k++;
	c+=p->Mstock;
    p=p->next; 
 }
 printf("属该厂家药品共：%d种，库存共：%.0lf\n",k,c);
 printf("药品信息查找已完成\n");
 printf("按任意键继续");
 getch();
}



void statistic2(struct Drug *head)//按药品名称统计信息
{   
struct Drug *p;
char a[20];
int k=0;
double c=0;
 p=head;
 printf("请输入要查找的药品名称:");
 scanf("%s",a);
 while(p!=NULL)
 {
  if(!strcmp(p->Mname,a))
    k++;
	c+=p->Mstock;
    p=p->next; 
 }
 printf("生产该药品的厂家共：%d家，库存共：%.0lf\n",k,c);
 printf("药品信息查找已完成\n");
 printf("按任意键继续");
 getch();
}



void statistic(struct Drug *head)//统计
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************输入统计药品信息********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 《统计厂家药品信息》：                                      *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 《统计药品库存量》：                                        *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 《返回上一层》：                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~3）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:statistic1(head);break;
	case 2:statistic2(head);break;
	case 3:break;
    default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
    if(x==3)
	  break;
	}
        printf("按任意键继续");
        getch();
}



void sort1(struct Drug *head)//药名升序
{
    struct Drug *p1,*p2;
	double temp;
	char t[30];
	for(p1=head;p1!=NULL;p1=p1->next) 
		for(p2=p1->next;p2!=NULL;p2=p2->next)
			  if(strcmp(p1->Mname,p2->Mname)<0)
			{
             strcpy(t,p1->Mname);
	         strcpy(p1->Mname,p2->Mname);
	         strcpy(p2->Mname,t);
			 strcpy(t,p1->manufacturers);
	         strcpy(p1->manufacturers,p2->manufacturers);
	         strcpy(p2->manufacturers,t);
			 strcpy(t,p1->Mtype);
	         strcpy(p1->Mtype,p2->Mtype);
	         strcpy(p2->Mtype,t);
	         temp=p1->Mprice, p1->Mprice=p2->Mprice, p2->Mprice=temp;
             temp=p1->Mstock, p1->Mstock=p2->Mstock, p2->Mstock=temp;
			}
			save(head);
printf("药品名称排序已完成\n");
printf("按任意键继续");
getch();
}



void sort2(struct Drug *head)//药名降序
{
    struct Drug *p1,*p2;
	double temp;
	char t[30];
	for(p1=head;p1!=NULL;p1=p1->next) 
		for(p2=p1->next;p2!=NULL;p2=p2->next)
			  if(strcmp(p1->Mname,p2->Mname)>0)
			{
             strcpy(t,p1->Mname);
	         strcpy(p1->Mname,p2->Mname);
	         strcpy(p2->Mname,t);
			 strcpy(t,p1->manufacturers);
	         strcpy(p1->manufacturers,p2->manufacturers);
	         strcpy(p2->manufacturers,t);
			 strcpy(t,p1->Mtype);
	         strcpy(p1->Mtype,p2->Mtype);
	         strcpy(p2->Mtype,t);
	         temp=p1->Mprice, p1->Mprice=p2->Mprice, p2->Mprice=temp;
             temp=p1->Mstock, p1->Mstock=p2->Mstock, p2->Mstock=temp;
			}
			save(head);
printf("药品名称排序已完成\n");
printf("按任意键继续");
getch();
}



void sort3(struct Drug *head)//价格升序
{
    struct Drug *p1,*p2;
	double temp;
	char t[30];
	for(p1=head;p1!=NULL;p1=p1->next) 
		for(p2=p1->next;p2!=NULL;p2=p2->next)
			  if(p1->Mprice>p2->Mprice)
			{
             strcpy(t,p1->Mname);
	         strcpy(p1->Mname,p2->Mname);
	         strcpy(p2->Mname,t);
			 strcpy(t,p1->manufacturers);
	         strcpy(p1->manufacturers,p2->manufacturers);
	         strcpy(p2->manufacturers,t);
			 strcpy(t,p1->Mtype);
	         strcpy(p1->Mtype,p2->Mtype);
	         strcpy(p2->Mtype,t);
	         temp=p1->Mprice, p1->Mprice=p2->Mprice, p2->Mprice=temp;
             temp=p1->Mstock, p1->Mstock=p2->Mstock, p2->Mstock=temp;
			}
			save(head);
printf("药品价格排序已完成\n");
printf("按任意键继续");
getch();
}



void sort4(struct Drug *head)//价格降序
{
    struct Drug *p1,*p2;
	double temp;
	char t[30];
	for(p1=head;p1!=NULL;p1=p1->next) 
		for(p2=p1->next;p2!=NULL;p2=p2->next)
			  if(p1->Mprice>p2->Mprice)
			{
             strcpy(t,p1->Mname);
	         strcpy(p1->Mname,p2->Mname);
	         strcpy(p2->Mname,t);
			 strcpy(t,p1->manufacturers);
	         strcpy(p1->manufacturers,p2->manufacturers);
	         strcpy(p2->manufacturers,t);
			 strcpy(t,p1->Mtype);
	         strcpy(p1->Mtype,p2->Mtype);
	         strcpy(p2->Mtype,t);
	         temp=p1->Mprice, p1->Mprice=p2->Mprice, p2->Mprice=temp;
             temp=p1->Mstock, p1->Mstock=p2->Mstock, p2->Mstock=temp;
			}
			save(head);
printf("药品价格排序已完成\n");
printf("按任意键继续");
getch();
}



void sort(struct Drug *head)//排序
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************选择排序依据信息********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 《根据药名升序》：                                          *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 《根据药名降序》：                                          *\n");
    printf("*                                                                                                             *\n");
	printf("*                                               3 《根据价格升序》：                                          *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               4 《根据价格降序》：                                          *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               5 《返回上一层》：                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~5）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:sort1(head);break;
	case 2:sort2(head);break;
	case 3:sort3(head);break;
	case 4:sort4(head);break;
	case 5:break;
    default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
    if(x==5)
	  break;
	}
        printf("按任意键继续");
        getch();
}



void format1()//格式化数据
{
	int flag;
	FILE *fp;
	char filename[]="drug.txt";
	flag=remove(filename);
	if(flag==0)
		printf("格式化成功！");
	else
		printf("格式化失败！");
	 printf("按任意键继续");
        getch();
}



void format2()//格式化账户
{
	int flag;
	char filename[]="zh.txt";
	FILE *fp;
	flag=remove(filename);
	if(flag==0)
		printf("格式化成功！");
	else
		printf("格式化失败！");
	 printf("按任意键继续");
        getch();
}



void format()
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************输入统计药品信息********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 《格式化数据》：                                            *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 《格式化账户》：                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 《返回上一层》：                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("请选择要进行的操作（1~3）：");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:format1();break;
	case 2:format2();break;
	case 3:break;
    default:printf("所输数字对应功能不存在，请重新输入。\n");
	}
    if(x==3)
	  break;
	}
        printf("按任意键继续");
        getch();
}



void main()
{
struct Drug *head;
FILE *fp;
int x;
start();
if((fp=fopen("drug.txt","rb"))!=NULL)
{
head=again();
fclose(fp);
}
while(1)
{
system("cls");
 	printf("                                     ****************药品管理系统*****************                                 \n");
    printf("\n\n");
	printf("*********************************************************菜单**********************************************************\n");
    printf("*                                                                                                                     *\n");
	printf("*   *    0    <初始化>           \t");
	printf("                                              1    <显示>                 *   *\n");
	printf("*   *    2    <插入>             \t");
	printf("                                              3    <删除>                 *   *\n");
	printf("*   *    4    <修改>             \t");
	printf("                                              5    <查询>                 *   *\n");
	printf("*   *    6    <统计>             \t");
	printf("                                              7    <排序>                 *   *\n");
	printf("*   *    8    <格式化>           \t");
    printf("                                              9    <退出>                 *   *\n");
    printf("*                                                                                                                     *\n");
	printf("***********************************************************************************************************************");
	printf("\n");
	printf("请输入要进行的操作(0~9)：");
  scanf("%d",&x);
  system("cls");
  switch(x)
  {
      case 0:head=creat();save(head);break;
      case 1:display(head);break;
      case 2:add(head);break;
      case 3:dele(head);break;
      case 4:change(head);break;
      case 5:find(head);break;
      case 6:statistic(head);break;
	  case 7:sort(head);break;
      case 8:format();break;
	  case 9:printf("祝您生活愉快，欢迎再次使用！\n");break;
      default:printf("所输数字对应功能不存在，请重新输入。\n");
  }
  if(x==9)
	  break;
 }
}
