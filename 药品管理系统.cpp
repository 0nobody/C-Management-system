#include<stdio.h>
#include<stdlib.h>//exit()��malloc()
#include<conio.h>//gtetch()���ú������Բ����Ժ���ֵ
#include<windows.h>//����
#include<string.h>
#define LEN sizeof(struct Drug)
struct Drug
{	
 char Mname[20];//����
 char manufacturers[30];//����
 char Mtype[10];//���
 double Mprice;//�۸�
 double Mstock;//���
 struct Drug*next;//ָ�����
};



void regist()//ע��
{
   void login();
   FILE *fp;//ָ���ļ���ָ�����
   int la,lb;
   char a[20],b[20],c[20];
   if((fp=fopen("zh.txt","r"))!=NULL)
   {
	   printf("��Ǹ��ϵͳֻ��ע��һ������Ա�˻�����Ҫ����ע�����½���ʽ����\n");
       printf("���������¼");
	   fclose(fp);
       getch();
	   login();
   }

   system("cls");
   while(1)
   {
    printf("������ע���˺ţ����ó���10λ����");
    scanf("%s",a);
    la=strlen(a);
    if(la>10)
	   printf("�����˺Ź��������������롣");
    else 
    break;
   }
   while(1)
   {
    printf("������ע�����루���ó���10λ����");
    scanf("%s",b);
	lb=strlen(b);
    if(lb>10)
	   printf("����������������������롣");
    else 
    break;
   }
   while(1)
   {
    printf("���ٴ�����ע�����룺");
    scanf("%s",c);
    if(strcmp(b,c))
	   printf("�������벻ͬ�����������롣\n");
    else 
    break;
   }
   fp=fopen("zh.txt", "w");
   fprintf(fp,"%s %s",a,b);
   fclose(fp);
   printf("ע��ɹ���\n");
   printf("����������ص�¼����");
   getch();
}



void login()//��¼
{
	FILE *fp;
	char a[20],b[20],d[20],e[20];
	if((fp=fopen("zh.txt","r"))==NULL)
    {
	printf("��Ǹ��ϵͳδע�����Ա�˻�������ע�ᡣ\n");
    printf("�������ע��");
    getch();
	regist();
	}
	fclose(fp);
	system("cls");
    printf("�������¼�˺ţ�");
    scanf("%s",d);
	printf("�������¼���룺");
    scanf("%s",e);
	fp=fopen("zh.txt","r");
	fscanf(fp,"%s %s",&a,&b);
	fclose(fp);
	if(!strcmp(a,d)&&!strcmp(b,e))
	{
		printf("��¼�ɹ���");
		printf("�����������ϵͳ");
        getch();
	}
	else
	{
		printf("�˺Ż�������󣬵�½ʧ�ܣ������ԣ�");
		getch();
		login();
	}
}



void start()//��¼����
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************ҩƷ��Ϣ����ϵͳ********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 ��ע�ᡷ��                                                  *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 ����¼����                                                  *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 ���˳�����                                                  *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~3����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:regist();break;
	case 2:login();break;
    case 3:exit(0);
    default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
	if(x==2)
		break;
	}
}



struct Drug *creat()//��ʼ����Ϣ
{
	struct Drug *head,*p1,*p2;
    int flag=0;
	char a[]="over";
	printf("������ҩƷ����Ϣ(ҩ��Ϊoverʱ����):\n");
	p1=p2=(struct Drug*)malloc(LEN);
	memset(p1,0,LEN);//��ʼ���ṹ��
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
	printf("ҩƷ��Ϣ���������\n");
    printf("�������������");
    getch();
	return(head);
}



void save(struct Drug *head)//�����ڱ���
{  
	FILE *fp;
    struct Drug *p;
	if((fp=fopen("drug.txt","wb"))==NULL)
	{
		printf("���ļ�ʧ�� ��\n");
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



void display(struct Drug *head)//��ʾ��Ϣ
{
	FILE *fp;
	struct Drug *p;
    printf("*ҩƷ����*          *ҩƷ����*                    *ҩƷ���*          *ҩƷ�ļ۸�*        *���*\n");
    if((fp=fopen("drug.txt","rb"))==NULL)
	{
	 printf("���ļ�ʧ�ܣ�\n");
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
    printf("ҩƷ��Ϣ��ʾ�����\n");
    printf("�������������");
    getch();
}



struct Drug *again()//������Ϣ
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



void add(struct Drug *head)//�����Ϣ
{
 FILE *fp;
 struct Drug*p1,*p2=NULL,*p3;
 if((fp=fopen("drug.txt","ab+"))==NULL)
 {
	 printf("���ļ�ʧ�ܣ�\n");
	 exit(0);
 }
 printf("ҩƷ��Ϣ���\n");
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
printf("ҩƷ��Ϣ��������\n");
printf("�����������");
getch();
}



void dele(struct Drug *head)//ɾ����Ϣ
{
 struct Drug *p1,*p2;
 char a[20];
 printf("ҩƷ��Ϣɾ��\n");
 printf("������Ҫɾ����ҩƷ��:");
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
	 printf("��ҩƷ����ҩƷ���У�\n");
save(head);
printf("ҩƷ��Ϣɾ�������\n");
printf("�����������");
getch();
}



void change(struct Drug *head)//�޸���Ϣ
{
 struct Drug *p;
 char mNAME[20];
 int x;
 double y;
 printf("ҩƷ��Ϣ�޸�\n");
 printf("������Ҫ�޸ĵ�ҩƷ��:");
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
	 printf("��ҩƷ����ҩƷ���У�\n");
	 printf("�����������");
     getch();
     return;
 }
 	while(1)
	{
    system("cls");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~************************�����޸�ҩƷ��Ϣ********************~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               1 ���޸�ҩ������                                              *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               2 ���޸ĳ��ҡ���                                              *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 ���޸����͡���                                              *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               4 �������۸񡷣�                                              *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               5 ��ҩƷ�����⡷��                                            *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               6 ��������һ�㡷��                                            *\n");
    printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~6����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
      case 1:printf("ԭ��Ϊ��%s\n",p->Mname);printf("�������޸ĺ��ҩ����");scanf("%s",p->Mname);break;
      case 2:printf("ԭ����Ϊ��%s\n",p->manufacturers);printf("�������޸ĺ�ĳ��ң�");scanf("%s",p->manufacturers);break;
      case 3:printf("ԭ����Ϊ��%s\n",p->Mtype);printf("�������޸ĺ�����ͣ�");scanf("%s",p->Mtype);break;
      case 4:printf("ԭ�۸�Ϊ��%.2lf\n",p->Mprice);printf("�����������ļ۸�");scanf("%lf",&p->Mprice);break;
      case 5:printf("���Ϊ��%.0lf\n",p->Mstock);printf("���������������������������⣬����������⣩��");scanf("%lf",&y);p->Mstock+=y;break;
      case 6:break;
      default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
    if(x==6)
	  break;
	}
 save(head);
printf("ҩƷ��Ϣ�޸������\n");
printf("�����������");
getch();
}
 


void find1(struct Drug *head)//��ҩƷ���Ʋ�ѯ��Ϣ
{   
struct Drug *p;
char a[20];
 p=head;
 printf("������Ҫ���ҵ�ҩƷ��:");
 scanf("%s",a);
 system("cls");
 printf("*ҩƷ����*          *ҩƷ����*                    *ҩƷ���*          *ҩƷ�ļ۸�*        *���*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->Mname,a))
  printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
  p=p->next;
 }
 if(p==NULL)
printf("û���ҵ���ҩƷ��Ϣ\n");
printf("ҩƷ��Ϣ���������\n");
printf("�����������");
getch();
}



void find2(struct Drug *head)//���������Ʋ�ѯ��Ϣ
{   
struct Drug *p;
char a[20];
 p=head;
 printf("������Ҫ���ҵĳ�����:");
 scanf("%s",a);
 system("cls");
 printf("*ҩƷ����*          *ҩƷ����*                    *ҩƷ���*          *ҩƷ�ļ۸�*        *���*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->manufacturers,a))
	printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
 p=p->next;
 }
 if(p==NULL)
printf("û���ҵ��ó�����Ϣ\n");
printf("ҩƷ��Ϣ���������\n");
printf("�����������");
getch();
}



void find3(struct Drug *head)//�����Ͳ�ѯ��Ϣ
{   
struct Drug *p;
char a[20];
 p=head;
 printf("������Ҫ���ҵ�����:");
 scanf("%s",a);
 system("cls");
 printf("*ҩƷ����*          *ҩƷ����*                    *ҩƷ���*          *ҩƷ�ļ۸�*        *���*\n");
 while(p!=NULL)
 {
  if(!strcmp(p->Mtype,a))
	printf("%-20s%-30s%-20s%-20.2lf%-20.0lf\n",p->Mname,p->manufacturers,p->Mtype,p->Mprice,p->Mstock);
 p=p->next;
 }
 if(p==NULL)
printf("û���ҵ�������ҩƷ��Ϣ\n");
printf("ҩƷ��Ϣ���������\n");
printf("�����������");
getch();
} 



void find(struct Drug *head)//��ѯ
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************�����ѯҩƷ��Ϣ********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 ������ҩƷ���Ʋ�ѯ����                                      *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 ������ҩƷ�����ز�ѯ����                                    *\n");
    printf("*                                                                                                             *\n");
	printf("*                                               3 ������ҩƷ���Ͳ�ѯ����                                      *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               4 ��������һ�㡷��                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~4����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:find1(head);break;
	case 2:find2(head);break;
	case 3:find3(head);break;
	case 4:break;
    default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
    if(x==4)
	  break;
	}
        printf("�����������");
        getch();
}



void statistic1(struct Drug *head)//����������ͳ����Ϣ
{   
struct Drug *p;
char a[20];
int k=0;
double c=0;
 p=head;
 printf("������Ҫ���ҵĳ�����:");
 scanf("%s",a);
 while(p!=NULL)
 {
  if(!strcmp(p->manufacturers,a))
    k++;
	c+=p->Mstock;
    p=p->next; 
 }
 printf("���ó���ҩƷ����%d�֣���湲��%.0lf\n",k,c);
 printf("ҩƷ��Ϣ���������\n");
 printf("�����������");
 getch();
}



void statistic2(struct Drug *head)//��ҩƷ����ͳ����Ϣ
{   
struct Drug *p;
char a[20];
int k=0;
double c=0;
 p=head;
 printf("������Ҫ���ҵ�ҩƷ����:");
 scanf("%s",a);
 while(p!=NULL)
 {
  if(!strcmp(p->Mname,a))
    k++;
	c+=p->Mstock;
    p=p->next; 
 }
 printf("������ҩƷ�ĳ��ҹ���%d�ң���湲��%.0lf\n",k,c);
 printf("ҩƷ��Ϣ���������\n");
 printf("�����������");
 getch();
}



void statistic(struct Drug *head)//ͳ��
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************����ͳ��ҩƷ��Ϣ********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 ��ͳ�Ƴ���ҩƷ��Ϣ����                                      *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 ��ͳ��ҩƷ���������                                        *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 ��������һ�㡷��                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~3����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:statistic1(head);break;
	case 2:statistic2(head);break;
	case 3:break;
    default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
    if(x==3)
	  break;
	}
        printf("�����������");
        getch();
}



void sort1(struct Drug *head)//ҩ������
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
printf("ҩƷ�������������\n");
printf("�����������");
getch();
}



void sort2(struct Drug *head)//ҩ������
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
printf("ҩƷ�������������\n");
printf("�����������");
getch();
}



void sort3(struct Drug *head)//�۸�����
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
printf("ҩƷ�۸����������\n");
printf("�����������");
getch();
}



void sort4(struct Drug *head)//�۸���
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
printf("ҩƷ�۸����������\n");
printf("�����������");
getch();
}



void sort(struct Drug *head)//����
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************ѡ������������Ϣ********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 ������ҩ�����򡷣�                                          *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 ������ҩ�����򡷣�                                          *\n");
    printf("*                                                                                                             *\n");
	printf("*                                               3 �����ݼ۸����򡷣�                                          *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               4 �����ݼ۸��򡷣�                                          *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               5 ��������һ�㡷��                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~5����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:sort1(head);break;
	case 2:sort2(head);break;
	case 3:sort3(head);break;
	case 4:sort4(head);break;
	case 5:break;
    default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
    if(x==5)
	  break;
	}
        printf("�����������");
        getch();
}



void format1()//��ʽ������
{
	int flag;
	FILE *fp;
	char filename[]="drug.txt";
	flag=remove(filename);
	if(flag==0)
		printf("��ʽ���ɹ���");
	else
		printf("��ʽ��ʧ�ܣ�");
	 printf("�����������");
        getch();
}



void format2()//��ʽ���˻�
{
	int flag;
	char filename[]="zh.txt";
	FILE *fp;
	flag=remove(filename);
	if(flag==0)
		printf("��ʽ���ɹ���");
	else
		printf("��ʽ��ʧ�ܣ�");
	 printf("�����������");
        getch();
}



void format()
{
	int x;
	while(1)
	{
	system("cls");
	printf(" ~~~~~~~~~~~~~~~~~~~~~~~************************����ͳ��ҩƷ��Ϣ********************~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("*                                               1 ����ʽ�����ݡ���                                            *\n");
    printf("*                                                                                                             *\n");
    printf("*                                               2 ����ʽ���˻�����                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                               3 ��������һ�㡷��                                            *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
	printf("*                                                                                                             *\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~*************************************************************~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("��ѡ��Ҫ���еĲ�����1~3����");
	scanf("%d",&x);
	system("cls");
	switch(x)
	{
	case 1:format1();break;
	case 2:format2();break;
	case 3:break;
    default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
	}
    if(x==3)
	  break;
	}
        printf("�����������");
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
 	printf("                                     ****************ҩƷ����ϵͳ*****************                                 \n");
    printf("\n\n");
	printf("*********************************************************�˵�**********************************************************\n");
    printf("*                                                                                                                     *\n");
	printf("*   *    0    <��ʼ��>           \t");
	printf("                                              1    <��ʾ>                 *   *\n");
	printf("*   *    2    <����>             \t");
	printf("                                              3    <ɾ��>                 *   *\n");
	printf("*   *    4    <�޸�>             \t");
	printf("                                              5    <��ѯ>                 *   *\n");
	printf("*   *    6    <ͳ��>             \t");
	printf("                                              7    <����>                 *   *\n");
	printf("*   *    8    <��ʽ��>           \t");
    printf("                                              9    <�˳�>                 *   *\n");
    printf("*                                                                                                                     *\n");
	printf("***********************************************************************************************************************");
	printf("\n");
	printf("������Ҫ���еĲ���(0~9)��");
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
	  case 9:printf("ף��������죬��ӭ�ٴ�ʹ�ã�\n");break;
      default:printf("�������ֶ�Ӧ���ܲ����ڣ����������롣\n");
  }
  if(x==9)
	  break;
 }
}
