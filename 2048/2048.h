#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include <unistd.h>
#include <limits.h>
#ifdef _WIN32 
#include <conio.h>
#define CLEAY "cls"//win下的清屏 cls
#define Dgetc(a) a=getch(); //win无缓冲输入
#else 
#define CLEAY "clear"  //linux下的清屏 clear
#define Dgetc(a) system("stty raw");a=getchar();system("stty -raw");  //linux无缓冲输入
#endif 

typedef struct item{
	int sum; //可以的数字
	int gai; //概率
	struct item *xia; //上一个表
}Item; //出现数字链表

typedef struct shizi{
	int sum; //当前格子的数字
	struct shizi *zuo; //左
	struct shizi *you; //右
	struct shizi *shang; //上
	struct shizi *xia; //下
}Shizi; //储存表格的十字链表

typedef struct undo{
	int u_fen; //分数
	int *form; //一维数组 按顺序保存
	struct undo *shang; //上一个表
}Undo; //出现数字链表

/////////////界面和自定义////////////////////////////
void logo(void); //打印logo
void xian(void); //显示表格 分数
void zi(void);  //自定义长宽和出现数字链表
int shhru(int s,int d); //向用户要求输入一个s到d的数
void jia(int i,int i2); //加入一个数字到出现数字链表
void chu(void); //默认长宽和出现数字链表
void kai(void); //显示开始菜单 logo 选择 默认初始化或自定义
void reset(void);  //回收三个链表的内存 初始化全局变量
////////////////游戏操作//////////////////////////////
int suiji(int a); //随机一个1到a的数
Shizi *c_kong(Shizi *a,char b,int c,bool d); //十字链表下的c是0时返回a在b(wasd)反方向下的第一个是0结构地址 c是1时返回非零 d是1时跳过搜素a 反之不跳没有找到预期的数返回NULL
bool fail(void); //当十字表满时调用 不能消除时返回1 否0
int tianjia(void);  //返回一个随机出来的出现数字链表的一个数
int j_man(int k_s); //返回十字链表中0的数量 向第k_s个0添加一个随机数 为负数不添加
bool s_tian(void); //向十字链表随机位置添加一个随机数 添加后不能消除时返回1 否0
void jianli(void); //根据全局变量建立十字表格 四个定点保存到全局变量
bool paixu(char a); //根据a的值(wasd)排序十字链表 排序后有变化返回1否0
////////////////撤销与恢复///////////////////////////
void form_c_z(int *a,bool b); //b是1复制a还原到游戏进度 b是0是时把游戏进度保存到a
void undo_c(void); //保存当前链表到历史纪录
void undo_z(void); //撤销操作


/*  
    _________________________________________________________
    |      |      |      |      |      |      |      |      |
   y|      |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
	|      |      |      |      |      |      |      |      |
	|	   |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
	|      |      |      |      |      |      |      |      |
	|	   |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
	|      |      |      |      |      |      |      |      |
	|	   |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
	|      |      |      |      |      |      |      |      |
	|	   |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
	|      |      |      |      |      |      |      |      |
   1|	   |      |      |      |      |      |      |      |
	|______|______|______|______|______|______|______|______|
        1                                                 x
下面是设计图
http://naotu.baidu.com/file/39225977ee66ea1d2128a0fa269246be?token=0bef6f354d510399 
密码为 c1yK
*/