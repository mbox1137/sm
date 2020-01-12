#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

//https://stackoverflow.com/questions/656542/trim-a-string-in-c
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(back>s && isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

typedef double (*funcptr_t)(double);

typedef struct FunctionTable_ {
    char name[20];
    funcptr_t func;
} FunctionTable;

FunctionTable fnt[]={	{"sin",&sin},
                        {"cos",&cos},
                        {"exp",&exp},
                        {"log",&log},
                        {"tan",&tan},
                        {"sqrt",&sqrt}
                    };

int main()
{
    char str[80], sname[20], sval[20];
    unsigned long n, k;
    char *cp;
    double arg, val;
    n=sizeof(fnt)/sizeof(FunctionTable);
    while (!feof(stdin))
    {
        if (fgets(str, 80, stdin) == NULL)
        {
            break;
        }
        rtrim(str);
        if(strlen(str) >0)
        {
          printf("%s: ", str);
          cp = strtok(str, " ");
          if(cp==NULL) {
            continue;
            }
          strcpy(sname,cp);
          cp = strtok(NULL, " ");
          if(cp==NULL) {
            continue;
            }
          strcpy(sval,cp);
          sscanf(sval,"%lf",&arg);
          val=NAN;
          for(k=0; k<n;k++) {
            if(strcmp(sname,fnt[k].name)==0) {
              val=fnt[k].func(arg);
              break;
            }
          }
          printf("%s(%s)==%s(%lf)=%lf\n", sname, sval, sname, arg, val);
        }
    }
    //sscanf;
/*
//https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
  ch = strtok(st, " ");
  while (ch != NULL) {
  printf("%s\n", ch);
  ch = strtok(NULL, " ,");
  }
*/
    return 0;
}
