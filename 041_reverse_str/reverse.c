#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  char * p=str;
  int i = 0;
  while(*p!='\0'){
    i++;
    p++;
  }
  char cop[i+1];
  cop[i]='\0';
  p--;
  //printf("%c\n",*p);
  for(int j=0;j<i;j++){
    cop[j]=*p;
    p--;
  }
  //printf("%s\n",cop);
  for(int j=0;j<i;j++){
    str[j]=cop[j];
  }
  //WRITE ME!
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}