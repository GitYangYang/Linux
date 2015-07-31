#include<stdio.h>
#include<string.h>
int main(){

char str[]="\003abc";
if(strncmp("\003",str,1)==0){
   printf("1");
}
else printf("0");
return (0);

}
