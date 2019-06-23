

class Node {
public:
	Node* left;
	Node* right;
	char data;
	Node(char data) {
		this->data = data;
	}
};


class Linklist {
private:
	Node* front;
	Node* back;
	int size = 0;
public:
	void insert(int n, char data){
		int ser;
		Node* search;
		if (size == 0) {
			search = new Node(data);
			front = search;
			back = search;
		}
		else if (n >= size) {
			search = new Node(data);
			search->left = back;
			back->right = search;
			back = search;
		}
		else if (size / 2 > n) {
			search = front;
			ser = 1;
			while (ser < n) {
				search = front->right;
				ser++;
			}
			Node* in = new Node(data);
			in->left = search;
			in->right = search->right;
			search->right->left = in;
			search->right = in;
		}
		else {
			search = back;
			ser = size;
			while (ser > n) {
				search = front->left;
				ser--;
			}
			Node* in = new Node(data);
			in->left = search;
			in->right = search->right;
			search->right->left = in;
			search->right = in;
		}
		size++;
	}
	void erase(int n) {
		int ser;
		Node* search;
		if (size == 0) {
			return;
		}
		else if (size == 1) {
			search = front;
			delete search;
		}
		else if (n >= size) {
			search = back;
			back = back->left;
			delete search;
		}
		else if (size / 2 > n) {
			search = front;
			ser = 1;
			while (ser < n) {
				search = front->right;
				ser++;
			}
			search->left->right = search->right;
			search->right->left = search->left;
			delete search;
		}
		else {
			search = back;
			ser = size;
			while (ser > n) {
				search = front->left;
				ser--;
			}
			search->left->right = search->right;
			search->right->left = search->left;
			delete search;
		}
		size--;
	}
	void clear() {
		while (back != front) {
			Node* del = back;
			back = back->left;
			delete del;
		}
		Node* del = back;
		delete del;
	}
	int getsize() {
		return size;
	}
};