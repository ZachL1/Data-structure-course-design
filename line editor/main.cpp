#define _CRT_SECURE_NO_WARNINGS
#include "editor.h"
#include <fstream>
#include <cstdio>

using namespace std;

lineList line_editor;

int main() {

	printf("\t                   简单行编辑器               \n");
	printf("\t                    使用说明                 \n");

	//select();
	int choose = 1;
	//cin >> choose;
	while (choose) {
		select();
		cin >> choose; 
		//clear();
		if (choose >= 2 && choose <= 8 && line_editor.empty()) {
			cout << "\n请先输入文章！\n";
			continue;
		}

		switch (choose)
		{
		case 1:
			if (Input()) {
				cout << "\n文章输入完成，请继续操作：\n";
				//select();
				//cin >> choose; clear();
			}
			else{
				cout << "\n输入失败，请重新操作:\n";
				line_editor.clear();
				//select();
				//cin >> choose; clear();
			}
			break;

		case 2:
			if (!line_editor.empty() && Display()) {
				cout << "\n输出完成，请继续操作: \n";
				//select();
			}
			break;

		case 3:
			if (!line_editor.empty() && Statistic()) {
				cout << "\n统计完成，请继续操作: \n";
				//select();
			}
			break;

		case 4:
			if (Lookup()) {
				cout << "\n查找完成，请继续操作:\n";
			}
			else
				cout << "\n查找失败，请重新操作\n";
			break;

		case 5:
			if (Deletestr()) {
				cout << "\n删除完成，请继续操作\n";
			}
			else
				cout << "\n删除失败，请重新操作\n";
			break;

		case 6:
			if (Deletelin()) {
				cout << "\n删除完成，请继续操作\n";
			}
			else
				cerr << "\n删除失败！请重新操作\n";
			break;

		case 7:
			if (Clearup()) {
				cout << "\n清空完成，请继续操作\n";
			}
			break;

		case 8:
			if (Save()) {
				cout << "\n保存完成，请继续操作\n";
			}
			else
				cout << "\n保存失败，请重新操作\n";
			break;

		case 9:
			if (Reenter()) {
				cout << "\n已清空编辑器，请重新输入文章: \n";
				if (Input()) {
					cout << "\n文章输入完成，请继续操作：\n";
				}
				else {
					cout << "\n输入失败，请重新操作:\n";
				}
			}
			break;
		case 0:
			break;
		default:
			cerr << "\n错误指令，请输入 0~9 的整数！\n";
			break;
		}
		
	}

	cout << "\n谢谢使用!" << endl;
	return 0;
}

/* 用户交互界面处理界面-函数定义 */

void select() {
	printf("\t***---------------------------------------------***\n");
	printf("\t###  请选择: 1.输入文章         2.显示文章内容  ###\n");
	printf("\t###          3.统计文章内容     4.查找字符串    ###\n");
	printf("\t###          5.删除字符串       6.删除行        ###\n");
	printf("\t###          7.清空文章         8.保存文章      ###\n");
	printf("\t###          9.重新输入         0.退出          ###\n");
	printf("\t***---------------------------------------------***\n");
}


// 输入文章
bool Input() {
	int choose;
	string file_way;
	ifstream infile;
	cout 
		<< "-->输入文章，请选择：" << endl
		<< "---->1. 键盘输入" << endl
		<< "---->2. 文件输入" << endl;
	cin >> choose;
	clear();
	switch (choose)
	{
	case 1:
		cout << "-->请输入文章 输入 <Ctrl+Z> 以结束输入：" << endl;
		line_editor.read();
		cin.clear();
		cin.eof();
		break;
	case 2:
		cout << "-->请输入文件名，如 <readme.txt> ：";
		cin >> file_way;
		infile.open(file_way);
		if (!infile) {
			cerr << "\n糟糕！没有成功打开文件。请检查文件名和路径是否正确！\n";
			return false;
		}
		else {
			cout << "\n成功打开文件，将从文件中读取文章....." << endl;
			line_editor.read(infile);
		}
		break;
	default:
		cerr << "\n错误输入！请输入数字 1 或 2 ！" << endl;
		return false;
		break;
	}
	//cout << "文章输入完成，请继续操作：\n";
	return true;
}

// 显示文章内容
bool Display() {
	line_editor.print();
	return true;
}

// 统计文章内容
bool Statistic() {
	int choose;
	line_editor.word_count();

	cout 
		<< "-->统计文章内容，请选择：" << endl
		<< "---->1. 统计全部字母数" << endl
		<< "---->2. 统计数字个数" << endl
		<< "---->3. 统计空格个数" << endl
		<< "---->4. 统计文章总字数" << endl
		<< "---->5. 统计以上全部" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
		cout << "\n本篇文章中，全部字母数为: " << line_editor.get_alpha() << endl;
		break;
	case 2:
		cout << "\n本篇文章中，数字个数为: " << line_editor.get_digit() << endl;
		break;
	case 3:
		cout << "\n本篇文章中，空格个数为: " << line_editor.get_space() << endl;
		break;
	case 4:
		cout << "\n本篇文章中，总字数为: " << line_editor.get_word() << endl;
		break;
	case 5:
		cout 
			<< "\n本篇文章中，全部字母数为: " << line_editor.get_alpha() << endl
			<< "              数字个数为: " << line_editor.get_digit() << endl
			<< "              空格个数为: " << line_editor.get_space() << endl
			<< "                总字数为: " << line_editor.get_word() << endl;
		break;
	default:
		cerr << "\n错误输入！请输入数字 1 ~ 5 ！" << endl;
		return false;
		break;
	}
	return true;
}

// 查找字符串，并统计出现次数
bool Lookup() {
	string str;
	unsigned scount = 0;
	char choose;
	unordered_map<list<string>::size_type, 
		string> smatch; // 匹配子串所在行的行号和行内容构成的哈希map
	
	cout << "-->请输入要查找的字符串: " << endl;
	cin >> str;
	if (str.length() > 80) {
		cerr << "\n糟糕！查找的字符串太长啦！";
		return false;
	}

	scount = line_editor.string_count(str, smatch);
	cout << "\n字符串 " + str + " 在整篇文章中出现了" << scount << "次！" << endl;

	cout << "\n您想显示它们的具体位置吗？(y/n): ";
	cin >> choose; clear();

	while (choose != 'y' && choose != 'n' && choose != 'Y' && choose != 'N') {
		cerr << "-->请输入 y/Y 或 n/N : ";
	}

	if (choose == 'y' || choose == 'Y') {
		cout << "\n字符串 " + str + " 出现了" << scount << "次，如下: " << endl;
		unordered_map<list<string>::size_type, string>::const_iterator it
			= smatch.cbegin();
		while (it != smatch.cend()) {
			cout << "   第" << it->first << "行: " + it->second << endl;
			++it;
		}
	}
	return true;
}

// 删除字符串
bool Deletestr() {
	int choose;
	string delestr;
	list<string>::size_type lin;

	cout
		<< "-->删除字符串，请选择：" << endl
		<< "---->1. 删除文章中所有出现" << endl
		<< "---->2. 删除指定行中的出现" << endl;
	cin >> choose; clear();
	cout << "\n请输入要删除的字符串: ";
	cin >> delestr;

	switch (choose)
	{
	case 1:
		line_editor.remove_substr(delestr);
		break;
	case 2:
		cout << "-->请输入行号: ";
		cin >> lin;
		line_editor.remove_substr(delestr, lin);
		break;
	default:
		cerr << "\n错误输入，请输入数字 1 或 2 ! " << endl;
		return false;
		break;
	}
	return true;
}

// 删除行
bool Deletelin() {
	list<string>::size_type beg, end=0;

	cout << "-->请输入要删除的行区间[m,n]，m 必须小于等于 n，例如 <4,5> <6,6> : ";
	if (scanf("%lu,%lu", &beg, &end) != 2) {
		cerr << "\n错误输入，请输入区间[m,n]，m小于等于n ! " << endl;
		clear();
		return false;
	}

	line_editor.remove_line(beg, end);
	return true;
}

// 清空文章
bool Clearup() {
	line_editor.clear();
	return true;
}

// 保存文章
bool Save() {
	string file_way;

	cout << "-->请输入保存文件名 如<writeme.txt> ：";
	cin >> file_way;
	ofstream outfile(file_way);
	if (!outfile) {
		cerr << "\n糟糕！没有成功打开文件。请检查文件名和路径是否正确！\n";
		return false;
	}
	else {
		cout << "\n成功打开文件，正在将文章保存到文件....." << endl;
		line_editor.print(outfile);
	}
	return true;
}

// 重新输入
bool Reenter() {
	line_editor.clear();
	return true;
}


// 冲洗缓冲区
void clear() {
	while (getchar() != '\n')
		continue;
}