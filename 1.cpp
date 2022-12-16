#include<conio.h> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Myprintf printf("|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n") //表格控制
#define bsize 4     //物理块大小
#define psize 16     //进程大小
typedef struct page{ 
       int num;  //记录页面号
       int time;  //记录调入内存时间
}Page;                   //页面逻辑结构，结构为方便算法实现设计

Page b[bsize];            //内存单元数 
int c[bsize][psize];   //暂保存内存当前的状态：缓冲区
int queue[100];      //记录调入队列
int K;              //调入队列计数变量 
int phb[bsize] = {0};   //物理块标号
int pro[psize] = {0};     //进程序列号
int flag[bsize] = {0};  //进程等待次数(存放最久未被使用的进程标志)
int i = 0, j = 0, k = 0;   //i表示进程序列号,j表示物理块号
int m = -1, n = -1;       //物理块空闲和进程是否相同判断标志
int max = -1,maxflag = 0; //标记替换物理块进程下标
int count = 0;            //统计页面缺页次数

int* build(){
	//随机产生序列号函数
	printf("随机产生一个进程序列号为：\n");
	int i = 0;
    for(i=0; i<psize; i++){
		pro[i] = 10*rand()/(RAND_MAX+1)+1;
        printf("%d  ",pro[i]);
    }
    printf("\n");
	return(pro);
}

int searchpb(){
	//查找空闲物理块
	for(j=0; j<bsize; j++){
		if(phb[j] == 0){
           m = j; 
		   return m;     
           break;
        }	
	}
	return -1;
}

int searchpro(){
	//查找相同进程
	for(j = 0; j < bsize; j++){
       if(phb[j] == pro[i]){
          n = j;
		  return j;
       }
    }
	return -1;
}
 
void empty(){
	//初始化内存
	for(i=0;i<bsize;i++){
		phb[i]=0;
	}
    count=0;                //计数器置零
}

void FIFO(){
   //先进先出页面置换算法
    for(i = 0; i<psize; i++){ 
	   m=searchpb();
	   n=searchpro();
        for(j = 0; j < bsize;j++){
        	//找flag值最大的
           if(flag[j]>maxflag){
                maxflag = flag[j];
                max = j;
            }
        }   
        if(n == -1){               
			//不存在相同进程
           if(m != -1){            
           	   	//存在空闲物理块
			   	phb[m] = pro[i];   //进程号填入该空闲物理块
			   	count++;
               	flag[m] = 0;
               	for(j = 0;j <= m; j++){
                  	flag[j]++;
               	}
               	m = -1;
           }
           else{               
              	//不存在空闲物理块
            	phb[max] = pro[i];
              	flag[max] = 0;
              	for(j = 0;j < bsize; j++){
              		flag[j]++;
              	}
              	max = -1;
              	maxflag = 0;
              	count++;
           }
       }
       else{                    
			//存在相同的进程
		   	phb[n] = pro[i];
           	for(j = 0;j < bsize; j++){
			   flag[j]++;
           	}
           	n = -1;
       }
       	for(j = 0 ;j < bsize; j++){
		  	printf("%d  ",phb[j]);
       	}
       printf("\n");
    }
    printf("缺页次数为：%d\n",count);
	printf("\n");
}

void Init(Page *b,int c[bsize][psize]){ 
 	//初始化内存单元、缓冲区
    int i,j; 
    for(i=0;i<psize;i++){ 
        b[i].num=-1; 
        b[i].time=psize-i-1; 
    } 
    for(i=0;i<bsize;i++) 
        for(j=0;j<psize;j++) 
            c[i][j]=-1; 
} 
 
int GetMax(Page *b){ 
 	//取得在内存中停留最久的页面,默认状态下为最早调入的页面
    int i; 
    int max=-1;
    int tag=0;
    for(i=0;i<bsize;i++){ 
        if(b[i].time>max){ 
            max=b[i].time; 
            tag=i; 
        } 
    } 
    return tag; 
}
 
int Equation(int fold,Page *b){ 
	//判断页面是否已在内存中
    int i; 
    for(i=0;i<bsize;i++){ 
        if (fold==b[i].num) 
            return i; 
    } 
    return -1; 
} 

void Lruu(int fold,Page *b){ 
	//LRU核心部分
    int i; 
    int val; 
    val=Equation(fold,b); 
    if (val>=0){ 
        b[val].time=0; 
        for(i=0;i<bsize;i++) 
            if (i!=val) 
                b[i].time++; 
    } 
    else{
        queue[++K]=fold; //记录调入页面
        val=GetMax(b); 
    	b[val].num=fold; 
        b[val].time=0; 
        for(i=0;i<bsize;i++) 
            if (i!=val) 
                b[i].time++; 
    } 
}
 
void LRU(){
    int i,j; 
    K=-1; 
    Init(b, c); 
    for(i=0;i<psize;i++){ 
        Lruu(pro[i],b); 
        c[0][i]=pro[i]; 
        //记录当前的内存单元中的页面
            for(j=0;j<bsize;j++) 
                c[j][i]=b[j].num; 
    } 
    //结果输出 
    printf("内存状态为：\n"); 
    Myprintf; 
    for(j=0;j<psize;j++) 
    	printf("|%2d ",pro[j]); 
       	printf("|\n"); 
       	Myprintf; 
       	for(i=0;i<bsize;i++){ 
            for(j=0;j<psize;j++){ 
              	if(c[i][j]==-1) 
                    printf("|%2c ",32); 
              	else 
                    printf("|%2d ",c[i][j]); 
            } 
            printf("|\n"); 
       	} 
       	Myprintf; 
       	printf("\n调入队列为:"); 
       	for(i=0;i<K+1;i++) 
		printf("%3d",queue[i]); 
       	printf("\n缺页次数为：%6d\n缺页率：%16.6f",K+1,(float)(K+1)/psize); 
}

int main()
{
	int sel;	
    do{	
    	printf("0、退出(Exit)\n");
    	printf("1、产生随机序列\n");
    	printf("2、最久未使用(LRU)\n");
    	printf("3、先进先出(FIFO)\n");
    	printf("<请选择所要执行的操作:(0)(1)(2)(3)>\n");
    	scanf("%d",&sel);
    	if(sel == 0){
    		printf("退出 \n");
		}
		if(sel == 1){
			build();
		}
		if(sel == 2){
			printf("LRU\n");
			LRU();
			empty();
			printf("\n");
		}
		if(sel == 3){
			printf("FIFO\n");
			FIFO();
			empty();
			printf("\n");
		}
	}while(sel!=0);
}
