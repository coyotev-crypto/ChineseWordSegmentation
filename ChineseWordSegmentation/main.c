#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "participle.h"
#include "linked_list.h"
#include <time.h>

int main(int argc,char *argv[]){
	char dic_path[200] = "CoreNatureDictionary.mini.gb2312.txt";
	struct dict *dic;         //�ֵ�
	struct dict *result_data; //�ִʽ��
	int start_time,end_time; //����ʱ��
	char src[3];
	int cmd;   //����
	dic = (struct dict*)malloc(sizeof(struct dict));
	dic->next = NULL;
	//�����ֵ�
	welcome();
	menue();
	//�����ֵ�
    load_dic(dic,dic_path);
	for(;;){
		printf("���ķִ�>");
		scanf("%d",&cmd);
		switch(cmd){
			case 1:
				printf("�������ֵ�·����%s",&dic_path);
				load_dic(dic,dic_path);
				break;
			case 2:
				printfList(dic);
				break;
			case 3:
			case 4:
			case 5:
				participle(dic,cmd);
				//�������
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