#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
char **tokenize(char *line);

int main()
{
    char input[1024];
    while (1)
    {
        printf("myshell> ");
        memset(input, 0, sizeof(input));   
        gets(input);
        
        char **words = tokenize(input);
    	char* command=words[0];
        /** WRITE YOUR CODE HERE **/
        if(strcmp(command,"checkcpupercentage") == 0){

            /*int rc=fork();
            if(rc==0){*/
        	//printf(words);
        	//printf("\n");
    		int pid = atoi(words[1]);
            
        	int rc=fork();
        	if(rc == 0){
        	//printf("%d",pid);
            char* buff1=(char *)calloc(100, sizeof(char));
        	char path[20];
            int s= snprintf(path, 20 ,"/proc/%d/stat%c",pid,'\0');

            int fid1=open(path);
            int sz1=read(fid1,buff1, 100);
            //printf("sz%d\n", sz1);
            //printf(buff1);
            char** parts=tokenize(buff1);
            int utime_before=atoi(parts[13]);
            int stime_before=atoi(parts[14]);
            close(fid1);

            char* buff2=(char *)calloc(300, sizeof(char));
 
            int fid2=open("/proc/stat");
            int sz2=read(fid2,buff2,300);

            int total_time_before=0;
            parts=tokenize(buff2);
            for(int i=0; i< sizeof(parts)/sizeof(parts[0]);i++){
                char* part=parts[i];
                if(strcmp(part,"cpu") == 0){
                    i=i+1;
                    while(strcmp(parts[i],"cpu0")){
                        total_time_before += atoi(parts[i]);
                        i+=1;
                    }
                    break;
                }           
            }
            close(fid2);

            sleep(1);

            char* buff3=(char *)calloc(100, sizeof(char));

            int fid3=open(path);
            int sz3=read(fid3,buff3, 100);

            char** parts3=tokenize(buff3);
            int utime_after=atoi(parts3[13]);
            int stime_after=atoi(parts3[14]);
            
            close(fid3);
    
            char* buff4=(char *)calloc(300, sizeof(char));
            int fid4=open("/proc/stat");
            int sz4=read(fid4,buff4,300);
 
            int total_time_after=0;
            parts=tokenize(buff4);
            
            for(int i=0; i< sizeof(parts)/sizeof(parts[0]);i++){
                char* part=parts[i];
                if(strcmp(part,"cpu") == 0){
                    i=i+1;
                    while(strcmp(parts[i],"cpu0")){
                        total_time_after += atoi(parts[i]);
                        i+=1;
                    }
                    break;
                }
            }
            close(fid4);

            free(buff1);
            free(buff2);
            free(buff3);
            free(buff4);

            int ut=(utime_after*100-utime_before*100)/(total_time_after-total_time_before);

            int st=(stime_after*100-stime_before*100)/(total_time_after-total_time_before);

            printf("utime_after:%d",utime_after);
            printf("stime_after:%d",stime_after);

            printf("utime_before:%d",utime_before);
            printf("stime_before:%d",stime_before);


            printf("User Mode CPU Percentage:");
            printf("%d\n",ut);

            printf("System Mode CPU Percentage:");
            printf("%d\n",st);

            //exit(1);
            
        
    }
       /* else if(command == "checkresidentmemory"){

        }
        else if(command=="listFiles"){

        }
        else if(command == "sortFile"){

        }
        else if(command == )*/

            
    }
    return 0;
}


char **tokenize(char *input)
{
    int count = 0;
    char **tokens = (char **) malloc(32 * sizeof(char *));
    char *sch;
    sch = strtok(input, " \t\n"); 

    while (sch != NULL)
    {
        tokens[count] = sch;
        count++;
        sch = strtok(NULL, " \t\n"); 
    }

    free(sch);
    tokens[count] = NULL ;
    return tokens;
}
