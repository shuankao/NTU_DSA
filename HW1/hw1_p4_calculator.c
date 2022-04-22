#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define INPUT_SIZE 1000000


void input_processing(char* _input, size_t _size);
int check_priority(char a, char b);
void double_push(double x);
void char_push(char x);
double double_pop();
char char_pop();
int int_top = 0, char_top = 0;
double calculate();
double double_arr[INPUT_SIZE];//存數字
char char_arr[INPUT_SIZE];//存運算符號
int char_arr_len, double_arr_len;
double* double_p;//int stack
char* char_p;//char stack

int main(){
    char input[INPUT_SIZE];
    
    while(scanf("%s", input)!=EOF){
        
        input_processing(input,strlen(input));
        
        char_p = (char*)malloc(char_arr_len*sizeof(char));
        double_p = (double*)malloc(double_arr_len*sizeof(double));

        double res = 0;
        int j = 0;
        // for(int i = 0; i < double_arr_len; i++){
        //     printf("%lf ", double_arr[i]);
        // }
        for(int i = 0; i < double_arr_len; i++){
            if(i < double_arr_len){
                double_push(double_arr[i]);
            }
            if(j < char_arr_len){
                if(char_arr[j] == '('){
                    char_push(char_arr[j]);
                    j++;
                }
                else if(char_arr[j]  == ')'){
                    while(char_p[char_top-1] != '('){
                        
                        res = calculate();
                        double_push(res);
                        //printf("%lf ", res);
                    }
                    char_pop(); // pop '('
                    j++;
                }
                if(j < char_arr_len){
                    if( char_top == 0 || check_priority(char_p[char_top-1], char_arr[j])){
                        char_push(char_arr[j]);
                        
                    }
                    else{
                        while(char_top > 0 && !check_priority(char_p[char_top-1], char_arr[j])){
                            res = calculate();
                            double_push(res);
                        }
                        char_push(char_arr[j]);
                        
                    }
                }
                
                // for(int k = 0; k < int_top; k++){
                //     printf("%lf ", double_p[k]);
                // }
                // printf("\n");
                
                j++;
               
                // if(i<strlen(char_arr)-1 && char_arr[i+1] == '('){
                // char_push(char_arr[i+1]);
                // i++;
                // }
                // else if(char_arr[i] == ')'){
                //     while(char_pop() != '('){
                //         int res = calculate();
                //         double_push(res);
                //     }
                // }
            }
            
        }
        
        while(char_top > 0){
            res = calculate();
            double_push(res);
            
        }
        printf("%.15lf ", res);
        // for(int i = 0; i < char_top; i++){
        //     printf("%c ", char_p[i]);
        // }
        

        memset(input,'0', strlen(input)); //clear char array
        free(double_p);
        free(char_p);
    }
    return 0;
}

void input_processing(char* _input, size_t _size){
    int arr[9];//整數最多10^8-1，為八位數
    int j = 0, num = 0, m = 0, n = 0;
    for(int i = 0; i < _size; i++){
        if(isdigit(_input[i])){
            arr[j] = _input[i]-'0';
            j++;
        }
        else{ //運算子存入char_arr[]
            char_arr[n] = _input[i];
            n++;
            if(_input[i] == '(' || _input[i] == ')') continue;
            for(int k = 0; k < j; k++){//運算子前面的所有連續digits合成一整數
                num = num*10 + arr[k];
            }
            //整數存入double_arr[]
            double_arr[m] = num;
            m++;
            num = 0;
            //清掉buffer arr[]以讀取下一整數
            for(int k = 0; k < j; k++){
                arr[k] = 0;
            }
            j = 0;
        }
    }
    for(int k = 0; k < j; k++){//處理最後一個整數
        num = num*10 + arr[k];
    }
    //整數存入double_arr[]
    double_arr[m] = num;
    m++;
    char_arr_len = n;
    double_arr_len = m;
}

void double_push(double x){
    double_p[int_top] = x;
    int_top++;
}

void char_push(char x){
    
    char_p[char_top] = x;
    char_top++;
}

double double_pop(){
    int_top--;
    return double_p[int_top];
    
}

char char_pop(){
    char_top--;
    return char_p[char_top];
    
}

int check_priority(char a, char b){ //return true if priority a < b
    int temp1, temp2;
    switch(a){
        case '+': temp1 = 1; break;
        case '-': temp1 = 1; break;
        case '*': temp1 = 2; break;
        case '/': temp1 = 2; break;
        case '(': temp1 = 0; break;
    }
    switch(b){
    case '+': temp2 = 1; break;
    case '-': temp2 = 1; break;
    case '*': temp2 = 2; break;
    case '/': temp2 = 2; break;
    case '(': temp2 = 0; break;
    }
    if(temp1 < temp2) return 1;
    else return 0;

}

double calculate(){
    char exp = char_pop();
    double top1 = double_pop();
    double top2 = double_pop();
    double temp = 0;
    switch(exp){
        case '+': temp = top2 + top1; break;
        case '-': temp = top2 - top1; break;
        case '*': temp = top2 * top1; break;
        case '/': temp = top2 / top1; break;
    }
    //printf("%lf %lf %lf ", top2, top1, temp);
    return temp;
}
