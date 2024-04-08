#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char* ECO;
	char* name;
	char* move;
	int childnum;
	struct node* child[20];
};

int size = 0;

void split(char* arr, char** answer){
    char* token = strtok(arr, " ");
	int i=0;
    while(token != NULL){
		answer[i] = token;
        token = strtok(NULL, " ");
		i++;
    }
	answer[i-1] = strtok(answer[i-1], "\n");
    size = i;
}

struct node* createNode(char* ECO, char* name, char* move){
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    for(int i=0; i<20; i++){
        temp->child[i] = NULL;
    }
    temp->childnum = 0;
}

void display(struct node* head){
    if(head==NULL){
        return;
    }
    for(int i=0; i<head->childnum; i++){
        printf("ECO: %s;", head->child[i]->ECO);
        printf("name:%s;", strtok(head->child[i]->name, "\t"));
        printf("move: %s\n", head->child[i]->move);
        display(head->child[i]);
    }
}

void push(char* ECO, char* name, char** move, struct node* head){
    struct node* temp = head;
    for(int i=0; i<size; i++){
        int j;
        for(j=0; j<=temp->childnum; j++){
            if(temp->child[j] == NULL){
                break;
            }
            if(strcmp(temp->child[j]->move, move[i]) == 0 || strcmp(temp->child[j]->move, move[i]) == 13){
                break;
            }
        }
        if(temp->child[j]==NULL){
            temp->child[j]=createNode(ECO, name, move[i]);
            temp->childnum++;
            temp->child[j]->move = strdup(move[i]);
            temp->child[j]->ECO = strdup(ECO);
            temp->child[j]->name = strdup(name);
        }
        temp = temp->child[j];
    }
}

void search(char** move, struct node* head){
    struct node* temp = head;
    char* ECO = "A00";
    char* name = "Flank Openings";
    for(int i=0; i<size; i++){
        int j;
        for(j=0; j<=temp->childnum; j++){
            if(temp->child[j] == NULL){
                break;
            }
            if(strcmp(temp->child[j]->move, move[i]) == 0 || strcmp(temp->child[j]->move, move[i]) == 13){
                break;
            }
        }
        if(temp->child[j]==NULL){
            break;
        }
        ECO = temp->child[j]->ECO;
        name = temp->child[j]->name;
        temp = temp->child[j];
    }
    ECO = temp->ECO;
    printf("ECO is %s\n", ECO);
    name = temp->name;
    printf("Name is%s\n", name);
}

void main(){
    struct node* head = malloc(sizeof(struct node));
    head->ECO = "A00";
    head->name = " Flank Openings";
    char** move = (char**)malloc(250);
    for(int i=0; i<20; i++){
        head->child[i] = NULL;
    }
    head->childnum = 0;

	FILE* fp = fopen("openings1.txt", "r");
	
	if (fp==NULL){
		printf("Can't open file\n");
	}
	else{
		char buffer[1024];
        char* token1;
        char* token2;
        char* token3;
		for(int i=0; i<500; i++){
            fgets(buffer, 1024, fp);
            token1 = strtok(buffer, ";");
            printf("%s\n",  token1);
            token2 = strtok(NULL, ";");
            printf("%s\n",  token2);
            token3 = strtok(NULL, ";");
            printf("%s",  token3);
            split(token3, move);
            push(token1, token2, move, head);
		}
		fclose(fp);
	}
    // display(head);
    char** answer = (char**)malloc(250);
    char* input;
    printf("\nEnter your move: ");
    scanf("%[^\n]s", input);
    split(input, answer);
    search(answer, head);
}
