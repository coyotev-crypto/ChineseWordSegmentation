/*
程序的功能定义
*/
//欢迎
void welcome();
//菜单
void menue();
//加载字典
int load_dic(struct dict *dic,char *dic_path);

char* getword(char* src);
//词典预览
void printf_dic(struct dict *dic);
//正向匹配
struct dict* forwardMatching(struct dict *dic,char *content);
int participle(struct dict *dic,int parent_cmd);
struct dict* participle_matching(struct dict *dic,char *src,int cmd);
//逆向匹配
struct dict* backwardMatch(struct dict *dic,char *content);
//双向匹配
struct dict* bidirectionalMatching(struct dict *dic,char *content);

char* get_last_surplus_str(char *str,int size);

int count_single_char(struct dict *root);