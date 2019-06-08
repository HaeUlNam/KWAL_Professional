//#include<iostream>
//using namespace std;
#define N_size 300
class Node {		//������
public:
	char *data = nullptr;
	Node* next = nullptr;
	Node() {}
};
Node* nodes[N_size];

void init() {	//������ 300���� �Ƚ� �� �ʱ�ȭ
	for (int i = 0; i < 300; i++)
	{
		Node init_node;
		*nodes[i] = init_node;
	}
}
int get_key(char *data) {		//���ڿ��������� key ����
	int a = (int)data;
	return a%300;
}

void insert(int buffer_size, char *buf) {		//�߰�
	int key = get_key(buf);
	Node* new_node = new Node();	new_node->data = buf;
	if(nodes[key]->data==nullptr){
		nodes[key] = new_node;
	}
	else {
		Node* current_node = nodes[key];
		while (current_node->next != nullptr)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

Node* search(int buffer_size, char *buf) {		//Ž��
	int key = get_key(buf);
	if (nodes[key]->data == nullptr)
		return nullptr;		//��ã��
	else {
		Node* current_node = nodes[key];
		if (current_node->data == buf)
			return current_node;
		while (current_node->next != nullptr)
		{
			if (current_node->data == buf)
				return current_node;
			current_node = current_node->next;
		}
		return nullptr;	//��ã��
	}
}
bool delete_node(int buffer_size, char* buf) {		//Ž�� �Լ������� ����
	Node* delete_node = search(buffer_size, buf);
	if (delete_node == nullptr)
		return false;
	else
	{
		delete(delete_node);
		return true;
	}
}