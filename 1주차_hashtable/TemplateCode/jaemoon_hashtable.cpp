
const int PN = 23;
const int HASH_SIZE = 10000;

int name_size=0;
char name[30000][100];
int table[HASH_SIZE][30];

unsigned int get_key(char _name[]) {
	unsigned int key = 0, p = 1;
	for (int i = 0; _name[i] != 0; i++) {
		key += (_name[i] * p);
		p *= PN;
	}
	return (key%HASH_SIZE);
}

int my_strcmp(char a[], char b[]) {
	int i = 0;
	while (a[i]) {
		if (a[i] != b[i]) {
			break;
		}
		++i;
	}
	return(a[i] - b[i]);
}

int catain(unsigned int key, char _name[]) {
	int h_size = table[key][0];
	for (int i = 1; i <= h_size; ++i) {
		int n_pos = table[key][i];
		if (my_strcmp(name[n_pos], _name) == 0) {
			return n_pos;
		}
	}
	return -1;
}

void add(unsigned int key, char _name[]) {
	int len;
	for (len = 0; _name[len] != 0; ++len) {
		name[name_size][len] = _name[len];
	}
	name[name_size][len] = 0;

	int& h_size = table[key][0];
	table[key][++h_size] = name_size;

	++name_size;
}

void insert(unsigned int key, char _name[]) {
	int n_pos;
	n_pos = catain(key, _name);
	if (n_pos == -1) {
		add(key, _name);
	}
}

bool remove(unsigned int key ,char _name[]) {
	int& h_size = table[key][0];
	for (int i = 1; i <= h_size; ++i) {
		int n_pos = table[key][i];
		if (my_strcmp(name[n_pos], _name) == 0){
			for (int j = i + 1; j <= h_size; ++j) {
				table[key][j - 1] = table[key][j];
			}
			--h_size;
			return true;
		}
	}
	return false;
}
