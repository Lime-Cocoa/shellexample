#include<conio.h> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Myprintf printf("|---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---|\n") //������
#define bsize 4     //������С
#define psize 16     //���̴�С
typedef struct page{ 
       int num;  //��¼ҳ���
       int time;  //��¼�����ڴ�ʱ��
}Page;                   //ҳ���߼��ṹ���ṹΪ�����㷨ʵ�����

Page b[bsize];            //�ڴ浥Ԫ�� 
int c[bsize][psize];   //�ݱ����ڴ浱ǰ��״̬��������
int queue[100];      //��¼�������
int K;              //������м������� 
int phb[bsize] = {0};   //�������
int pro[psize] = {0};     //�������к�
int flag[bsize] = {0};  //���̵ȴ�����(������δ��ʹ�õĽ��̱�־)
int i = 0, j = 0, k = 0;   //i��ʾ�������к�,j��ʾ������
int m = -1, n = -1;       //�������кͽ����Ƿ���ͬ�жϱ�־
int max = -1,maxflag = 0; //����滻���������±�
int count = 0;            //ͳ��ҳ��ȱҳ����

int* build(){
	//����������кź���
	printf("�������һ���������к�Ϊ��\n");
	int i = 0;
    for(i=0; i<psize; i++){
		pro[i] = 10*rand()/(RAND_MAX+1)+1;
        printf("%d  ",pro[i]);
    }
    printf("\n");
	return(pro);
}

int searchpb(){
	//���ҿ��������
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
	//������ͬ����
	for(j = 0; j < bsize; j++){
       if(phb[j] == pro[i]){
          n = j;
		  return j;
       }
    }
	return -1;
}
 
void empty(){
	//��ʼ���ڴ�
	for(i=0;i<bsize;i++){
		phb[i]=0;
	}
    count=0;                //����������
}

void FIFO(){
   //�Ƚ��ȳ�ҳ���û��㷨
    for(i = 0; i<psize; i++){ 
	   m=searchpb();
	   n=searchpro();
        for(j = 0; j < bsize;j++){
        	//��flagֵ����
           if(flag[j]>maxflag){
                maxflag = flag[j];
                max = j;
            }
        }   
        if(n == -1){               
			//��������ͬ����
           if(m != -1){            
           	   	//���ڿ��������
			   	phb[m] = pro[i];   //���̺�����ÿ��������
			   	count++;
               	flag[m] = 0;
               	for(j = 0;j <= m; j++){
                  	flag[j]++;
               	}
               	m = -1;
           }
           else{               
              	//�����ڿ��������
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
			//������ͬ�Ľ���
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
    printf("ȱҳ����Ϊ��%d\n",count);
	printf("\n");
}

void Init(Page *b,int c[bsize][psize]){ 
 	//��ʼ���ڴ浥Ԫ��������
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
 	//ȡ�����ڴ���ͣ����õ�ҳ��,Ĭ��״̬��Ϊ��������ҳ��
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
	//�ж�ҳ���Ƿ������ڴ���
    int i; 
    for(i=0;i<bsize;i++){ 
        if (fold==b[i].num) 
            return i; 
    } 
    return -1; 
} 

void Lruu(int fold,Page *b){ 
	//LRU���Ĳ���
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
        queue[++K]=fold; //��¼����ҳ��
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
        //��¼��ǰ���ڴ浥Ԫ�е�ҳ��
            for(j=0;j<bsize;j++) 
                c[j][i]=b[j].num; 
    } 
    //������ 
    printf("�ڴ�״̬Ϊ��\n"); 
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
       	printf("\n�������Ϊ:"); 
       	for(i=0;i<K+1;i++) 
		printf("%3d",queue[i]); 
       	printf("\nȱҳ����Ϊ��%6d\nȱҳ�ʣ�%16.6f",K+1,(float)(K+1)/psize); 
}

int main()
{
	int sel;	
    do{	
    	printf("0���˳�(Exit)\n");
    	printf("1�������������\n");
    	printf("2�����δʹ��(LRU)\n");
    	printf("3���Ƚ��ȳ�(FIFO)\n");
    	printf("<��ѡ����Ҫִ�еĲ���:(0)(1)(2)(3)>\n");
    	scanf("%d",&sel);
    	if(sel == 0){
    		printf("�˳� \n");
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
