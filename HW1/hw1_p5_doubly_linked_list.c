#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
    int l;
    struct Node* next;
    struct Node* prev;
};

void enter(int _l, struct Node** head, struct Node** tail){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->l = _l;
    if(!(*head)){
        *head = newNode;
        *tail = newNode;
        newNode->prev = NULL;
    }
    else{
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = (*tail)->next;
    }
    newNode->next = NULL;
    //printf("%d\n",(*tail)->l);
}

void leave(struct Node** tail){
    *tail = (*tail)->prev;
    free((*tail)->next);
    (*tail)->next = NULL;
    //printf("%d\n", (*tail)->l);
}

void migrate(struct Node** heada, struct Node** headb,struct Node** taila, struct Node** tailb){
    if(*taila && *tailb){
        (*taila)->next = *tailb;
        (*tailb)->next = *taila;
        *tailb = *heada;
    } 
    else if(*tailb == NULL && *taila){
        *headb = *taila;
        *tailb = *heada;
    }
    *heada = NULL;
    *taila = NULL;
}

void print_map(struct Node* head){
    if(head && head->prev && !head->next){
        while(head){
            printf("%d ",head->l);
            head = head->prev;
        }
    }
    while(head){
        printf("%d ", head->l);
        if(head->next && head == (head->next)->next){
            break;
        }
        head = head->next;
    }
    if(head) head = head->next;
    while(head){
        printf("%d ", head->l);
        head = head->prev;
    }
}

int main(){
    int k,n;
    char input[10];
    int r,l,ra,rb;

    freopen("testcase_hw1_p5.txt","r",stdin);
    freopen("output.txt","w",stdout);

    scanf("%d%d",&k,&n);
    struct Node** head = (struct Node**)calloc((k),sizeof(struct Node*));
    struct Node** tail = (struct Node**)calloc((k),sizeof(struct Node*));
    for(int i=0;i<n;i++){
        scanf("%s", input);
        if(strcmp(input,"enter")==0){
            scanf("%d%d", &r,&l);
            if(r<k) enter(l,&head[r],&tail[r]);
        }
        else if(strcmp(input,"leave")==0){
            scanf("%d", &r);
            if(r<k && tail[r]!=NULL){
                leave(&tail[r]);
            }
        }
        else if(strcmp(input,"migrate")==0){
            scanf("%d%d", &ra,&rb);
            if(ra!=rb && ra<k && rb<k){
                migrate(&head[ra],&head[rb],&tail[ra],&tail[rb]);
            }
        }
    }

    for(int i=0;i<k;i++){
        if(!head[i]){
            printf("\n");
        }
        else{
            print_map(head[i]);
            printf("\n");
        }
    }

    for(int i=0;i<k;i++){ //node一個一個free
        struct Node* tmp = head[i];
        if(tmp && tmp->prev && !tmp->next){
            while(tmp){
                tmp = tmp->prev;
                free(head[i]);
                head[i] = tmp;
            }
        }
        while(tmp){
            if(tmp->next && tmp == (tmp->next)->next){
                break;
            }
            tmp = tmp->next;
            free(head[i]);
            head[i] = tmp;
        }
        if(tmp) {
            tmp = tmp->next;
            free(head[i]);
            head[i] = tmp;
        }
        while(tmp){
            tmp = tmp->prev;
            free(head[i]);
            head[i] = tmp;
        }
    }

    free(head);
    free(tail); //free陣列
 
}