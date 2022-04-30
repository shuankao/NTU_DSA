#include <stdio.h>
#include "generator.h"

int min(int a,int b){
    if(a<=b){
        return a;
    }
    else return b;
}

int max(int a,int b){
    if(a>=b){
        return a;
    }
    else return b;
}

int main(){
    generator.init();
    int t = generator.getT();
    while(t--){
        int n,*q,*p,*r;
        int ans = 0;
        generator.getData(&n,&p,&q,&r);
        for(int i=0;i<n-1;i++){
            for(int j=i+1;j<n;j++){
                if(p[i]==p[j] || q[i] == q[j] || r[i] == r[j]) ans++;
                else if(p[i]>p[j] && min(q[i],r[i])<=max(q[j],r[j])) ans++;
                else if(p[i]<p[j] && max(q[i],r[i])>=min(q[j],r[j])) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}