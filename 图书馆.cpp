#include <conio.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<string.h> 
#define MAXSIZE   20

int M[10];                  // �����洢ÿһ�����Ԫ�ص����ֵ

int m;						//��¼�������ֿ���
int r[10][10] ;             //������������
int blockNum;				//��¼ÿ��Ԫ�ظ���

typedef struct              /*����ṹ������*/ 
{ 
    int num;                /*���*/
	char name_1[20];        /*����*/
    char name_2[20];        /*������*/ 
    int xc;                 /*�ִ���*/
	int kc;                 /*�����*/ 
	int lag;
}bookrary; 
bookrary book[80];          /*�ṹ���������*/
 
typedef struct car          /*��������Ϣ�ṹ������*/     
{ 
	int xuehao;             //������ѧ��
	char data[10];          //��������
	char name[20];          //�����������
}car; 
car p[20];                  //��������
int q=0;	        	    //�����������


int menu_select()           /*�˵�����*/ 
{ 
    int  c; 
    system("cls"); 
    printf("\t      ��������������������������\n");
    printf("\t      �� ��ӭ����ͼ���ѯϵͳ ��\n");
    printf("\t      ��������������������������\n\n");
    printf("\t************ͼ�����ϵͳ************\n\n"); 
    printf("\t��ѡ��:\n"); 
    printf("\t    1. ������Ϣ                     \n"); 
    printf("\t    2. ��ʾ������Ϣ                 \n"); 
    printf("\t    3. �ɹ�����                     \n"); 
    printf("\t    4. ����                         \n"); 
    printf("\t    5. �黹                         \n");
	printf("\t    6. ����������                   \n");
	printf("\t    7. ����                         \n");
	printf("\t    8. ���ڴ��ж�ȡ                 \n");
    printf("\t    0. Quit                         \n\n"); 
    printf("\t************************************\n\n"); 
    scanf("%d",&c); 
    return(c);  
} 

int Great(bookrary book[],int n) /*������������¼*/ 
{
	int i=0; 
    char sign;  
    while(sign!='n'&&sign!='N')
	{ 
         printf("\t���:");  
         scanf("\t%d",&book[n+i].num); 
         printf("\t����:"); 
         scanf("\t%s",&book[n+i].name_1); 
		 printf("\t������:"); 
         scanf("\t%s",&book[n+i].name_2); 
         printf("\t�ִ���:"); 
         scanf("\t%d",&book[n+i].xc);
		 printf("\t�����:"); 
         scanf("\t%d",&book[n+i].kc);
         printf("\t����Ҫ����������?(Y/N)"); 
         scanf("\t%c",&sign); /*�����ж�*/ 
		 book[i].lag=0;
         i++; 
	} 
    return(n+i); 
} 

int search(int booknum) //�����������ͼ����е��±꺯��
{
	int i,j;
	for(i=0;i<m;i++)
		if(booknum<=M[i])
			break;
	if(i==m) 
		return -1;		 //δ�ҵ�

	for(j=0;j<blockNum;j++)
		if(booknum==r[i][j])
			break;
	
	if(j==blockNum) 	//δ�ҵ�
		return -1;
	else
		return i*blockNum+j;	
}

void Display(bookrary book[],int n) /*��ʾ���м�¼*/ 
{ 
    int i; 
    printf("\t-----------------------------------\n"); 
    printf("\t���\t����\t������\t�ִ���\t�����\n"); 
    printf("\t-----------------------------------\n"); 
    for(i=0;i<n;i++)   
        printf("\t %d\t%s\t %s\t %d\t %d\n",book[i].num,book[i].name_1,book[i].name_2,book[i].xc,book[i].kc);         
    printf("\t"); 
}

int Insert(bookrary book[],int n,int m)/*�ɹ���������*/
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(book[i].num==m)
			break;
	}
	if(i==n)
	{
		printf("ͼ���û�д���\n");
     	book[i].num=m;
		printf("\t����:"); 
        scanf("\t%s",&book[i].name_1); 
		printf("\t������:"); 
        scanf("\t%s",&book[i].name_2);
		book[i].xc++;
        book[i].kc++;
		n++;
	}
	else
	{
		book[i].kc++;
		book[i].lag=1;
	}
	Display(book,n);
	return n;
}
void lend(bookrary book[],int i)//��������
{
	char b[10];
	int a;
	if(book[i].xc!=0 && book[i].lag==1)
	{
		book[i].lag=0;
		book[i].xc--;
		printf("����������ߵ�ѧ��\n");
		scanf("%d",&a);
		getchar();
		printf("�������ʱ��\n");
		scanf("%s",b);
		getchar();
		strcpy(p[q].data,b);
	    strcpy(p[q].name,book[i].name_1);
        p[q].xuehao=a;
		q++;
	}
	else
		printf("û���ҵ�!");
}

int bank(bookrary book[],char bookname[],int n)//�黹�������bookname[]
{
	int b=0;
	int i,j;
	for(b=0;b<q;b++)
	{
		if(strcmp(p[b].name,bookname)==0)
			break;
	}
    if(b==q) 
    { 
		printf("û���ҵ�!\n"); 
        return 0;
    }
	for(j=0;j<n;j++)
	{
		if(strcmp(book[j].name_1,bookname)==0)
			break;
	}
    for(i=b-1;i<q;i++)/*ɾ�������¼*/
	{
       p[i].xuehao=p[i+1].xuehao;
	   strcpy(p[i].name,p[i+1].name);
	   strcpy(p[i].data,p[i+1].data);
	}
     book[j].xc++;
	 book[j].lag=1;
     Display(book,n);
	 return 1;
}

void Sort_num(bookrary book[],int n) /*��shu������*/ 
{ 
	int i,j,*p,*q,s; 
    char t[10]; 
    for(i=0;i<n-1;i++)  
      for(j=0;j<n-1-i;j++)		
         if(book[j].num>book[j+1].num) 
		 {
			 p=&book[j+1].num; 
             q=&book[j].num; 
             s=*p; 
             *p=*q; 
             *q=s; 
             strcpy(t,book[j+1].name_1); 
             strcpy(book[j+1].name_1,book[j].name_1); 
             strcpy(book[j].name_1,t);
			 strcpy(t,book[j+1].name_2); 
             strcpy(book[j+1].name_2,book[j].name_2); 
             strcpy(book[j].name_2,t);
             p=&book[j+1].kc; 
             q=&book[j].kc; 
             s=*p; 
             *p=*q; 
             *q=s; 
			 p=&book[j+1].xc; 
             q=&book[j].xc; 
             s=*p; 
             *p=*q; 
             *q=s; 
		 } 
		 printf("\t����������Ϊ\n");
         Display(book,n);
}

void suoyin(bookrary book[],int n)
{
	int i,j;
	Sort_num(book, n);
    printf("����ֿ�ĸ���\n");
    scanf("%d",&m);  
	blockNum =n%m ==0 ? n/m : n/m+1;
	int h=0;		//��¼��ǰԪ���±�
	for(i=0 ;i<m;i++)
	{
		for(j=0;j<blockNum && h<n;j++ )
		{
			r[i][j]=book[h].num;              
			h++;
		}
	}
	//��ÿһ������Ԫ�ش�������M��
    for( i=0;i<m;i++) 
	{
         for(j=0;j<blockNum;j++) 
		 {
             if(r[i][j]>= M[i])
                  M[i]=r[i][j];
		 }
	}
 
    printf("ÿ�������Ԫ��Ϊ\n");
    for(i=0;i<m;i++)
        printf("%d  ",M[i]); 
}
				   

void Save(bookrary book[],int n)
{
	FILE *fp;
    if((fp=fopen("ͼ���.txt","w"))==NULL)
    {
        printf("���ļ�ʧ��!\n\n");
        return;  
	}
	fwrite(book,sizeof(bookrary ),n,fp);
	printf("����ɹ�\n");
	fclose(fp);	 
}

 
int Load(bookrary book[])
{
    int i=0;
	FILE *fp;
	if((fp=fopen("ͼ���.txt","rt"))==NULL)
	{
		printf("���ļ�ʧ��!\n\n");
		return 0;
	}

	while(!feof(fp))
	{			
		fread(&book[i],sizeof(bookrary),1,fp);
			if(!feof(fp))	  
				i++;	   	  
	}

	fclose(fp);	
	return i;
}
int main() /*������*/ 
{ 
	 int bookno;
     int n=0;
	 int k;
	 char c[20];
     for(;;) 
	 { 
         switch(menu_select()) /*ѡ���ж�*/ 
		 { 
             case 1: 
                 system("cls");
                 printf("\t      ��������������������������\n");
                 printf("\t      ��      ���Ӽ�¼        ��\n");
                 printf("\t      ��������������������������\n\n");
                 n=Great(book,n);		 
                 break; 

             case 2: 
                 system("cls");
                 printf("\t      ��������������������������\n");
                 printf("\t      ��    ͼ���״��һ��    ��\n");
                 printf("\t      ��������������������������\n\n");
                 Display(book,n); 
                 break; 

             case 3:
             	 system("cls");
             	 printf("\t      ��������������������������\n");
                 printf("\t      ��       �ɹ�����       ��\n");
                 printf("\t      ��������������������������\n\n");
				 printf("����ɹ���������\n");
                 scanf("%d",&m);
                 n=Insert(book,n,m);			
					break;
				 
             case 4: 
				  system("cls");
				  printf("\t      ��������������������������\n");
                  printf("\t      ��         ��ѯ         ��\n");
                  printf("\t      ��������������������������\n\n");
				  printf("�����鼮�����\n");
				  scanf("%d",&bookno); 
				  k = search(bookno);
				  if( n != -1)
				     printf("\t%d\t%s\t%s\t%d\t%d\n",book[k].num,book[k].name_1,book[k].name_2,book[k].xc,book[k].kc); 
				 book[k].lag = 1;
                 lend(book,k);
                 break;	
			 case 5: 
			     system("cls");
			     printf("\t      ��������������������������\n");
                 printf("\t      ��         ����         ��\n");
                 printf("\t      ��������������������������\n\n");
				 printf("���뻹�������\n");
				 scanf("%s",c);
				 bank(book,c,n);
				 break;	
			 case 6:
			   	 system("cls");
			   	 printf("\t      ��������������������������\n");
                 printf("\t      ��      ����������      ��\n");
                 printf("\t      ��������������������������\n\n");
				 suoyin(book,n);		
				 break;
			 case 7:
			 	 printf("\t      ��������������������������\n");
                 printf("\t      ��         ����         ��\n");
                 printf("\t      ��������������������������\n\n");
			 	 system("cls");
				 Save(book,n);
				 break;
			 case 8:
			 	 printf("\t      ��������������������������\n");
                 printf("\t      ��         ��ȡ         ��\n");
                 printf("\t      ��������������������������\n\n");
			 	 system("cls");
				 n = Load(book);
				 break;
             case 0: 
                 printf("\t��ӭʹ��!!\n�ټ���\n"); /*��������*/ 
                 printf("\n"); 
                 system("pause"); 
                 exit(0); 
		 } 
		 system("pause"); 
	 } 
}

