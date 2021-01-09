#include <sstream>
#include <iostream>
#include "set.h"



bool Copy(List L1, List& L2) {
	if (!L1.head) {
		return ERROR;
	}
	PNode current = L1.head->next;
	while (current) {
		Append(L2, current->data);
		current = current->next;
	}

	return OK;
}

// 求两集合的补集
bool Complement(List L1, List L2, List& L3) {
	PNode node_l2 = L2.head;

	for (int i = 1; i <= L2.length; i++) {
		node_l2 = node_l2->next;
		if (!LocateElem(L1, node_l2->data)) {
			Append(L3, node_l2->data);
		}
	}
	sort(L3);
	return OK;
}

//求两集合的差集
bool Difference(List L1, List L2, List& L3) {
	PNode node_l1 = L1.head;

	for (int i = 1; i <= L1.length; i++) {
		node_l1 = node_l1->next;
		if (!LocateElem(L2, node_l1->data)) {
			Append(L3, node_l1->data);
		}
	}
	sort(L3);
	return OK;
}

//求两集合的交集
bool Intersection(List L1, List L2, List& L3) {
	PNode node_b = L2.head;

	for (int i = 1; i <= L2.length; i++) {
		node_b = node_b->next;
		if (LocateElem(L1, node_b->data)) {
			Append(L3, node_b->data);
		}
	}
	sort(L3);
	return OK;
}

//求两集合并集
bool Union(List L1, List L2, List& L3) {
	PNode node_l2 = L2.head;
	Copy(L1, L3);

	for (int i = 1; i <= L2.length; i++) {
		node_l2 = node_l2->next;
		if (!LocateElem(L3, node_l2->data)) {
			Append(L3, node_l2->data);
		}
	}
	sort(L3);
	return OK;

}

//创建新的集合
bool CreateSet(List& L, ElemType* s, int length) {
	if (InitList(L)) {
		for (int i = 0; i < length; i++) {
			if (!LocateElem(L, s[i])) {
				Append(L, s[i]);
			}
		}
		sort(L);//排序 
		return OK;
	}

	return ERROR;
}

bool CreateSet(List& L) {
	if (InitList(L)) {
		return OK;
	}

	return ERROR;
}

//销毁集合 
bool DestroySet(List& L) {
	DestroyList(L);
	return OK;
}

double stringToNum(const string& str)
{
	istringstream iss(str);
	double num;
	iss >> num;
	return num;
}

bool sort(List& L) {
	int flag = 1;
	ElemType temp;
	PNode current;

	current = L.head->next;
	for (int i = 1; i < L.length; i++) {
		if (!isNum(current->data)) {
			flag = 0;
			break;
		}
		current = current->next;
	}

	if (flag) { //数字排序
		for (int i = L.length; i >= 2; i--) {
			current = L.head->next;
			for (int j = 1; j < i; j++) {
				if (stringToNum(current->data) > stringToNum(current->next->data)) {
					temp = current->data;
					current->data = current->next->data;
					current->next->data = temp;
				}
				current = current->next;
			}
		}
	}
	else { //字符串排序 
		for (int i = L.length; i >= 2; i--) {
			current = L.head->next;
			for (int j = 1; j < i; j++) {
				if (current->data > current->next->data) {
					temp = current->data;
					current->data = current->next->data;
					current->next->data = temp;
				}
				current = current->next;
			}
		}
	}
	return OK;
}

bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}

/* 以下为对线性表的操作 */

//删去重复元素
bool removeReated(List& L) {
	if (!L.head) {
		return ERROR;
	}

	PNode current = L.head->next;

	for (int i = 1; i <= L.length; i++) {
		PNode temp = current;
		for (int j = i + 1; j < L.length; j++) {
			if (current->data == temp->next->data) {
				PNode f = temp->next;
				temp->next = f->next;
				delete f;
				L.length--;
			}

			temp = temp->next;
		}

		current = current->next;
	}

	return OK;
}

//返回线性表长度
bool ListLength(List L, int& index) {
	if (!L.head) {
		return ERROR;
	}
	return L.length;
}
bool InitList(List& L) {
	L.head = L.head = new Node;//L.head = (PNode)malloc(sizeof(Node));
	if (!L.head) {
		return ERROR;
	}

	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;

	return OK;
}
bool DestroyList(List& L) {
	if (!L.head) {
		return ERROR;
	}
	PNode current = L.head;
	while (current) {
		PNode f = current;
		current = current->next;
		delete f;
	}
	//   PNode p;
	//   while(L.head != L.tail){
	//		p = L.head;
	//		L.head = L.head->next;
	//		free(p);
	//	} 

	//	free(L.head);
	//printf("销毁成功");
	return OK;
}
bool ClearList(List& L) {
	if (!L.head) {
		return ERROR;
	}
	PNode current = L.head;
	while (current != L.tail) {
		PNode f = current;
		current = current->next;
		delete f;
	}
	L.head = L.tail;
	L.length = 0;
	return OK;
}
bool ListEmpty(List& L) {
	if (!L.head) {
		return TRUE;
	}

	return FALSE;
}
bool GetElem(List L, int index, ElemType& e) {
	if (!L.head || index < 1 || index > L.length) {
		return ERROR;
	}
	PNode current = L.head;
	int i = 0;
	while (i != index) {
		current = current->next;
		i++;
	}

	e = current->data;

	return OK;
}
bool LocateElem(List L, ElemType e) {
	if (!L.head) {
		return FALSE;
	}

	PNode current = L.head->next;
	while (current) {
		if (current->data == e) {
			return TRUE;
		}
		current = current->next;
	}

	return FALSE;
}

bool Append(List& L, ElemType e) {
	if (!L.head) {
		return ERROR;
	}

	PNode newNode = new Node;
	newNode->data = e;
	newNode->next = NULL;

	L.tail->next = newNode;
	L.tail = newNode;
	L.length++;
	return OK;
}
bool InsertElem(List& L, int index, ElemType e) {
	if (!L.head) {
		return ERROR;
	}

	if (index < 1 || index > L.length + 1) {
		return ERROR;
	}
	int i = 1;

	PNode current = L.head;
	while (i != index) {
		current = current->next;
		i++;
	}

	PNode newNode = new Node;

	newNode->data = e;
	newNode->next = current->next;
	current->next = newNode;

	if (index == L.length + 1) {
		L.tail = newNode;
	}

	L.length++;
	return OK;
}
bool removeIndex(List& L, int index)
{
	if (!L.head || L.length == 0) {
		return ERROR;
	}

	if (index < 1 || index > L.length) {
		return ERROR;
	}
	PNode current = L.head;
	int i = 0;
	while (++i != index) {
		current = current->next;
	}

	PNode f = current->next;
	current->next = f->next;
	delete f;
	L.length--;

	return OK;
}

bool removeElem(List& L, ElemType e) {
	if (!L.head || L.length == 0) {
		return ERROR;
	}

	PNode current = L.head;

	while (current) {
		current = current->next;

		if (current->data == e) {
			PNode f = current->next;
			current = f;

			delete f;
			L.length--;
			return OK;
		}
	}

	return ERROR;

}
bool printList(List L) {
	if (!L.head) {
		return ERROR;
	}

	std::cout << "{";
	if (!L.length) {
		std::cout << "}" << endl;
		return OK;
	}

	PNode current = L.head->next;

	for (int i = 1; i < L.length; i++) {
		std::cout << current->data << ",";
		current = current->next;
	}

	std::cout << current->data << "}" << endl;
	return OK;
}