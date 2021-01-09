#include <iostream>
#include <algorithm>

#include "set.h"
using namespace std;


// 重载集合的输出运算符
ostream& operator<<(ostream& output, List& L) {
	printList(L);
	return output;
}
void inputSet(List& set);
void select();


int main() {
	printf("\t                              集合运算                 \n");
	printf("\t                              使用说明                 \n");
	select();

	while (true) {
	Lab:	List set1;
		List set2;
		List set3;
		CreateSet(set3);
		cout << "   请输入集合，输入示例: {1,2,3,4,8}或{\"word\",\"ppt\",\"append\"}或{'a','b','c','f'}\n\n";
		cout << "请输入集合A:";
		inputSet(set1);
		cout << "请输入集合B:";
		inputSet(set2);
		cout << "\n集合输入完成，请继续操作\n";

		//select();
		while (true) {
			cout << "\n请选择操作：";
			int ch;
			cin >> ch;
			switch (ch) {
			case 1:
				Intersection(set1, set2, set3); 
				cout << set3; ClearList(set3); 
				break;//交集 
			case 2:
				Union(set1, set2, set3); 
				cout << set3; ClearList(set3); 
				break;//并集 
			case 3:
				Complement(set1, set2, set3); 
				cout << set3; ClearList(set3); 
				break;//!A（AUB为全集）
			case 4:
				Complement(set2, set1, set3); 
				cout << set3; ClearList(set3); 
				break;//!B（AUB为全集） 
			case 5:
				Difference(set1, set2, set3); 
				cout << set3; ClearList(set3); 
				break;//A-B
			case 6:
				Difference(set2, set1, set3); 
				cout << set3; ClearList(set3); 
				break;//B-A
			case 7:
				DestroySet(set1); 
				DestroySet(set2); 
				DestroySet(set3);
				cout << endl;
				goto Lab;//重新输入集合 
			case 8:
				DestroySet(set1); 
				DestroySet(set2); 
				DestroySet(set3); 
				return 0;//退出 
			default:
				cout << "操作有误!"; 
				break;
			}
		}
	}

	return 0;
}


void select() {
	printf("\t***------------------------------------------------------------***\n");
	printf("\t###  请选择: 1.交集:A∩B                2.并集:AUB             ###\n");
	printf("\t###          3.补集:!A（AUB为全集）    4.补集:!B（AUB为全集）  ###\n");
	printf("\t###          5.差集:A-B                6.差集:B-A               ###\n");
	printf("\t###          7.重新输入集合            8.退出                  ###\n");
	printf("\t***------------------------------------------------------------***\n");
}

void inputSet(List& set) {
	ElemType* deal;
	int length;
	while (1) {
		string str;
		cin >> str;

		if (str.length() == 2) {
			deal = new string[0];
			length = 0;
			break;
		}

		int former = str.find("{");
		int later = str.find("}");
		int count_former = count(str.begin(), str.end(), '{');
		int count_later = count(str.begin(), str.end(), '}');
		int count_Elem = count(str.begin(), str.end(), ',') + 1;
		//检查输入合法性
		if (former != 0 || later != str.length() - 1 || count_former != 1 || count_later != 1) {
			cout << "输入有误:请重新输入:";
		}
		else {
			deal = new string[count_Elem];

			str[0] = ',';
			str[str.length() - 1] = ',';
			//提取元素 
			for (unsigned current = 0, next, i = 0; current < str.length() && i < count_Elem; i++) {
				next = str.find_first_of(',', current + 1);
				deal[i] = str.substr(current + 1, next - current - 1);
				current = next;
			}
			length = count_Elem;

			break;
		}
	}

	CreateSet(set, deal, length);
	delete[] deal;// 
}