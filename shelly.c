#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 1000

void intro();
void space(int);
void location();
void help();
void notfound(char *, char *);

int main() {
    intro();
	
    // entering an infinite command loop
    while (1) {
        location();

		char str[N] = {};
	
        fgets(str, N, stdin);        
        char * rest = str;
        
        str[strcspn(str, "\n")] = '\0';

        if (strcmp(str, "עזרה") == 0)
            help();
        else if (strcmp(str, "צא") == 0)
            break;
        else if (strcmp(str, "של") == 0){
        	int pid;
        	if ( (pid = fork()) == 0 ){ //child
                char cwd[N] = {};
                getcwd(cwd, sizeof(cwd));
                execl( strcat(cwd,"/shelly"),"shelly",NULL);
			    notfound("של", cwd);
                exit(0);
            }
           	else{ //father
			if (wait(NULL) == -1) {
			    char cwd[N] = {};
			    getcwd(cwd, sizeof(cwd));
			    notfound("של", cwd);
			    }
	    	}
        }
        else if (strcmp(str, "רשימה") == 0){
        	int pid;
        	if ( (pid = fork()) == 0 ){ //child
                char cwd[N] = {};
                getcwd(cwd, sizeof(cwd));
                execl( strcat(cwd,"/listall"),"listall",NULL);
			    notfound("רשימה", cwd);
                exit(0);
            }
           	else{ //father
			if (wait(NULL) == -1) {
			    char cwd[N] = {};
			    getcwd(cwd, sizeof(cwd));
			    notfound("רשימה", cwd);
			    }
	    	}
        }
        else if ( strcmp(strtok_r(rest, " ", &rest), "הדפס") == 0){
            printf("\n%s\n", rest);
        }
        else{
			space(39);
			printf("\033[1mהפקודה שהזנת איננה תקינה, לעזרה הקש: עזרה\033[0m\n");
    	}
	}

    return 0;
}

void help() {
     printf("\n");
     space(47); printf("\033[1m:הפקודות הבאות זמינות\033[0m\n");
     space(20); printf("\033[1m רשימה: הדפסת כל הקבצים והתיקיות בתיקייה הנוכחית\033[0m\n");
     space(27); printf("\033[1m של: כניסה לתת תכנית לביצוע פקודות נוספות\033[0m\n");
     space(25); printf("\033[1m הדפס: הדפסת המחרוזת המצורפת אחרי המילה הזו\033[0m\n");
     space(49); printf("\033[1m צא: יציאה מהתוכנית\033[0m\n");
     space(32); printf("\033[1m עזרה: הדפסת פרטים על הפקודות השונות\033[0m\n");
     printf("\n");
}    
void location(){
	char cwd[N] = {};
	getcwd(cwd, sizeof(cwd));
	printf("\033[1;32m[%s]\033[1m\033[35m >> \033[0m\033[1m", cwd);
}

void space(int n){
	for (int i = 0; i < n; i++)
		printf(" ");
}

void intro() {
    printf("\n");
    space(27);	printf("\033[1m! שלי - השל העברי הראשון\033[0m\n");
	printf("\n");
    space(30);	printf("\033[1mפותח על ידי מתן קיכלר\033[0m\n");

}
void notfound(char *program, char *directory) {
    space(5);
    printf("\033[1m! הפקודה %s שהזנת אמנם תקינה אך קובץ\nההרצה איננו בנמצא במיקום %s\033[0m\n", program, directory);
}
