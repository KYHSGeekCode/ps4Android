//#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()
#include <stdlib.h>
 
#include<stdio.h>
#define PROC_DIRECTORY "/proc/"

void ps1();

int main()
{
	//printf("start");
	ps1();
	//printf("terminated");
	return 0;
}
int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

void ps1()
{
    char chrarry_CommandLinePath[100]  ;
    char chrarry_NameOfProcess[300]  ;
    char* chrptr_StringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;

	//printf("Hello world!");
    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        printf("Couldn't open the " PROC_DIRECTORY " directory") ;
        return /*(pid_t) -2 */;
    }

    // Loop while not NULL
    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY) ;
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name) ;
                strcat(chrarry_CommandLinePath, "/cmdline") ;
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt") ;  // open the file for reading text
                if (fd_CmdLineFile)
                {
                    fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) ; // read from /proc/<NR>/cmdline
                    fclose(fd_CmdLineFile);  // close the file prior to exiting the routine

                    printf("%s\n", chrarry_NameOfProcess);
                  //  printf("Pure Process name: %s\n", chrptr_StringToCompare );
					pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
                   // closedir(dir_proc) ;
                    printf("%d\n", pid_ProcessIdentifier) ;
                }
            }
        }
		//printf("%s",de_DirEntity->d_name);
		//puts("");
    }
    closedir(dir_proc) ;
	//printf("done");
    return;// pid_ProcessIdentifier ;
}

