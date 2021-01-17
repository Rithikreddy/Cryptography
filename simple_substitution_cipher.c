#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
    int fd[2];
char pt[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char ct[]={'K','D','G','F','N','S','L','V','B','W','A','H','E','X','J','M','Q','C','P','Z','R','T','Y','I','U','O'};
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
        int l=0,j;
        while(s[l++]);
        l--;
        char str[l];
        for(int i=0;i<l;i++){
            for(j=0;j<26;j++){
                if(s[i] == pt[j])
                    break;
            }
            str[i]=ct[j];
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
        int l,j=0;
        if((l=read(fd[0],p,100)) == -1){
            printf("Error in reading\n");
        }
        char *g = (char*)malloc(l*sizeof(char));
        for(int i=0;i<l;i++){
            for(j=0;j<26;j++){
                if(ct[j] == p[i])
                    break;
            }
            g[i]=pt[j];
        }
        printf("The string after decryption is %s\n",g);
    }
}
