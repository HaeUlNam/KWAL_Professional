//#include<iostream>
//using namespace std;
#define N_size 300
class Node {		//노드단위
public:
	char *data = nullptr;
	Node* next = nullptr;
	Node() {}
};
Node* nodes[N_size];

void init() {	//사이즈 300으로 픽스 및 초기화
	for (int i = 0; i < 300; i++)
	{
		Node init_node;
		*nodes[i] = init_node;
	}
}
int get_key(char *data) {		//문자열바탕으로 key 생성
	int a = (int)data;
	return a%300;
}

void insert(int buffer_size, char *buf) {		//추가
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

Node* search(int buffer_size, char *buf) {		//탐색
	int key = get_key(buf);
	if (nodes[key]->data == nullptr)
		return nullptr;		//못찾음
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
		return nullptr;	//못찾음
	}
}
bool delete_node(int buffer_size, char* buf) {		//탐색 함수를통한 삭제
	Node* delete_node = search(buffer_size, buf);
	if (delete_node == nullptr)
		return false;
	else
	{
		delete(delete_node);
		return true;
	}
}