//#include<iostream>
//using namespace std;

class Node {
public:
	char data;
	int count=0;
	Node* next[26] = { nullptr, };
	Node() {}
};
Node nodes[26];
void init(void) {

	for (int i = 0; i < 26; i++) {
		Node init_node;
		init_node.data = (char)(97 + i);
		
		nodes[i] = init_node;
	}
	/*for (int i = 0; i < 26; i++) init test
	{
		cout << nodes[i].data << endl;
	}*/
}
int get_key(char data) {
	int a = (int)data;
	return a - 97;
}
void insert(int buffer_size, char *buf) {
	char data = buf[0];
	Node* current_node = &nodes[get_key(data)];
	for (int i = 1; i < buffer_size; i++) {
		data = buf[i];
		if (current_node->next[get_key(data)] == nullptr) {
			Node* new_node=new Node();
			new_node->data = data;
			current_node->next[get_key(data)] = new_node;
		}
		current_node->count += 1;
		current_node = current_node->next[get_key(data)];
	}
	current_node->count += 1;
}

int query(int buffer_size, char *buf) {
	char data = buf[0];
	Node* current_node = &nodes[get_key(data)];
	for (int i = 1; i < buffer_size; i++) {
		data = buf[i];
		if (current_node->next[get_key(data)] == nullptr)
			return 0;
		current_node = current_node->next[get_key(data)];
	}
	return current_node->count;
}