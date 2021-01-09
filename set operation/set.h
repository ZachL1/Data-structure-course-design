/* set.h -- 集合类型的头文件 */
#ifndef SET_H_
#define SET_H_

#include <string>

/* 特定程序的声明 */
#define ERROR false
#define	OK true
#define TRUE true
#define	FALSE false
using namespace std;

/* 一般类型定义 */
typedef string ElemType;

typedef struct Node {
	ElemType data;//数据元素 
	struct Node* next;//下一个节点的地址
}Node, * PNode;//单个节点的结构体 

typedef struct List {
	PNode head;//集合的头节点
	PNode tail;//集合中的最后一个元素所在节点 
	int length;//集合中元素的个数
}List, * PList;


/* 函数原型 */

/* 创建集合 */
bool CreateSet(List& L);
/* 创建集合_重载 */
bool CreateSet(List& L, ElemType* s, int length);

/* 销毁集合 */
bool DestroySet(List& L);

/* 并集 */
bool Union(List L1, List L2, List& L3);

/* 交集 */
bool Intersection(List L1, List L2, List& L3);

/* 补集 */
bool Complement(List L1, List L2, List& L3);

/* 差集 */
bool Difference(List L1, List L2, List& L3);



/* 拷贝线性表 */
bool Copy(List L1, List& L2);

/* 求线性表长度 */
bool ListLength(List L, int& index);

/* 初始化线性表 */
bool InitList(List& L);//初始化线性表 

/* 销毁线性表 */
bool DestroyList(List& L);//销毁线性表 	

/* 清空线性表 */
bool ClearList(List& L);//清空线性表


/* 操作：		获取线性表index位置的元素					*/
/* 				L 指向一个已初始化的链表				*/
/*				index 为查找位置							*/
/*				e 返回第i个位置元素的值				*/
/* 后置条件：	查找成功返回true，查找失败返回false	*/
bool GetElem(List L, int index, ElemType& e);//获取线性表index位置的元素 

/* 操作：		查找线性表中值为e的元素				*/
/* 				L 指向一个已初始化的链表				*/
/*				e 为要查找的值						*/
/* 后置条件：	查找成功返回元素位置，查找失败返回 0	*/
bool LocateElem(List L, ElemType e);//判断e是否在L中， 不在返回false     

/* 操作：		添加e到线性表末尾				*/
/* 				L 指向一个已初始化的链表				*/
/*				e 为要查找的值						*/
/* 后置条件：	查找成功返回元素位置，查找失败返回 0	*/
bool Append(List& L, ElemType e);//添加e到线性表末尾               

/* 操作：		在线性表第i个位置插入元素				*/
/* 				L 指向一个已初始化的链表				*/
/*				index 为要插入的位置						*/
/*				e 为要插入的值						*/
/* 后置条件：	插入成功返回true，插入失败返回false	*/
bool InsertElem(List& L, int index, ElemType e);//插入e到index位置      

/* 操作：		删除线性表中值为e的元素					*/
/* 				L 指向一个已初始化的链表				*/
/*				e 为要删除的元素值						*/
/* 后置条件：	删除成功返回true，删除失败返回false	*/
bool removeElem(List& L, ElemType e);//删除线性表中e元素               

/* 操作：		删除线性表中第i个元素					*/
/* 				L 指向一个已初始化的链表				*/
/*				index 为要删除的位置						*/
/* 后置条件：	删除成功返回true，删除失败返回false	*/
bool removeIndex(List& L, int index);//删除线性表中index号元素         

/* 操作：		将集合元素排序						*/
/* 				L 指向一个已初始化的集合				*/
/* 后置条件：	集合元素递增排列						*/
bool sort(List& L);//给线性表排序，默认升序  

/* 输出链表 */
bool printList(List L);

/* 操作：		判断集合中元素是否是数字				*/
/* 				L 为需要判断的集合					*/
/* 后置条件：	是数字，返回true；否则返回false		*/
bool isNum(string str);


#endif