#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node{
    int key;
    struct Node* left;
    struct Node* right;
};

void init(struct Node** node){
    *node = (struct Node*)malloc(sizeof(struct Node));
    (*node)->key = 0;
    (*node)->left = NULL;
    (*node)->right = NULL;
}

void construct(struct Node* root,struct Node** node_by_id,int w,int l,int r){
    root->key = w;
    if(l != -1){ 
        init(&root->left);
        node_by_id[l] = root->left;
    }
    if(r != -1){
        init(&root->right);
        node_by_id[r] = root->right;
    }
}
int count = 0;
void traverse(struct Node* root,int min,int max){
    if(!root) return;
    if(root->key>min && root->key<max) {
        count++;
        traverse(root->left,min,root->key);
        traverse(root->right,root->key,max);
    }
    else return;
}

// void free_tree(struct Node** root){
//     if(*root){
//         free_tree(&((*root)->left));
//         free_tree(&((*root)->right));
//         free(*root);
//     }
// }

int main(){
    freopen("testcase_hw2_p4.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N,w,l,r;
    scanf("%d", &N);
    struct Node** node_by_id = (struct Node**)malloc((N+1)*sizeof(struct Node*));
    struct Node* root;
    init(&root);
    node_by_id[1] = root;
    for(int i=1;i<=N;i++){
        scanf("%d%d%d",&w,&l,&r);
        construct(node_by_id[i],node_by_id,w,l,r);
        //printf("%d\n",node_by_id[i]->key);
    }
    traverse(root,INT_MIN,INT_MAX);
    printf("%d\n", count);

    //free_tree(&root);
    for(int i=1;i<=N;i++){
        free(node_by_id[i]);
        node_by_id[i] = NULL;
    }
    free(node_by_id);
    node_by_id = NULL;
    root = NULL;
    //printf("%d\n",root->key);
    //for(int i=1;i<=N;i++) printf("%d\n",node_by_id[i]->key);
    //printf("%d\n",(root->left)->key);
    return 0;
}