//Encrypting a charecter by circular moving with a value d in alphabetical order
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
    int fd[2];
    printf("Enter the value d\n");
    int d;
    scanf("%d",&d);
    if(pipe(fd)<0){
        printf("Error in making pipe\n");
    }
    int c=fork();
    if(c>0){
        printf("Entered parent process which is sender\n");
        close(fd[0]);           //fd[0] is the read end in pipe
        char s[100];
        sleep(1);
        printf("Enter the plain text\n");
        scanf("%s",s);
        int l=0;
        while(s[l++]);
        l--;
        char str[l];
        for(int i=0;i<l;i++){
            str[i]= 97+(26+d+s[i]-97)%26;
        }
        printf("The string after encryption is %s\n",str);
        write(fd[1],str,sizeof(str));
        int wstatus=0;
        wait(&wstatus);
    }
    else{
        printf("Entered child process which is receiver\n");
        close(fd[1]);           //fd[1] is the write end in pipe
        char p[100];
        sleep(3);
        int l;
        if((l=read(fd[0],p,100)) == -1){
            printf("Error in reading\n");
        }
        int i=0;
        char *g = (char*)malloc(l*sizeof(char));
        for(int i=0;i<l;i++){
            g[i]= 97+(26+p[i]-d-97)%26;
        }
        printf("The string after decryption is %s\n",g);
    }
}

