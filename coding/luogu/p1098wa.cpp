/*#include<iostream>
using namespace std;
int main(){
    int p1,p2,p3;
    string s;
    cin>>p1>>p2>>p3;
    cin>>s;
    char head,tail;
    for(int k=0;k<s.size();k++){
        if(s[k+1]=='-'){
            head=s[k];
            tail=s[k+2];
            if(((head>='0' && head<='9') && (tail>='a' && tail<='z')) || ((tail>='0' && tail<='9') && (head>='a' && head<='z'))){
                cout<<head<<'-';
                k++;
                continue;
            }
            else if(head>=tail){  
                cout<<head<<'-';
                k++;
                continue;
            }
            cout<<s[k];
            if(p3==1){
                if(p1==1){
                    for(char i=head+1;i<tail;i++){
                        for(int j=0;j<p2;j++){
                            printf("%c",i);
                        }
                    }
                }
                if(p1==2){
                    for(char i=head+1;i<tail;i++){
                        for(int j=0;j<p2;j++){
                            printf("%c",i+'A'-'a');
                        }
                    }
                }
                if(p1==3){
                    for(char i=head+1;i<tail;i++){
                        for(int j=0;j<p2;j++){
                            printf("*");
                        }
                    }
                }
            }

            if(p3==2){
                if(p1==1){
                    for(char i=tail-1;i>head;i--){
                        for(int j=0;j<p2;j++){
                            printf("%c",i);
                        }
                    }
                }
                if(p1==2){
                    for(char i=tail-1;i>head;i--){
                        for(int j=0;j<p2;j++){
                            printf("%c",i+'A'-'a');
                        }
                    }
                }
                if(p1==3){
                    for(char i=tail-1;i>head;i--){
                        for(int j=0;j<p2;j++){
                            printf("*");
                        }
                    }
                }
            }
        }
        else if(s[k]=='-') continue;
        else{
            printf("%c",s[k]);
        }
    }
}*/

#include <iostream>
using namespace std;

int main() {
    int p1, p2, p3;
    string s;
    cin >> p1 >> p2 >> p3;
    cin >> s;

    for (int k = 0; k < (int)s.size(); k++) {

        // 必须保证 k+2 不越界，且当前是 head
        if (k + 2 < (int)s.size() && s[k + 1] == '-') {

            char head = s[k];
            char tail = s[k + 2];

            bool headDigit = (head >= '0' && head <= '9');
            bool tailDigit = (tail >= '0' && tail <= '9');
            bool headLetter = (head >= 'a' && head <= 'z');
            bool tailLetter = (tail >= 'a' && tail <= 'z');

            // 非法区间：原样输出 head 和 '-'
            if (!((headDigit && tailDigit) || (headLetter && tailLetter)) || head >= tail) {
                cout << head << '-';
                k++;          // 只跳过 '-'
                continue;
            }

            // 相邻字符：只删减号
            if (tail == head + 1) {
                cout << head << tail;
                k += 2;
                continue;
            }

            // 合法展开
            cout << head;

            if (p3 == 1) {
                for (char c = head + 1; c < tail; c++) {
                    for (int j = 0; j < p2; j++) {
                        if (p1 == 3) cout << '*';
                        else if (headDigit) cout << c;
                        else if (p1 == 1) cout << c;
                        else cout << char(c - 'a' + 'A');
                    }
                }
            } else {
                for (char c = tail - 1; c > head; c--) {
                    for (int j = 0; j < p2; j++) {
                        if (p1 == 3) cout << '*';
                        else if (headDigit) cout << c;
                        else if (p1 == 1) cout << c;
                        else cout << char(c - 'a' + 'A');
                    }
                }
            }

            cout << tail;
            k += 2;   // 跳过 '-' 和 tail
        }
        else if (s[k] != '-') {
            cout << s[k];
        }
    }
    return 0;
}
