#include "stdio.h" 
#include "string.h" 
#include "iostream" 
#include "math.h" 
#include "stdlib.h" 
#include "iomanip" 
using namespace std;
// ******************目录和文件的结构定义****** 
typedef struct node{ 
char name[50]; /*目录或文件的名字*/ 
int type; /*0代表目录，1代表普通文件*/ 
struct node *next; /*指向下一个兄弟结点的指针*/ 
struct node *sub; /*指向第一个子结点的指针*/ 
struct node *father; /*指向父结点的指针*/ 
int size; /*如果是文件则表示文件的大小*/ 
}dirNode; 

dirNode *workDir; //定义当前工作目录 
dirNode root; //定义根目录 

char path[100]; //定义路径信息 

//初始化函数 
void initial() 
{ 
strcpy(root.name,"root"); 
root.type=0; 
root.next=NULL; 
root.sub=NULL; 
root.father=NULL; 
root.size=0; 

workDir=&root; 

strcpy(path,"root"); 
} 

//初始化新结点函数 
dirNode *init() 
{ 
dirNode *p; 

p=new dirNode; 

strcpy(root.name,""); 
root.type=0; 
root.next=NULL; 
root.sub=NULL; 
root.father=NULL; 
root.size=0; 

return p; 
} 

//改变目录 
void CD(char dirName[]) 
{ 
dirNode *p; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"错误,\""<<dirName<<"\"子目录不存在"<<endl; 
} 
else
{ 
	while(p)
	{ 
		if(p->type==0)
		{ 
			if(!strcmp(p->name,dirName))
			{ 
				flag=1; 
				break; 
			} 
		} 
		p=p->next; 
	} 
	if(flag==1)
	{ 
		workDir=p; 
		strcat(path,"\\ "); 
		strcat(path,p->name); 
		cout<<"工作目录已进入\""<<dirName<<"\""<<endl; 
	} 
	else
	{ 
		cout<<"错误,\""<<dirName<<"\"子目录不存在"<<endl; 
	} 
} 
} 

//创建文件 
void CREATE(char fileName[],int fileSize) 
{ 
int flag; 
dirNode *p,*q; 

q=new dirNode; 
strcpy(q->name,fileName); 
q->sub=NULL; 
q->type=1; 
q->next=NULL; 
q->father=workDir; 
q->size=fileSize; 

p=workDir->sub; 

if(p==NULL)
{ 
	workDir->sub=q; 
	cout<<"\""<<fileName<<"\"文件创建成功"<<endl; 
} 
else
{ 
	flag=0; 
	while(p)
	{ 
		if(p->type==1)
		{ 
			if(!strcmp(p->name,fileName))
			{ 
				flag=1; 
				cout<<"错误,\""<<fileName<<"\"文件已存在"<<endl; 
			} 
		} 
		p=p->next; 
	} 
	if(flag==0)
	{ 
		p=workDir->sub; 
		while(p->next)
		{ 
			p=p->next; 
		} 
		p->next=q; 
		cout<<"\""<<fileName<<"\"文件创建成功"<<endl; 
	} 
} 
} 

//删除文件 
void DEL(char fileName[]) 
{ 
dirNode *p,*q; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"错误,\""<<fileName<<"\"文件不存在"<<endl; 
} 
else
{ 
	while(p)
	{ 
		if(p->type==1)
		{ 
			if(!strcmp(p->name,fileName))
			{ 
				flag=1; 
				break; 
			} 
		} 
		p=p->next; 
	} 
	if(flag==1)
	{ 
		if(p==workDir->sub)
		{ 
			workDir->sub=p->next; 
		} 
		else
		{ 
			q=workDir->sub; 
			while(q->next!=p)
			{ 
				q=q->next; 
			} 
			q->next=p->next; 
			delete p; 
		} 
		cout<<"\""<<fileName<<"\"文件已删除"<<endl; 
	} 
	else
	{ 
		cout<<"错误,\""<<fileName<<"\"文件不存在"<<endl; 
	} 
} 
} 

//显示所有目录 

//显示本目录下所有兄弟目录和文件 
void dir(dirNode *p) 
{ 
while(p)
{ 
	if(p->type==0)
	{ 
		cout.setf(ios_base::left); 
		cout<<setw(14)<<p->name<<setw(12)<<"<DIR>"<<endl; 
	} 
	else
	{ 
		cout.setf(ios_base::left); 
		cout<<setw(14)<<p->name<<setw(12)<<"<FILE>"<<setw(10)<<p->size<<endl; 
	} 
	p=p->next; 
} 
} 
// 
void dirs(dirNode *p,char str[]) 
{ 
char newstr[100]; 
dirNode *q; 
cout<<str<<"下子目录及文件:"<<endl; 
dir(p); 

q=p; 
if(q->sub)
{ 
	strcpy(newstr,""); 
	strcat(newstr,str); 
	strcat(newstr,"\\"); 
	strcat(newstr,q->name); 
	dirs(q->sub,newstr); 
} 
q=p; 
while(q->next)
{ 
	if(q->next->sub)
	{ 
		strcpy(newstr,""); 
		strcat(newstr,str); 
		strcat(newstr," \\"); 
		strcat(newstr,q->next->name); 

		dirs(q->next->sub,newstr); 
	} 
	q=q->next; 
} 
} 

//显示所有目录 
void LSALL() 
{ 
dirNode *p; 

cout<<"显示所有目录结构";
cout<<endl<<"--------------------------------------------"<<endl; 

p=root.sub; 
if(p!=NULL)
  dirs(p,"root"); 
else
  cout<<"目录为空"<<endl;

} 
//创建目录 
void MD(char dirName[]) 
{ 
int flag; 
dirNode *p,*q; 

q=new dirNode; 
strcpy(q->name,dirName); 
q->sub=NULL; 
q->type=0; 
q->next=NULL; 
q->father=workDir; 
q->size=0; 

p=workDir->sub; 

if(p==NULL)
{ 
	workDir->sub=q; 
	cout<<"\""<<dirName<<"\"子目录创建成功"<<endl; 
} 
else
{ 
	flag=0; 
	while(p)
	{ 
		if(p->type==0)
		{ 
			if(!strcmp(p->name,dirName))
			{ 
				flag=1; 
				cout<<"错误,\""<<dirName<<"\"子目录已存在"<<endl; 
			} 
		} 
		p=p->next; 
	} 
	if(flag==0)
	{ 
		p=workDir->sub; 
		while(p->next)
		{ 
			p=p->next; 
		} 
	p->next=q; 
	cout<<"\""<<dirName<<"\"子目录创建成功"<<endl; 
	} 
} 
} 

//删除目录 
void RD(char dirName[]) 
{ 
dirNode *p,*q; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"错误,\""<<dirName<<"\"子目录不存在"<<endl; 
} 
else
{ 
	while(p)
	{ 
		if(p->type==0)
		{ 
			if(!strcmp(p->name,dirName))
			{ 
				flag=1; 
				break; 
			} 
		} 
	p=p->next; 
	} 
	if(flag==1)
	{ 
		if(p==workDir->sub)
		{ 
			workDir->sub=p->next; 
		} 
		else
		{ 
			q=workDir->sub; 
			while(q->next!=p)
			{ 
				q=q->next; 
			} 
			q->next=p->next; 
			delete p; 
		} 
	cout<<"\""<<dirName<<"\"子目录已删除"<<endl; 
	} 
	else
	{ 
		cout<<"错误,\""<<dirName<<"\"子目录不存在"<<endl; 
	} 
} 
} 



int main() 
{ 
int len,fileSize,flag,comm; 

char string[50]; 
char command[10]; 
char name[40]; 
char *s,*s1; 

initial(); 
flag=1; 
while(flag){ 
cout<<endl<<" 模拟文件管理模拟系统"<<endl; 
cout<<endl<<"cd 改变目录 create 创建文件 del 删除文件 "<<endl<<"dir 显示目录 md 创建目录 rd 删除目录"<<endl<<"exit 退出"<<endl; 
cout<<endl<<"-----------------------------------------------"<<endl; 
printf("%s:>#",path); 

gets(string); 
len=strlen(string); 

if(len==0)
{ 
	strcpy(command,"errer"); 
} 
else
{//获得命令 
	s=NULL; 
	s=strchr(string,' '); 
	if(s!=NULL)
	{ 
		*s='\0'; 
	} 
strcpy(command,string); 

//测试命令类型 
if((!strcmp(command,"CD"))||!strcmp(command,"cd"))
{ 
	comm=1; 
} 
else
{ 
	if((!strcmp(command,"CREATE"))||!strcmp(command,"create"))
	{ 
		comm=2; 
	}  
	else
	{ 
		if((!strcmp(command,"DEL"))||!strcmp(command,"del"))
		{ 
			comm=3; 
		} 
		else
		{ 
			if((!strcmp(command,"DIR"))||!strcmp(command,"dir"))
			{ 
				comm=4; 
			} 
			else
			{ 
				if((!strcmp(command,"MD"))||!strcmp(command,"md"))
				{ 
					comm=5; 
				} 
				else
				{ 
					if((!strcmp(command,"RD"))||!strcmp(command,"rd"))
					{ 
						comm=6; 
					} 
					else
					{ 
						if((!strcmp(command,"EXIT"))||!strcmp(command,"exit"))
						{ 
							comm=0; 
						} 
						else
						{ 
							comm=100; 
						} 
					} 
				} 
			} 
		} 
	} 
} 
switch(comm){ 
case 1: 
//改变目录 
strcpy(name,s+1); 
CD(name); 
break; 
case 2: 
//创建文件 
strcpy(name,s+1); 
fileSize=50; 
CREATE(name,fileSize); 
break; 
case 3: 
//删除文件 
strcpy(name,s+1); 
DEL(name); 
break; 
case 4: 
//显示目录 
LSALL(); 
break; 
case 5: 
//创建目录 
strcpy(name,s+1); 
MD(name); 
break; 
case 6: 
//删除目录 
strcpy(name,s+1); 
RD(name); 
break; 
case 0: 
//退出系统 
flag=0; 
break; 
default: 
cout<<"命令错误"<<endl; 
} 
} 
} 
}
