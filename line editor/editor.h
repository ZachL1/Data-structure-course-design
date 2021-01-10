#ifndef EDITOR_H_
#define EDITOR_H_

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <iomanip>
using namespace std;

/* 非成员函数-函数声明 */
// KMP算法
void getNext(const string& t, string::size_type next[]);
string::size_type KMP(const string& s, const string& t);

/* 数据结构 */
struct lineList {
public:
	lineList() {}

	using listType = list<string>;

	/* 成员函数-函数声明 */

	// 清空编辑器
	void clear() { L.clear(); line = 0; }
	// 编辑器是否为空
	bool empty() { return L.empty(); }

	// 存储文章
	istream& read(istream& in = cin);
	// 输出文章
	ostream& print(ostream& out = cout);

	// 统计英文字母数、数字数、空格数及总字数
	void word_count();
	// 统计某一字符串出现次数
	unsigned string_count(const listType::value_type t,
		unordered_map<listType::size_type, string>& smatch);

	// 删除某一子串的所有出现
	void remove_substr(listType::value_type remove_str);
	// 删除某一子串在指定行中的出现
	void remove_substr(listType::value_type remove_str,
		listType::size_type n);
	// 按行删除指定区间
	void remove_line(listType::size_type begin_line,
		listType::size_type end_line = 0);


	unsigned get_alpha() { return alpha; }
	unsigned get_digit() { return digit; }
	unsigned get_space() { return space; }
	unsigned get_word() { return word; }

private:
	listType L;
	listType::size_type line = 0;

	unsigned alpha = 0;
	unsigned digit = 0;
	unsigned space = 0;
	unsigned word = 0;

};

/* 用户交互界面处理函数-函数声明 */
void select();
// 输入文章
bool Input();
// 显示文章内容
bool Display();
// 统计文章内容
bool Statistic();
// 查找字符串，并统计出现次数
bool Lookup();
// 删除字符串
bool Deletestr();
// 删除行
bool Deletelin();
// 清空文章
bool Clearup();
// 保存文章
bool Save();
// 重新输入
bool Reenter();
// 清空输入区
void clear();


#endif // !EDITOR_H_