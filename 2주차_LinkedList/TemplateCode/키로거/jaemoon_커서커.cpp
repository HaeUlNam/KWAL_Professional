#include<iostream>
using namespace std;
#include<string>;

class Node {
public:
	Node *left;
	Node *right;
	char data;
	Node() {}
	Node(char data) {
		this->data = data;
	}
};
class Linklist {
private:
	Node* prev;
	Node* back;
	Node* cur;
public:
	Linklist() {
		Node *n = new Node(); //리스트생성시 초기 노드값 생성 아무것도 안들어간다(커서맨앞일때의 역활)
		prev = n;
		back = n;
		cur = n;
	}
	void insert(char data) {
		Node *a = new Node(data);
		if (cur == back) { //맨뒤에서 삽입경우
			a->left = cur;
			cur->right = a;
			cur = a;
			back = a;
		}
		else {  //나머지삽입경우
			a->left = cur;
			a->right = cur->right;
			cur->right = a;
			a->right->left = a;
			cur = a;
		}
	}
	void backcur() {//왼쪽쉬프트
		if (prev != cur) {
			cur = cur->left;
		}
	}
	void forwardcur() {//우측쉬프트
		if (back != cur) {
			cur = cur->right;
		}
	}
	void erase() {
		Node* del;
		if (cur == prev) { //커서가 맨앞일때
			return;
		}
		else if (cur == back) {//커서 맨뒤
			del = cur;
			cur = cur->left;
			back = back->left;
			delete del;
		}
		else { //나머지 경우
			del = cur;
			cur = cur->left;
			cur->right = del->right;
			del->right->left = cur;
			delete del;
		}
	}
	void print() {
		Node* c = prev->right;
		while (c != back) {
			cout << c->data;
			c = c->right;
		}
		cout << c->data;
	}
	void clear() {
		while (back != prev) {
			Node* del = back;
			back = back->left;
			delete del;
		}
		delete back;
	}
};



int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		string a;
		cin >> a;
		int size = a.size();
		int j = 0;
		Linklist n;
		for (j; j < size; j++) {
			switch (a[j])
			{
			case '<':
				n.backcur();
				break;
			case '>':
				n.forwardcur();
				break;
			case '-':
				n.erase();
				break;
			default:
				n.insert(a[j]);
				break;
			}
		}
		n.print();
		cout << endl;
		n.clear();
	}
	return 0;
}