//#include<iostream>
//using namespace std;

class Node {	//노드 하나하나가 알파벳 단어 하나 즉 'abcd'인 경우 'a'->'b'->'c'->'d'로 구성
public:		//여기서 'abcd'와 'abcde'가 있는 경우 'a'->'b'->'c'->'d'->'e'로 만들어지고(a,b,c,d count가 2개, e는 count가 1)
	char data;
	int count=0;
	Node* next[26] = { nullptr, };
	Node() {}
};
Node nodes[26];
void init(void) {	//해시는 알파벳이 무엇으로 시작하냐로 처음에 나눔 a~z까지 총 26

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
int get_key(char data) {	//알파벳 넣으면 그에 따른 idnex 리
	int a = (int)data;
	return a - 97;
}
void insert(int buffer_size, char *buf) {		//값 없는경우(nullptr인 경우) 새 노드 만들어서 추가 이 때, new()안쓰면 주소값 문제 발
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

int query(int buffer_size, char *buf) {		//buf단어 위치까지찾아감 해당 값의 count가 해당 단어를 prefix로 포함하는 단어의 수.
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
