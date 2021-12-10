struct dict{
	char ch[20];
	struct dict *next;
};

int addList(struct dict *root,char *content);

int getValue(struct dict *root,char *key);

struct dict* getLastDic(struct dict *root);

int printfList(struct dict *root);
int clear(struct dict *root);
int get_size(struct dict *root);
int printf_result(struct dict *root);