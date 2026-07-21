#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=0;i<=n;i++){
        cin>>a[i];
    }
    reverse(a.begin(), a.end());
    for(int i=n;i>0;i--){
        if(a[i]==0) continue;
        if(a[i]>0){
            if(i==n){
                if(a[i]==1){
                    if(i==1) printf("x");
                    else printf("x^%d",i);
                }
                else{
                    if(i==1) printf("%dx",a[i]);
                    else printf("%dx^%d",a[i],i);
                }
            }
            if(i!=n){   
                if(a[i]==1){
                    if(i==1) printf("+x");
                    else printf("+x^%d",i);
                }
                else{
                    if(i==1) printf("+%dx",a[i]);
                    else printf("+%dx^%d",a[i],i);
                }
            }
        }

        if(a[i]<0){
            if(a[i]==-1){
                if(i==1) printf("-x");
                else printf("-x^%d",i);
            }
            else{
                if(i==1) printf("%dx",a[i]);
                else printf("%dx^%d",a[i],i);
            }
        }
    }
    if(n!=0){
        if(a[0]==0) return 0;
        else if(a[0]>=0) printf("+%d",a[0]);
        else printf("%d",a[0]);
    }
    else{
        printf("%d",a[0]);
    }
}