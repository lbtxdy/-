#include <conio.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<string.h> 
#define MAXSIZE   20

int M[10];                  // 用来存储每一块的中元素的最大值

int m;						//记录索引划分块数
int r[10][10] ;             //建立的索引表
int blockNum;				//记录每块元素个数

typedef struct              /*定义结构体数组*/ 
{ 
    int num;                /*书号*/
	char name_1[20];        /*书名*/
    char name_2[20];        /*著作者*/ 
    int xc;                 /*现存量*/
	int kc;                 /*库存量*/ 
	int lag;
}bookrary; 
bookrary book[80];          /*结构体数组变量*/
 
typedef struct car          /*借阅者信息结构体数组*/     
{ 
	int xuehao;             //借阅者学号
	char data[10];          //借阅日期
	char name[20];          //所借书的书名
}car; 
car p[20];                  //存书数组
int q=0;	        	    //所借书的数量


int menu_select()           /*菜单函数*/ 
{ 
    int  c; 
    system("cls"); 
    printf("\t      ◢━━━━━━━━━━━◣\n");
    printf("\t      ┃ 欢迎进入图书查询系统 ┃\n");
    printf("\t      ◥━━━━━━━━━━━◤\n\n");
    printf("\t************图书管理系统************\n\n"); 
    printf("\t请选择:\n"); 
    printf("\t    1. 输入信息                     \n"); 
    printf("\t    2. 显示所有信息                 \n"); 
    printf("\t    3. 采购新书                     \n"); 
    printf("\t    4. 借阅                         \n"); 
    printf("\t    5. 归还                         \n");
	printf("\t    6. 建立索引表                   \n");
	printf("\t    7. 保存                         \n");
	printf("\t    8. 从内存中读取                 \n");
    printf("\t    0. Quit                         \n\n"); 
    printf("\t************************************\n\n"); 
    scanf("%d",&c); 
    return(c);  
} 

int Great(bookrary book[],int n) /*输入若干条记录*/ 
{
	int i=0; 
    char sign;  
    while(sign!='n'&&sign!='N')
	{ 
         printf("\t书号:");  
         scanf("\t%d",&book[n+i].num); 
         printf("\t书名:"); 
         scanf("\t%s",&book[n+i].name_1); 
		 printf("\t著作者:"); 
         scanf("\t%s",&book[n+i].name_2); 
         printf("\t现存量:"); 
         scanf("\t%d",&book[n+i].xc);
		 printf("\t库存量:"); 
         scanf("\t%d",&book[n+i].kc);
         printf("\t还需要继续输入吗?(Y/N)"); 
         scanf("\t%c",&sign); /*输入判断*/ 
		 book[i].lag=0;
         i++; 
	} 
    return(n+i); 
} 

int search(int booknum) //查找书号所在图书馆中的下标函数
{
	int i,j;
	for(i=0;i<m;i++)
		if(booknum<=M[i])
			break;
	if(i==m) 
		return -1;		 //未找到

	for(j=0;j<blockNum;j++)
		if(booknum==r[i][j])
			break;
	
	if(j==blockNum) 	//未找到
		return -1;
	else
		return i*blockNum+j;	
}

void Display(bookrary book[],int n) /*显示所有记录*/ 
{ 
    int i; 
    printf("\t-----------------------------------\n"); 
    printf("\t书号\t书名\t著作者\t现存量\t库存量\n"); 
    printf("\t-----------------------------------\n"); 
    for(i=0;i<n;i++)   
        printf("\t %d\t%s\t %s\t %d\t %d\n",book[i].num,book[i].name_1,book[i].name_2,book[i].xc,book[i].kc);         
    printf("\t"); 
}

int Insert(bookrary book[],int n,int m)/*采购新书的书号*/
{
	int i=0;
	for(i=0;i<n;i++)
	{
		if(book[i].num==m)
			break;
	}
	if(i==n)
	{
		printf("图书馆没有此书\n");
     	book[i].num=m;
		printf("\t书名:"); 
        scanf("\t%s",&book[i].name_1); 
		printf("\t著作者:"); 
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
void lend(bookrary book[],int i)//借书的书号
{
	char b[10];
	int a;
	if(book[i].xc!=0 && book[i].lag==1)
	{
		book[i].lag=0;
		book[i].xc--;
		printf("请输入借阅者的学号\n");
		scanf("%d",&a);
		getchar();
		printf("输入借阅时间\n");
		scanf("%s",b);
		getchar();
		strcpy(p[q].data,b);
	    strcpy(p[q].name,book[i].name_1);
        p[q].xuehao=a;
		q++;
	}
	else
		printf("没有找到!");
}

int bank(bookrary book[],char bookname[],int n)//归还书的书名bookname[]
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
		printf("没有找到!\n"); 
        return 0;
    }
	for(j=0;j<n;j++)
	{
		if(strcmp(book[j].name_1,bookname)==0)
			break;
	}
    for(i=b-1;i<q;i++)/*删除还书记录*/
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

void Sort_num(bookrary book[],int n) /*按shu号排序*/ 
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
		 printf("\t排序后的序列为\n");
         Display(book,n);
}

void suoyin(bookrary book[],int n)
{
	int i,j;
	Sort_num(book, n);
    printf("输入分块的个数\n");
    scanf("%d",&m);  
	blockNum =n%m ==0 ? n/m : n/m+1;
	int h=0;		//记录当前元素下标
	for(i=0 ;i<m;i++)
	{
		for(j=0;j<blockNum && h<n;j++ )
		{
			r[i][j]=book[h].num;              
			h++;
		}
	}
	//将每一组的最大元素存入数组M中
    for( i=0;i<m;i++) 
	{
         for(j=0;j<blockNum;j++) 
		 {
             if(r[i][j]>= M[i])
                  M[i]=r[i][j];
		 }
	}
 
    printf("每个块最大元素为\n");
    for(i=0;i<m;i++)
        printf("%d  ",M[i]); 
}
				   

void Save(bookrary book[],int n)
{
	FILE *fp;
    if((fp=fopen("图书馆.txt","w"))==NULL)
    {
        printf("打开文件失败!\n\n");
        return;  
	}
	fwrite(book,sizeof(bookrary ),n,fp);
	printf("保存成功\n");
	fclose(fp);	 
}

 
int Load(bookrary book[])
{
    int i=0;
	FILE *fp;
	if((fp=fopen("图书馆.txt","rt"))==NULL)
	{
		printf("打开文件失败!\n\n");
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
int main() /*主函数*/ 
{ 
	 int bookno;
     int n=0;
	 int k;
	 char c[20];
     for(;;) 
	 { 
         switch(menu_select()) /*选择判断*/ 
		 { 
             case 1: 
                 system("cls");
                 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃      增加记录        ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
                 n=Great(book,n);		 
                 break; 

             case 2: 
                 system("cls");
                 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃    图书馆状况一览    ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
                 Display(book,n); 
                 break; 

             case 3:
             	 system("cls");
             	 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃       采购新书       ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
				 printf("输入采购新书的书号\n");
                 scanf("%d",&m);
                 n=Insert(book,n,m);			
					break;
				 
             case 4: 
				  system("cls");
				  printf("\t      ◢━━━━━━━━━━━◣\n");
                  printf("\t      ┃         查询         ┃\n");
                  printf("\t      ◥━━━━━━━━━━━◤\n\n");
				  printf("查找书籍的书号\n");
				  scanf("%d",&bookno); 
				  k = search(bookno);
				  if( n != -1)
				     printf("\t%d\t%s\t%s\t%d\t%d\n",book[k].num,book[k].name_1,book[k].name_2,book[k].xc,book[k].kc); 
				 book[k].lag = 1;
                 lend(book,k);
                 break;	
			 case 5: 
			     system("cls");
			     printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃         还书         ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
				 printf("输入还书的书名\n");
				 scanf("%s",c);
				 bank(book,c,n);
				 break;	
			 case 6:
			   	 system("cls");
			   	 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃      建立索引表      ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
				 suoyin(book,n);		
				 break;
			 case 7:
			 	 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃         保存         ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
			 	 system("cls");
				 Save(book,n);
				 break;
			 case 8:
			 	 printf("\t      ◢━━━━━━━━━━━◣\n");
                 printf("\t      ┃         读取         ┃\n");
                 printf("\t      ◥━━━━━━━━━━━◤\n\n");
			 	 system("cls");
				 n = Load(book);
				 break;
             case 0: 
                 printf("\t欢迎使用!!\n再见！\n"); /*结束程序*/ 
                 printf("\n"); 
                 system("pause"); 
                 exit(0); 
		 } 
		 system("pause"); 
	 } 
}

