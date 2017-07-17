#include "2048.h"

int xsum=4;  //链表x轴长度
int ysum=4;  //链表y轴长度
Shizi *d_11=NULL;  //表格顶点之一
Shizi *d_y1=NULL;  //表格顶点之一
Shizi *d_1x=NULL;  //表格顶点之一
Shizi *d_yx=NULL;  //表格顶点之一
Item *li=NULL;  //随机数链表开始位置
Undo *undo_now=NULL;  //历史记记录表开始位置
int fen=0;  //分数

int main(int argc, char const *argv[])
{
    char a=0;
    int q=0;
    start:kai();
    printf("\n");
    s_tian();
    while(1){
        if(s_tian()){
            xian();
            printf("游戏结束,试试=键\n");
        }else{
            undo_c();
            xian();
        }
        while(1){
            Dgetc(a);
            if(a=='w'||a=='a'||a=='s'||a=='d'){
                q=1;
                if(paixu(a))  
                    break;
            }else if(a=='-'){
                reset();
                goto start;
            }else if(a=='='){
            	if(q){
            		q=0;
            		undo_z();
            	}
                undo_z();
                xian();
            }else
                ;
        }
    }
	printf("游戏结束\n"); 
	return 0;
}
void reset(void)
{
	Shizi *j_i=d_y1;
    Shizi *j_i2=j_i;
	while(1){
        while(1){
            if(j_i->you!=NULL){
                j_i2=j_i;
                j_i=j_i->you;
                free(j_i2);
            }
            else
                break;
        }
        if(j_i->xia!=NULL){
            j_i2=j_i;
            j_i=j_i->xia;
            free(j_i2);
        }else
            break;
        while(1){
            if(j_i->zuo!=NULL){
                j_i2=j_i;
                j_i=j_i->zuo;
                free(j_i2);
            }
            else
                break;
        }
        if(j_i->xia!=NULL){
            j_i2=j_i;
            j_i=j_i->xia;
            free(j_i2);
        }else
            break;
    }
    Item *a=li;
    Item *b=a;
    while(a!=NULL){
    	b=a;
    	a=a->xia;
    	free(b);
    }
    Undo *c=undo_now;
    Undo *d=c;
    while(c!=NULL){
    	d=c;
    	c=c->shang;
    	free(d);
    }
	xsum=4;
	ysum=4;
	d_11=NULL; 
	d_y1=NULL;
	d_1x=NULL;
	d_yx=NULL;
	li=NULL;  
	undo_now=NULL; 
    fen=0;
}
void form_c_z(int *a,bool b)
{
	Shizi *j_i=d_y1;
	while(1){
        while(1){
        	if(b)
				j_i->sum=*(a++);
			else
	            *(a++)=j_i->sum;
            if(j_i->you!=NULL)
                j_i=j_i->you;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
            break;
        while(1){
        	if(b)
				j_i->sum=*(a++);
			else
	            *(a++)=j_i->sum;
            if(j_i->zuo!=NULL)
                j_i=j_i->zuo;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
            break;
    }
}
void undo_z(void)
{
    form_c_z(undo_now->form,1);
    fen=undo_now->u_fen;
    if(undo_now->shang==NULL)
        return ;
    Undo *a=undo_now;
    undo_now=undo_now->shang;
    free(a);

}
void undo_c(void)
{
	Undo *a=(Undo *)malloc(sizeof(Undo));
	a->shang=undo_now;
	a->form=(int *)malloc(xsum*ysum*sizeof(int));
	undo_now=a;
    undo_now->u_fen=fen;
	form_c_z(a->form,0);
}
bool paixu(char a)
{
    int x;
    bool bian=0;
    Shizi *l_b1=NULL;
    Shizi *l_b2=NULL;
    Shizi *l_b3=NULL;
    if(a=='w'){
        l_b1=d_y1;
        x=xsum;
    }
    else if(a=='s'){
        l_b1=d_11;
        x=xsum;
    }
    else if(a=='a'){
        l_b1=d_y1;
        x=ysum;
    }
    else if(a=='d'){
        l_b1=d_yx;
        x=ysum;
    }
    else
        exit(1);
    for(int i=0;i<x;i++){
        l_b2=l_b1;
        l_b3=c_kong(l_b2,a,1,1);
        while(l_b3!=NULL){
            if(l_b2->sum==l_b3->sum){
                l_b2->sum*=2;
                fen+=l_b2->sum;
                l_b3->sum=0;
                bian=1;
            }
            l_b2=l_b3;
            l_b3=c_kong(l_b2,a,1,1);
        }
        l_b2=l_b1;
        while(1){
            l_b2=c_kong(l_b1,a,0,0);
            if(l_b2==NULL)
                break;
            l_b3=c_kong(l_b2,a,1,1);
            if(l_b3==NULL)
                break;
            l_b2->sum=l_b3->sum;
            l_b3->sum=0;
            bian=1;
        }
        if(a=='w'||a=='s')
            l_b1=l_b1->you;
        else if(a=='a'||a=='d')
            l_b1=l_b1->xia;
        else
            exit(1);
    }
    return bian;
}
Shizi *c_kong(Shizi *a,char b,int c,bool d)
{
    if(b=='w'){
        if(d)
            if(a->xia!=NULL)
                a=a->xia;
            else
                return NULL;
        while(1){
            if((!(a->sum))^c)
                return a;
            if(a->xia==NULL)
                return NULL;
            a=a->xia;
        }
    }else if(b=='s'){
        if(d)
            if(a->shang!=NULL)
                a=a->shang;
            else
                return NULL;
        while(1){
            if((!(a->sum))^c)
                return a;
            if(a->shang==NULL)
                return NULL;
            a=a->shang;
        }
    }else if(b=='a'){
        if(d)
            if(a->you!=NULL)
                a=a->you;
            else
                return NULL;
        while(1){
            if((!(a->sum))^c)
                return a;
            if(a->you==NULL)
                return NULL;
            a=a->you;
        }
    }else if(b=='d'){
        if(d)
            if(a->zuo!=NULL)
                a=a->zuo;
            else
                return NULL;
        while(1){
            if((!(a->sum))^c)
                return a;
            if(a->zuo==NULL)
                return NULL;
            a=a->zuo;
        }
    }else
        ;
    exit(1);
}
bool fail(void)
{
    Shizi *j_i=d_y1;
    while(1){
        while(1){
            if((j_i->you!=NULL&&j_i->sum==j_i->you->sum)||(j_i->xia!=NULL&&j_i->sum==j_i->xia->sum))
                return 0;
            if(j_i->you!=NULL)
                j_i=j_i->you;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
        	break;
        while(1){
            if((j_i->zuo!=NULL&&j_i->sum==j_i->zuo->sum)||(j_i->xia!=NULL&&j_i->sum==j_i->xia->sum))
                return 0;
            if(j_i->zuo!=NULL)
                j_i=j_i->zuo;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
        	break;
    }
    return 1;
}
bool s_tian(void)
{
    int k_s,s_s;
    k_s=j_man(-1);
    s_s=suiji(k_s);
    j_man(s_s);
    if(k_s==1)
        return fail();
    return 0;
}
int j_man(int k_s)
{
    int i=0;
    Shizi *j_i=d_y1;
    while(1){
        while(1){
            if(j_i->sum==0){
                i++;
                if(i==k_s)
                    j_i->sum=tianjia();
            }
            if(j_i->you!=NULL)
                j_i=j_i->you;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
        	break;
        while(1){
            if(j_i->sum==0){
                i++;
                if(i==k_s)
                    j_i->sum=tianjia();
            }
            if(j_i->zuo!=NULL)
                j_i=j_i->zuo;
            else
                break;
        }
        if(j_i->xia!=NULL)
            j_i=j_i->xia;
        else
        	break;
    }
    return i;
}
int shhru(int s,int d)
{
    int i=0;
    while(1){
        scanf("%d",&i);
        while(getchar()!='\n')
            ;
        if(i<=d&&i>=s)
            break;
        else
            printf("\t错误的值,应在%d到%d之间\n\t",s,d);
    }
    return i;
}
int tianjia(void)
{
    int i=0;
    Item *b=li;
    i=suiji(li->gai);
    while(b->xia->gai>=i)
        b=b->xia;
    return b->sum;
}
int suiji(int a)
{
    return rand()%a+1;
}
void xian(void) 
{
    Shizi *a=d_y1;
    Shizi *b=a;
    system(CLEAY);
    printf("分数:%d\n",fen);
    for(int i=0;i<(xsum*7)+1;i++)
        putchar('_');
        putchar('\n');
    for(int i=0;i<ysum;i++){
        putchar('|');
        for(int i=0;i<xsum;i++)
            printf("      |");
        putchar('\n');
        putchar('|');
        for(int i=0;i<xsum;i++){
            if(a->sum==0)
                printf("      |");
            else
                printf("%6d|",a->sum);
            a=a->you;
        }
        putchar('\n'); 
        putchar('|');
        for(int i=0;i<xsum;i++)
            printf("______|");
        putchar('\n');
        a=b->xia;
        b=a;
    }
}
void jianli(void) 
{
    Shizi *z_z=NULL; 
    Shizi *z_x=NULL;
    Shizi *z_a=NULL;
    Shizi *z_s=NULL;
    Shizi *z_y=NULL;
    for(int y=1;y<=ysum;y++){
    	for(int x=1;x<=xsum;x++){
    		z_a=z_y;
    		z_y=(Shizi *)malloc(sizeof(Shizi));
    		if(x==1){  
    			z_a=(Shizi *)malloc(sizeof(Shizi));
    			z_a->zuo=NULL;
                if(y==1)
                    d_11=z_a;
                if(y==ysum)
                    d_y1=z_a;
    		}else
    			z_a->zuo=z_z;
    		if(x==xsum){ 
    			free(z_y);
    			z_a->you=NULL;
                if(y==1)
                    d_1x=z_a;
                if(y==ysum)
                    d_yx=z_a;
    		}else
    			z_a->you=z_y;
    		if(y==1) 
    			z_a->xia=NULL;
    		else{
    			z_a->xia=z_x;
    			z_x=z_x->you;
    		}
    		z_z=z_a;
    		if(y!=1){ 
    			z_s=z_a->xia;
    			z_s->shang=z_a;
    		}
    		if(y==ysum)
    			z_a->shang=NULL;
            z_a->sum=0;
    	}
    	z_x=z_a;
    	while(z_x->zuo!=NULL)
    		z_x=z_x->zuo;
    }
}
void jia(int i,int i2)
{
    if(li==NULL){
        li=(Item *)malloc(sizeof(Item));
        li->sum=0;
        li->gai=0;
        li->xia=NULL;
        jia(i,i2);
        return ;
    }
        Item *a=(Item *)malloc(sizeof(Item));
        a->sum=i;
        a->gai=i2+(li->gai);
        a->xia=li;
        li=a;
}
void kai(void)
{
    srand(time(0));
    system(CLEAY);
	logo();
    printf( "                            《2048》是一款比较流行的数字游戏，最早于2014年3月20日发行。");
    printf("\n                   原版2048首先在GitHub上发布，原作者是Gabriele Cirulli，后被移植到各个平台。"); 
    printf("\n             wasd控制上下左右 游戏中按'-'返回主菜单 按'='撤回(默认保存10个可以自定义) 显示错误请放大窗口\n");
    printf("\n\tA:开始游戏\n\tB:自定义游戏\n\tC:退出游戏\n------->") ;
    char a;
    while(1){
        Dgetc(a); 
        printf("\b");
        if(a=='A'||a=='a'){
        	xsum=4;
        	ysum=4;
			jia(2,9);
			jia(4,1);
            break;
        }
        else if(a=='b'||a=='B'){
            zi();
            break;
        }
        else if(a=='c'||a=='C')
            exit(0);
        else
            ; 
    }
    jianli();
}
void logo(void)
{	      
    unsigned long int b;
    unsigned long int c;
    unsigned long int *ai;
    unsigned long int a[]={ 
        0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFC000FF,0xFFC001FF,0xFFFF807F,0xFF0003FF,0xFF00001F,
        0xFE00007F,0xFFFF007F,0xF80000FF,0xFE00000F,0xFC01C01F,0xFFFC007F,0xF00FC07F,0xFFC7F80F,0xF807F00F,
        0xFFF8007F,0xF03FE03F,0xFFFFF80F,0xF80FF80F,0xFFE0007F,0xF01FE03F,0xFFFFF80F,0xF81FFC0F,0xFFC0607F,
        0xF807807F,0xFFFFF01F,0xF01FFC07,0xFF01E07F,0xFE0001FF,0xFFFFC03F,0xF01FFC07,0xFE03E07F,0xFF0007FF,
        0xFFFF00FF,0xF01FFC07,0xF80FE07F,0xF80000FF,0xFFFC03FF,0xF01FFC0F,0xF03FE07F,0xF01FC03F,0xFFF00FFF,
        0xF81FF80F,0xE0000007,0xE03FF03F,0xFFC03FFF,0xF80FF80F,0xE0000007,0xE03FF03F,0xFE00FFFF,0xFC07E01F,
        0xE0000007,0xE01FE03F,0xFE000007,0xFE00003F,0xFFFFE07F,0xF000007F,0xFE000007,0xFF0000FF,0xFFFFE07F,
        0xFC0000FF,0xFFFFFFFF,0xFFF007FF,0xFFFFFFFF,0xFFC00FFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
    };
    ai=a;
    for(int i=0;i<18;i++){
        for(int i=0;i<4;i++){
            b=0x80000000;
            for(int i=0;i<32;i++){
                c=*ai&b;
                if(c==b)
                    putchar(' ');
                else
                    putchar('&');
                b>>=1;
            }
            ai++;
        }
        printf("\n");
    }
}
void zi(void)
{ 
    char a;
    int undo_big;
    system(CLEAY);
    logo(); 
    printf("\n\t输入X轴:");
    xsum=shhru(2,100);
    system(CLEAY);
    logo();
    printf("\n\t输入Y轴:");
    ysum=shhru(2,100);
    system(CLEAY);
    logo(); 
    gai_shu:printf("\n\t是否更改出现的数字的种类和概率,默认出现2和4概率9:1(y/n)\n\t");
    scanf("%c",&a);
    while(getchar()!='\n')
		;
    if(a=='Y'||a=='y'){
    	int i=0,i2=0;
      	while(1){
            printf("\t输入一个要添加的数字,输入非数字退出\n\t");
            a=getchar();
            if(a>='0'&&a<='9')
                ungetc(a,stdin);
            else{
                if(li==NULL){
                    printf("\t至少添加一个数字\n");
                    while(getchar()!='\n')
                        ;
                    goto gai_shu;
                }
                return ;
            }
            i=shhru(INT_MIN,INT_MAX);
            system(CLEAY);
            logo(); 
            printf("\t输入出现的概率\n\t");
            i2=shhru(1,10000);
            system(CLEAY);
            logo(); 
			jia(i,i2);
    	}
    }else{
        jia(2,9);
        jia(4,1);
    }
}