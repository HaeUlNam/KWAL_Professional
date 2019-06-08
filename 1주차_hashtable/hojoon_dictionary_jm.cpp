

class NodeType {
private:
	int size = 0;
	int count = 0;
	NodeType *array[27];
	char data;
public:
	NodeType(char data) {
		this->data = data;
		count++;
	}
	void countPlus() {
		count++;
	}
	void reset(){
		size = 0;
		count = 0;
	}
	void add(int buffer_size, int start, char data[]) {
		if (buffer_size== start) {
			return;
		}
		int check = 0;
		for (int i = 0; i < size; i++) {
			if (array[i]->data == data[start]) {
				array[i]->countPlus();
				check = 1;
				array[i]->add(buffer_size, start + 1, data);
				break;
			}
		}
		if (check == 0) {
			array[size] = new NodeType(data[start]);
			array[size]->add(buffer_size, start + 1, data);
			size++;
		}
	}
	int check(int buffer_size, int start, char buf[]) {
		if (buffer_size - 1 == start) {
			for (int i = 0; i < size; i++) {
				if (array[i]->data == buf[start]) {
					return array[i]->count;
				}
			}
			return 0;
		}
		for (int i = 0; i < size; i++) {
			if(array[i]->data==buf[start]){
				return array[i]->check(buffer_size, start + 1, buf);
			}
		}
		return 0;
	}

	void deletes() {
		for (int i = 0; i < size; i++) {
			array[i]->deletes();
			delete array[i];
		}
	}
};

NodeType start('a');

extern void init() {
	start.deletes();
	start.reset();
};

extern void insert(int buffer_size, char *buf) {
	start.add(buffer_size, 0, buf);
}

extern int query(int buffer_size, char *buf) {
	return start.check(buffer_size, 0,buf);
}
