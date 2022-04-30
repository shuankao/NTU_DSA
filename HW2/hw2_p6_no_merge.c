#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


struct Node{
    int line;
    int height;
    struct Node* prev;
    struct Node* next;
    // int from_line;
    // int to_line;
};

void init(struct Node** node,int h,int l){
    struct Node* tmp = malloc(sizeof(struct Node));
    tmp->height = h;
    tmp->line = l;
    tmp->prev = NULL;
    tmp->next = NULL;
    *node = tmp;
}

void construct_line_seq(struct Node** line_seq,struct Node** read_node,struct Node** tail){
    int i = (*read_node)->line;
    if(line_seq[i]){
        tail[i]->next = *read_node;
        (*read_node)->prev = tail[i];
    }
    else{
        line_seq[i] = *read_node;
    }
    tail[i] = *read_node;
}


struct Node* get_max_node(struct Node* head){
    struct Node* max_node = head;
    while(head != NULL){
        if(max_node->height < head->height){
            max_node = head;
        }
        head = head->next;
    }
    return max_node;
}

bool check_can_pop(struct Node** node,struct Node** line_seq,struct Node** tail){
    int l = (*node)->line;
    int h = (*node)->height;
    if(line_seq[l]){
        struct Node* max_node = get_max_node(line_seq[l]);
        if(*node == line_seq[l]){ //若node在該line的頭，則可pop
            printf("pop front: %d\n",h);
            struct Node* tmp = line_seq[l];
            line_seq[l] = line_seq[l]->next;
            free(tmp);
            if(line_seq[l]) line_seq[l]->prev = NULL;
            else tail[l] = NULL;
            *node = NULL;
            return true;
        } 
        else if(*node == tail[l]){ //若node在該line的尾，則可pop
            printf("pop back: %d\n",h);
            struct Node* tmp = tail[l];
            tail[l] = tail[l]->prev;
            free(tmp);
            if(tail[l]) tail[l]->next = NULL;
            else line_seq[l] = NULL;
            *node = NULL;
            return true; 
        } 
        else if(h == max_node->height) { //若node的高度為該line最大，則可pop
            printf("pop max: %d\n",h);
            if(max_node->next) (max_node->next)->prev = max_node->prev;
            if(max_node->prev) (max_node->prev)->next = max_node->next;
            free(max_node);
            *node = NULL;
            return true; 
        }
    }
    return false;
}

int main(){

    freopen("testcase_hw2_p6_1.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T,N,O,L;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d",&N,&O,&L);
        struct Node** read_seq = (struct Node**)malloc(N*sizeof(struct Node*));//存operations
        for(int i=0;i<O;i++){
            char s[10];
            int h,l,from_l,to_l;
            scanf("%s\n",s);
            if(!strcmp(s,"push")){
                scanf("%d%d",&h,&l);
                init(&read_seq[i],h,l);
            }
            else if(!strcmp(s,"merge")){
                scanf("%d%d",&from_l,&to_l);
            }
        }
        int* log = (int*)malloc(N*sizeof(int));//日誌
        for(int i=0;i<N;i++){
            scanf("%d",&log[i]);
        }
        struct Node** line_seq = calloc(L,sizeof(struct Node*));
        struct Node** tail = calloc(N,sizeof(struct Node*));
        int i=0,j=0,k=0;
        char res[11] = "possible";
        // construct_line_seq(line_seq,&read_seq[j++],tail);
        // printf("check_can_pop:%d\n",check_can_pop(read_seq,line_seq,tail));
        while(i<N){
            while(k<j){
                if(read_seq[k] && read_seq[k]->height == log[i]){
                    if(check_can_pop(&read_seq[k],line_seq,tail)){
                        //printf("can pop height: %d, log: %d\n",log[i],i);
                        i++;
                        k=0;
                        continue;
                    }
                    else {
                        strcpy(res,"impossible");
                        break;
                    }
                }
                k++;
            }
            if(j<N){
                construct_line_seq(line_seq,&read_seq[j],tail);
                //printf("construct %d times\n",j+1);
                j++;
                k=0; 
            }
            if(!strcmp(res,"impossible")){
                break;
            } 
        }
        printf("%s\n",res);

        free(read_seq);
        free(line_seq);
        free(tail);
        free(log);
        read_seq = NULL;
        line_seq = NULL;
        tail = NULL;
        log = NULL;
    }
    
    return 0;
}