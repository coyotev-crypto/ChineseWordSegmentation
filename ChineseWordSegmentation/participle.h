/*
����Ĺ��ܶ���
*/
//��ӭ
void welcome();
//�˵�
void menue();
//�����ֵ�
int load_dic(struct dict *dic,char *dic_path);

char* getword(char* src);
//�ʵ�Ԥ��
void printf_dic(struct dict *dic);
//����ƥ��
struct dict* forwardMatching(struct dict *dic,char *content);
int participle(struct dict *dic,int parent_cmd);
struct dict* participle_matching(struct dict *dic,char *src,int cmd);
//����ƥ��
struct dict* backwardMatch(struct dict *dic,char *content);
//˫��ƥ��
struct dict* bidirectionalMatching(struct dict *dic,char *content);

char* get_last_surplus_str(char *str,int size);

int count_single_char(struct dict *root);