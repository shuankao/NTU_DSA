#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node{
    int l;
    struct Node* next;
};

void enter(int _l, struct Node** head){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->l = _l;
    newNode->next = *head;
    *head = newNode;
    //printf("%d\n",(*head)->l);
}

void leave(struct Node** head){
    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    //printf("%d\n", (*head)->l);
}

void reverse(struct Node** head);

void migrate(struct Node** heada, struct Node** headb){
    
    reverse(heada);
    // while(*heada){
    //     printf("%d ", (*heada)->l);
    //     *heada = (*heada)->next;
    // }
    struct Node* temp = *heada;
    while(temp && temp->next){
        temp = temp->next;
    }
    if(temp){
        temp->next = *headb;
        *headb = *heada;
        *heada = NULL;
    }

    // while(*headb){
    //     printf("%d ", (*headb)->l);
    //     *headb = (*headb)->next;
    // }
}

void reverse(struct Node** head){
    struct Node* cur = NULL;
    struct Node* prev = NULL;
    while(*head){
        prev = cur;
        cur = *head;
        *head = (*head)->next;
        cur->next = prev;   
    }
    *head = cur;
}

void print_reverse(struct Node* head){
    if(head->next){
      print_reverse(head->next);
    }
    printf("%d ",head->l);
}

int main(){

    // freopen("testcase_hw1_p5.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    int k,n;
    char input[10];
    int r,l,ra,rb;
    scanf("%d%d",&k,&n);
    struct Node** head = (struct Node**)calloc((k),sizeof(struct Node*));

    for(int i=0;i<n;i++){
        scanf("%s", input);
        if(strcmp(input,"enter")==0){
            scanf("%d%d", &r,&l);
            if(r<k) enter(l,&head[r]);
        }
        else if(strcmp(input,"leave")==0){
            scanf("%d", &r);
            if(r<k && head[r]!=NULL){
                leave(&head[r]);
            }
        }
        else if(strcmp(input,"migrate")==0){
            scanf("%d%d", &ra,&rb);
            if(ra!=rb && ra<k && rb<k){
                migrate(&head[ra],&head[rb]);
            }
        }
    }
    
    for(int i=0;i<k;i++){
        if(!head[i]){
            printf("\n");
        }
        else if(head[i]->next){
            print_reverse(head[i]->next);
            printf("%d", head[i]->l);
            printf("\n");
        }
        else{
            printf("%d", head[i]->l);
            printf("\n");
        }
    }

    for(int i=0;i<k;i++){ //node一個一個free
        struct Node* tmp = head[i];
        while(tmp){
            tmp = tmp->next;
            free(head[i]);
            head[i] = tmp;
        }
    }
    free(head);//free陣列
}