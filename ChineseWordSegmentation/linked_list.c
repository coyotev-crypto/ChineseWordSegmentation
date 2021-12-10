#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "participle.h"


int addList(struct dict *root,char *content){
	struct dict *dict;
	dict = (struct dict*)malloc(sizeof(struct dict));
	strcpy(dict->ch,content);
	dict->next = root->next;
	root->next = dict;
	return 0;
}

int getValue(struct dict *root,char *key){
	struct dict *p;
	p = root->next;
	while(p != NULL)
	{
		if(strcmp(p->ch,key)==0)
		{
			/*ÕÒµ½*/
			return 1;
		}
		p =  p->next;
	}
	return 0;
}


int clear(struct dict *root){
	struct dict *p;
	struct dict *del;
	p = root->next;
	while(p!=NULL){
		del = p;
		p = del->next;
		free(del);
	}
	root->next = NULL;
	return 0;
}

struct dict* getLastDic(struct dict *root){
	struct dict *p;
	struct dict *last_dict;
	p = root -> next;
	if(p == NULL){
		return root;
	}
	while(p != NULL){
		if(p != NULL){
			last_dict = p;
		}
		p = p->next;
	}
	return last_dict;
}

int printfList(struct dict *root){
	struct dict *p;
	p = root->next;
	/*Êä³ö´Êµä*/
	while(p != NULL){
		printf("%s\t",p->ch);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int printf_result(struct dict *root){
	struct dict *p;
	struct dict *last_dic;
	last_dic = getLastDic(root);
	p = root->next;
	/*Êä³ö´Êµä*/
	printf("\n[");
	while(p != NULL){
		if(p == last_dic){
			printf("'%s'",p->ch);
		}else{
			printf("'%s'£¬",p->ch);
		}
		p = p->next;
	}
	printf("]\n\n");
	return 0;
}


int get_size(struct dict *root){
	struct dict *p;
	int i = 0;
	p = root -> next;
	if(p == NULL){
		return 0;
	}
	while(p != NULL){
		i++;
		p = p->next;
	}
	return i;
}