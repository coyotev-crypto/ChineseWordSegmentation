#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "participle.h"
#include <time.h>

void welcome(){
	//输出welcome
	printf("\n");
	printf("***    ***    ***\n");
	printf(" **   ** **   **\n");
	printf("  ** **	  ** **\n");
	printf("   ***     ***\n");
	printf("    *       *\n");

}
//菜单
void menue(){
	printf("\n");
	printf(" ***********************\n");
	printf(" * 1、加载字典         *\n");
	printf(" * 2、词典预览         *\n");
	printf(" * 3、正向匹配查找     *\n");
	printf(" * 4、逆向匹配查找     *\n");
	printf(" * 5、双向匹配查找     *\n");
	printf(" * 0、退出             *\n");
	printf(" ***********************\n");
	printf("\n");
}
//加载字典
int load_dic(struct dict *dic,char *dic_path){
	FILE *fp;
	char line[64];
	char *word;
	int start_time,end_time; //加载时间
	fp = fopen(dic_path,"rb");
	if(!fp){
		printf("加载字典文件失败!\n");
		return 1;
	}
	clear(dic); //清除原先字典内容
	start_time = clock();
	while(fgets(line,64,fp) != NULL){
		word = getword(line);
		addList(dic,word);
	}	
	fclose(fp);
	end_time = clock();
	printf("字典加载成功%d毫秒\n\n",end_time-start_time);
	return 0;
}

char* getword(char* src){
	char *buff,*p;
	int index;
	p = strchr(src,9); /*找空格*/
	if(p != NULL)
	{
		index = p-src; /*计算长度*/
		buff = (char*)malloc(index+1);
		strncpy(buff,src,index);
		buff[index]='\0';
		return buff;
	}
	return NULL;
}

//词典预览
void printf_dic(struct dict *dic){
	printfList(dic);
}
/*
正向匹配
root 词典
content 待分词文本
return 分词结果
*/
struct dict* forwardMatching(struct dict *dic,char *content){
	int i = 0;
	int cp_len;             //拷贝字符串的长度 0~strlen(content)
	struct dict *dic_list;	//分词结果
	struct dict *new_node;  //新节点
	struct dict *last_dic;  //分词结果最后的节点
	char longest_word[20];  //最长匹配字符串
	char temp_word[20];        //临时存储查找的字符串
	dic_list = (struct dict*)malloc(sizeof(struct dict));
	dic_list->next = NULL;
	while(*content != '\0'){
		//拷贝5个字符
		//printf("字符长度%d\t",strlen(content));
		if(strlen(content) >= 10){
			memcpy(longest_word,content,10); 
			cp_len=10;
		}else{
			memcpy(longest_word,content,strlen(content)); 
			cp_len=strlen(content);
		}
		longest_word[cp_len]='\0'; //开始的字符
		//字典查找
		//最长字典为5个字符
		for(i = 0;i < strlen(longest_word);i+=2){
			memcpy(temp_word,content,cp_len);
			temp_word[cp_len]='\0';
			//printf("最长字符：%s\t字符：%s\n",longest_word,temp_word);
			if(getValue(dic,temp_word) == 1){
				//printf("找到分词结果：%s",temp_word);
				strcpy(longest_word,temp_word);
				break;
			}
			cp_len-=2;
		}
		//将查找到的串添加到链表中
		new_node = (struct dict*)malloc(sizeof(struct dict));
		new_node->next = NULL;
		strcpy(new_node->ch,longest_word);
		//尾插法
		last_dic = getLastDic(dic_list);
		last_dic->next = new_node;
		content+=strlen(longest_word);  //指针后移,分词剩余的单词
	}
	return dic_list;
}

struct dict* participle_matching(struct dict *dic,char *src,int cmd){
	struct dict *result_data;
	switch(cmd){
			case 3:
				result_data = forwardMatching(dic,src);
				break;
			case 4:
				result_data = backwardMatch(dic,src);
				break;
			case 5:
				result_data = bidirectionalMatching(dic,src);
				break;
	}
	return 	result_data;
}

int participle(struct dict *dic,int parent_cmd){
	int start_time,end_time;
	char *participle_paht;//待分词路径或文本 长度200
	char line[200];
	int cmd;  //1、输入分词路径  2、分词文本
	struct dict *result_data;
	char *word;
	FILE *fp;
	int index;
	char *p;
	participle_paht = (char*)malloc(sizeof(char)*200);
	printf("1、请输入分词文本文件路径\n");
	printf("2、请输入分词文本\n");
	printf("请选择>");
	scanf("%d",&cmd);
	//strcpy(participle_paht,"C:\\Users\\Administrator\\Desktop\\C语言期末作品\\abc.txt");
	printf(">");
	scanf("%s",participle_paht);
	if(cmd == 1){
		fp = fopen(participle_paht,"rb");
		if(!fp){		//打开文件
			printf("文件打开失败！\n");
			return 1;
		}
		start_time = clock();
		while(fgets(line,200,fp) != NULL){
			//一行行分词
			//去掉换行
			p = strchr(line,'\n'); /*找换行*/
			if(p != NULL){
				index = p - line;
				//-1 是因为前面还有一个字符
				line[index-1] = '\0';
			}
			result_data = participle_matching(dic,line,parent_cmd);
			printf_result(result_data);
		}	
		fclose(fp);
		end_time = clock();
		printf("分词成功%d毫秒\n\n",end_time-start_time);
		return 0;
	}else if(cmd == 2){
		start_time = clock();
		result_data = participle_matching(dic,participle_paht,parent_cmd);
		end_time = clock();
	}else{
		printf("\n参数错误！\n");
		return 1;
	}
	if(get_size(result_data) == 0){
			printf("分词失败%d毫秒\n\n",end_time-start_time);
	}else{
			printf_result(result_data);
			printf("分词成功%d毫秒\n\n",end_time-start_time);
	}
	return 0;
}
//逆向匹配
//通过指针的方式
struct dict* backwardMatch(struct dict *dic,char *content){
	struct dict *result_list;  //分割返回的字符串
	struct dict *new_node;  //新节点
	char *longest_word;  //最长匹配字符串
	int max_match_size = 5; //截取几个字符
	int i,j,k,str_len,l;
	int match_len = 5;
	int before = 0;
	char *temp_str;
	char *surplus_str;    //分词剩余的文本
	str_len = strlen(content);
	//初始化
	result_list = (struct dict*)malloc(sizeof(struct dict));
	result_list->next = NULL;
	surplus_str = (char*) malloc(sizeof(char)*str_len);
	strcpy(surplus_str,content);
	i = str_len >>1;
	//把整个文本分割
	while(i > 0){
		//从文本的后面截取5个中文字符
		//如果字符不够长截取剩余字符
		if(i > 5){
			longest_word = get_last_surplus_str(surplus_str,5); 
			match_len = 5;
		}else{
			longest_word = get_last_surplus_str(surplus_str,i); 
			match_len = i;
		}
		//遍历如果匹配不成功则减少一个汉字
		//printf("最长字符串：%s\t",longest_word);
			for(j = match_len;j >= 0; j--){
				//printf("%d\n",j);
				temp_str = get_last_surplus_str(surplus_str,j);
				//printf("%s\n",temp_str);
				if(getValue(dic,temp_str) == 1){
					strcpy(longest_word,temp_str);
					break;
				}
			}
			k = str_len - strlen(longest_word) - before;
			memcpy(surplus_str,content,k);
			surplus_str[k] = '\0';
			before+=strlen(longest_word);
			//将查找到的串添加到链表中
			new_node = (struct dict*)malloc(sizeof(struct dict));
			new_node->next = NULL;
			strcpy(new_node->ch,longest_word);
			//头插法
			new_node->next = result_list->next;
			result_list->next = new_node;
			match_len -= strlen(longest_word) >> 1;
			i -= strlen(longest_word) >> 1;
	}
	return result_list;
}

/*
char *str 截取的文本
int size  截取几个字符  中文字符*2
*/
char* get_last_surplus_str(char *str,int size){
	char *last_str;
	char *p_str;
	int offset;   //指针偏移量
	last_str = (char*)malloc(sizeof(char)*size*2+1);
	p_str = str;
	offset = strlen(str) - size*2;
	p_str += offset; //字符串指针后移
	memcpy(last_str,p_str,size*2);
	last_str[size*2]='\0';
	return last_str;
}

//双向匹配
struct dict* bidirectionalMatching(struct dict *dic,char *content){
	struct dict *forward;
	struct dict *backward;
	forward = forwardMatching(dic,content);
	backward=backwardMatch(dic,content);
	if(get_size(forward) < get_size(backward)){
		return forward;
	}else if(get_size(forward) > get_size(backward)){
		return backward;
	}else{
		//单字词更少的优先级更高
		if(count_single_char(forward) < count_single_char(backward)){
			return forward;
		}else{
			// 词数以及单字词数量都相等的时候，逆向最长匹配优先级更高
			return backward;
		}
	}
	return 0;
}

/*
统计单字词的个数
*/
int count_single_char(struct dict *root){
	struct dict *p;
	int sum = 0;
	p = root -> next;
	while(p != NULL){
		if(strlen(p->ch) == 2){
			sum++;
		}
		p = p->next;
	}
	return sum;

}