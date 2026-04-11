//给定字符串，还有变形行数，输出二维Z形的字符串。

//输出格式也需要对齐
#include <iostream>
#include <string>
using namespace std;
void printString(std::string str, int rowCount){
    int size =str.size();
    int drow=(rowCount-1)*2;
    for(int i=0;i<rowCount;i++){
        int t1=(rowCount-2-i)*2;//表示第一次打印的空格数
        int t2=(i-1)*2;//表示第二次打印的空格数
        int index=i;
        while(index<size){
            printf("%c ",str[index]);
            if(i==0||i==rowCount-1){
                index+=drow;
                printf("%*s",(rowCount-2)*2," ");//输出空格
            }else{
                printf("%*s",t1," ");
                index+=(drow-2*i);
                if(index<size){
                    printf("%*s",t2," ");
                    printf("%c ",str[index]);
                    index+=2*i;
                }
            }
        }
        cout<<endl;
    }
}