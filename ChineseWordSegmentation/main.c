#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "participle.h"
#include "linked_list.h"
#include <time.h>

int main(int argc,char *argv[]){
	char dic_path[200] = "CoreNatureDictionary.mini.gb2312.txt";
	struct dict *dic;         //字典
	struct dict *result_data; //分词结果
	int start_time,end_time; //加载时间
	char src[3];
	int cmd;   //命令
	dic = (struct dict*)malloc(sizeof(struct dict));
	dic->next = NULL;
	//加载字典
	welcome();
	menue();
	//加载字典
    load_dic(dic,dic_path);
	for(;;){
		printf("中文分词>");
		scanf("%d",&cmd);
		switch(cmd){
			case 1:
				printf("请输入字典路径：%s",&dic_path);
				load_dic(dic,dic_path);
				break;
			case 2:
				printfList(dic);
				break;
			case 3:
			case 4:
			case 5:
				participle(dic,cmd);
				//清除缓存
				fflush(stdin);
				break;
			case 0:
				exit(0);
			default:
				menue();
		}
	}
	system("pause");
	return 0;
}