#include"editor.h"


/* 成员函数-函数定义 */
// 静态存储文章
istream& lineList::read(istream& in)
{
	listType::value_type temp;
	// 存入当前行
	while (getline(in, temp)) {
		L.push_back(temp);
		++line;
	}

	return in;
}

// 输出文章
ostream& lineList::print(ostream& out)
{
	listType::size_type lcount = 0;
	listType::const_iterator it = L.cbegin();
	while (it != L.cend()) {
		//fprintf(out, "%3d. ", ++lcount);
		//if(out==cout)
		out << setw(2) << ++lcount << ". "; //输出显示行号以便操作
		out << *it++ << endl;
	}
	return out;
}

void lineList::word_count() {

	listType::const_iterator it = L.cbegin();
	while (it != L.cend()) {
		// 统计英文字母、数字和空格
		for (signed char i : *it) {
			if (isalpha(i))
				alpha++;
			else if (isdigit(i))
				digit++;
			else if (isspace(i))
				space++;
		}

		// 统计字数
		bool flag = false;
		for (signed char i : *it) {
			if (i == ' ')
				flag = false; //如果当前字符是空格，则使flag为false
			else if (!flag)
			{
				flag = true;
				word++;
			}
		}

		++it;
	}
}



// 统计字符串出现次数
unsigned lineList::string_count(const listType::value_type t, 
	unordered_map<listType::size_type, string> &smatch) {

	unsigned scount = 0; // 字符串出现次数
	listType::size_type lcount = 0; // 当前行
	// unordered_map<int, string> smatch; // 匹配子串所在行的行号和行内容构成的哈希map

	listType::value_type s;
	string::size_type kmp_index;
	listType::const_iterator it = L.cbegin();
	while (it != L.cend()) {
		++lcount;
		//s = *it; // 当前行字符串
		//kmp_index = string::npos; // 匹配子串在主串中的位置
		//								 
		//// 当前行中可能有多个子串匹配，
		//// 每次匹配成功后更改主串，继续匹配
		//while ((kmp_index = KMP(s, t)) != string::npos) {
		//	// 匹配到该子串，计数加一
		//	++scount;
		//	// 并将该行添加到哈希map中
		//	smatch.insert(make_pair(lcount, *it));

		//	// 更新主串
		//	if (kmp_index + t.length() < s.length()) 
		//		s = s.substr(kmp_index + t.length(), s.length() - (kmp_index + 1));
		//}

		kmp_index = 0; // 匹配子串在主串中的位置
		while ((kmp_index = (*it).find(t, kmp_index)) != string::npos) {
			// 匹配到该子串，计数加一
			++scount;
			// 并将该行添加到哈希map中
			smatch.insert(make_pair(lcount, *it));

			// 更新下次匹配位置
			if (kmp_index + t.length() < s.length())
				kmp_index += t.length();
			else
				break;
		}
		++it;
	}

	return scount;
}



// 删除某一子串
// 删除子串在全文的一切出现
void lineList::remove_substr(listType::value_type remove_str)
{
	
	listType::value_type::size_type kmp_index;
	listType::iterator it = L.begin();
	while (it != L.end()) {

		if (*it == remove_str) {
			// 如果要删除的字符串与当前行相同，直接删除整行
			L.erase(it);
		}
		else {
			// 否则从当前行匹配子串并删除
			//kmp_index = string::npos; // 匹配子串在主串中的位置
			//while ((kmp_index = KMP(*it, remove_str)) != string::npos) {
			//	(*it).erase(kmp_index, remove_str.length());
			//}

			kmp_index = 0; // 匹配子串在主串中的位置
			while ((kmp_index = (*it).find(remove_str, kmp_index)) != string::npos) {
				(*it).erase(kmp_index, remove_str.length());
				kmp_index = 0;
			}

		}
		++it;
	}
}
// 重载版本：删除子串在指定行的出现
void lineList::remove_substr(listType::value_type remove_str, 
	listType::size_type n)
{
	listType::size_type lcount = 0; // 当前行

	listType::value_type::size_type kmp_index;
	listType::iterator it = L.begin();
	while (it != L.end()) {
		// 如果当前行不是指定行，不做处理
		if (++lcount != n)
			continue;

		if (*it == remove_str) {
			// 如果要删除的字符串与当前行相同，直接删除整行
			L.erase(it);
		}
		else {
			// 否则从当前行匹配子串并删除
			//kmp_index = string::npos; // 匹配子串在主串中的位置
			//while ((kmp_index = KMP(*it, remove_str)) != string::npos) {
			//	(*it).erase(kmp_index, remove_str.length());
			//}

			kmp_index = 0; // 匹配子串在主串中的位置
			while ((kmp_index = (*it).find(remove_str, kmp_index)) != string::npos) {
				(*it).erase(kmp_index, remove_str.length());
			}
		}
		// 处理完毕，跳出循环
		if (lcount == n)
			break;

		++it;
	}
}

// 删除某一行
// 按行号删除
void lineList::remove_line(listType::size_type begin_line,
	listType::size_type end_line) {

	// 如果只有一个行号，即只删除一行
	if (end_line == 0)
		end_line = begin_line;
	listType::size_type lcount;
	listType::iterator it;
	for (it = L.begin(), lcount = 1; 
		it != L.end() && lcount <= end_line; ++lcount) {
		if (lcount >= begin_line)
			it = L.erase(it);
		else
			++it;
	}
}


/* 非成员函数-函数定义 */
// 利用修正的KMP算法查找子串
void getNext(const string& t, string::size_type next[]) {
	string::size_type j = 0, k = string::npos;
	next[0] = string::npos;
	while (j < t.length()) {
		if (k == string::npos || t.at(j) == t.at(k)) {
			++j;
			++k;
			if (t.at(j) != t.at(k))
				next[j] = k;
			else
				next[j] = next[k];
		}
		else
			k = next[k];
	}
}
/* 
 * KMP 模式匹配子串
 * 若匹配成功，返回第一次匹配主串位置
 * 匹配失败，返回 string::npos
 */
string::size_type KMP(const string& s, const string& t) {
//	/*string::size_type*/ int const max_size = max(s.length(), t.length());
	string::size_type next[80];
	string::size_type i=0, j=0;
	getNext(t, next);
	while (i < s.length() && j < t.length()) {
		if (j == string::npos || s.at(i) == t.at(j)) {
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j >= t.length())
		return i - t.length();
	else
		return string::npos;
}



//void strcount(lineList*& lList, const string& str) {
//	// 统计英文字母、数字和空格
//	for (const char& i : str) {
//		if (isalpha(i))
//			lList.alpha++;
//		else if (isdigit(i))
//			lList.digit++;
//		else if (isspace(i))
//			lList.space++;
//	}
//
//	// 统计字数
//	bool flag = false;
//	for (const char& i : str) {
//		if (i == ' ') 
//			flag = false; //如果当前字符是空格，则使flag为false
//		else if (!flag)
//		{
//			flag = true;
//			lList.word++;
//		}
//	}
//}