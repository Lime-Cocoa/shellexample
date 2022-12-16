#include "stdio.h" 
#include "string.h" 
#include "iostream" 
#include "math.h" 
#include "stdlib.h" 
#include "iomanip" 
using namespace std;
// ******************Ŀ¼���ļ��Ľṹ����****** 
typedef struct node{ 
char name[50]; /*Ŀ¼���ļ�������*/ 
int type; /*0����Ŀ¼��1������ͨ�ļ�*/ 
struct node *next; /*ָ����һ���ֵܽ���ָ��*/ 
struct node *sub; /*ָ���һ���ӽ���ָ��*/ 
struct node *father; /*ָ�򸸽���ָ��*/ 
int size; /*������ļ����ʾ�ļ��Ĵ�С*/ 
}dirNode; 

dirNode *workDir; //���嵱ǰ����Ŀ¼ 
dirNode root; //�����Ŀ¼ 

char path[100]; //����·����Ϣ 

//��ʼ������ 
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

//��ʼ���½�㺯�� 
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

//�ı�Ŀ¼ 
void CD(char dirName[]) 
{ 
dirNode *p; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"����,\""<<dirName<<"\"��Ŀ¼������"<<endl; 
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
		cout<<"����Ŀ¼�ѽ���\""<<dirName<<"\""<<endl; 
	} 
	else
	{ 
		cout<<"����,\""<<dirName<<"\"��Ŀ¼������"<<endl; 
	} 
} 
} 

//�����ļ� 
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
	cout<<"\""<<fileName<<"\"�ļ������ɹ�"<<endl; 
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
				cout<<"����,\""<<fileName<<"\"�ļ��Ѵ���"<<endl; 
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
		cout<<"\""<<fileName<<"\"�ļ������ɹ�"<<endl; 
	} 
} 
} 

//ɾ���ļ� 
void DEL(char fileName[]) 
{ 
dirNode *p,*q; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"����,\""<<fileName<<"\"�ļ�������"<<endl; 
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
		cout<<"\""<<fileName<<"\"�ļ���ɾ��"<<endl; 
	} 
	else
	{ 
		cout<<"����,\""<<fileName<<"\"�ļ�������"<<endl; 
	} 
} 
} 

//��ʾ����Ŀ¼ 

//��ʾ��Ŀ¼�������ֵ�Ŀ¼���ļ� 
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
cout<<str<<"����Ŀ¼���ļ�:"<<endl; 
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

//��ʾ����Ŀ¼ 
void LSALL() 
{ 
dirNode *p; 

cout<<"��ʾ����Ŀ¼�ṹ";
cout<<endl<<"--------------------------------------------"<<endl; 

p=root.sub; 
if(p!=NULL)
  dirs(p,"root"); 
else
  cout<<"Ŀ¼Ϊ��"<<endl;

} 
//����Ŀ¼ 
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
	cout<<"\""<<dirName<<"\"��Ŀ¼�����ɹ�"<<endl; 
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
				cout<<"����,\""<<dirName<<"\"��Ŀ¼�Ѵ���"<<endl; 
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
	cout<<"\""<<dirName<<"\"��Ŀ¼�����ɹ�"<<endl; 
	} 
} 
} 

//ɾ��Ŀ¼ 
void RD(char dirName[]) 
{ 
dirNode *p,*q; 
int flag=0; 

p=workDir->sub; 
if(p==NULL)
{ 
	cout<<"����,\""<<dirName<<"\"��Ŀ¼������"<<endl; 
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
	cout<<"\""<<dirName<<"\"��Ŀ¼��ɾ��"<<endl; 
	} 
	else
	{ 
		cout<<"����,\""<<dirName<<"\"��Ŀ¼������"<<endl; 
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
cout<<endl<<" ģ���ļ�����ģ��ϵͳ"<<endl; 
cout<<endl<<"cd �ı�Ŀ¼ create �����ļ� del ɾ���ļ� "<<endl<<"dir ��ʾĿ¼ md ����Ŀ¼ rd ɾ��Ŀ¼"<<endl<<"exit �˳�"<<endl; 
cout<<endl<<"-----------------------------------------------"<<endl; 
printf("%s:>#",path); 

gets(string); 
len=strlen(string); 

if(len==0)
{ 
	strcpy(command,"errer"); 
} 
else
{//������� 
	s=NULL; 
	s=strchr(string,' '); 
	if(s!=NULL)
	{ 
		*s='\0'; 
	} 
strcpy(command,string); 

//������������ 
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
//�ı�Ŀ¼ 
strcpy(name,s+1); 
CD(name); 
break; 
case 2: 
//�����ļ� 
strcpy(name,s+1); 
fileSize=50; 
CREATE(name,fileSize); 
break; 
case 3: 
//ɾ���ļ� 
strcpy(name,s+1); 
DEL(name); 
break; 
case 4: 
//��ʾĿ¼ 
LSALL(); 
break; 
case 5: 
//����Ŀ¼ 
strcpy(name,s+1); 
MD(name); 
break; 
case 6: 
//ɾ��Ŀ¼ 
strcpy(name,s+1); 
RD(name); 
break; 
case 0: 
//�˳�ϵͳ 
flag=0; 
break; 
default: 
cout<<"�������"<<endl; 
} 
} 
} 
}
