#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char *filetype(unsigned char type) {
    char *str;
    switch(type) {
        case DT_BLK: str = "block device"; break;
        case DT_CHR: str = "character device"; break;
        case DT_DIR: str = "directory"; break;
        case DT_FIFO: str = "named pipe (FIFO)"; break;
        case DT_LNK: str = "symbolic link"; break;
        case DT_REG: str = "regular file"; break;
        case DT_SOCK: str = "UNIX domain socket"; break;
        case DT_UNKNOWN: str = "unknown file type"; break;
        default: str = "UNKNOWN";
    }
    return str;
}

void recdir(char *fileName, const char *S, char *subString){
    char path[1024];
    struct dirent *dirent;
    DIR *parentDir;

    parentDir = opendir(fileName);
    if (parentDir == NULL) {
        return;
    }

    int indent ;

    while ((dirent = readdir(parentDir)) != NULL) {
        if((((strcmp(subString, "") == 0) || (strstr(dirent->d_name, subString) != NULL)))) {
            if (dirent->d_type == DT_DIR) {
                if ((strcmp(dirent->d_name, ".") == 0) || (strcmp(dirent->d_name, "..") == 0)) {
                    continue;
                }
                indent = 8;
                if (strcmp(S,"t") == 0) {
                    printf("%*s %s (%s) <%ld bytes>\n", indent, "", dirent->d_name, filetype(dirent->d_type), dirent->d_off);
                }else{
                    printf("%*s %s (%s) \n", indent, "", dirent->d_name, filetype(dirent->d_type));
                }
                strcpy(path, fileName);
                strcat(path, "/");
                strcat(path, dirent->d_name);
                recdir(path, S, "");
            } else {
                indent = 16;
                if (strcmp(S,"t") == 0) {
                    printf("%*s %s (%s) <%ld bytes>\n", indent, "", dirent->d_name, filetype(dirent->d_type), dirent->d_off);
                }
                else{
                    printf("%*s %s (%s) \n", indent, "", dirent->d_name, filetype(dirent->d_type));
                }
            }
        }
    }
    closedir(parentDir);
}

int main (int argc, char **argv) {
    struct dirent *dirent;
    DIR *parentDir;


    if (argc == 1) {
        parentDir = opendir(".");
        if (parentDir == NULL) {
            printf("Error opening directory '%s'\n", argv[1]);
            exit(-1);
        }
        recdir("..", "f", "");
        closedir (parentDir);
    }else{

        int i;
        char filename[100] = "..";
        char S[100];
        char subString[100];

        for (i = 0; i < sizeof(argv); ++i){
            if (strcmp(argv[i],"-S") == 0) {
                strcpy(S,"t");
                break;            /*}else if (strcmp(argv[i],"-s") == 0) {
                *fileSize = (long)(argv[i]+1);
                ++i;
                break; */

            }else if (strcmp(argv[i],"-f") == 0) {
                strcpy(subString,argv[i+1]);
                ++i;
                break;
            }
        }

        parentDir = opendir(filename);
        if (parentDir == NULL) {
            printf("Error opening directory '%s'\n", argv[1]);
            exit(-1);
        }

        recdir(filename, S, subString);
    }


        return 0;
}

