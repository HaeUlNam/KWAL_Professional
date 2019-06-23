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
		Node *n = new Node(); //����Ʈ������ �ʱ� ��尪 ���� �ƹ��͵� �ȵ���(Ŀ���Ǿ��϶��� ��Ȱ)
		prev = n;
		back = n;
		cur = n;
	}
	void insert(char data) {
		Node *a = new Node(data);
		if (cur == back) { //�ǵڿ��� ���԰��
			a->left = cur;
			cur->right = a;
			cur = a;
			back = a;
		}
		else {  //���������԰��
			a->left = cur;
			a->right = cur->right;
			cur->right = a;
			a->right->left = a;
			cur = a;
		}
	}
	void backcur() {//���ʽ���Ʈ
		if (prev != cur) {
			cur = cur->left;
		}
	}
	void forwardcur() {//��������Ʈ
		if (back != cur) {
			cur = cur->right;
		}
	}
	void erase() {
		Node* del;
		if (cur == prev) { //Ŀ���� �Ǿ��϶�
			return;
		}
		else if (cur == back) {//Ŀ�� �ǵ�
			del = cur;
			cur = cur->left;
			back = back->left;
			delete del;
		}
		else { //������ ���
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