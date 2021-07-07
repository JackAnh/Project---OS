#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<psapi.h>
#include <dirent.h>

STARTUPINFO si[100];
PROCESS_INFORMATION pi[100];
char name[10][25];
int n = 0;

void SHOWMENU() {
    printf("\n***************************************************************\n");
    printf("    ----My Shell supports the following commands:----\n\n");
    printf("bat     : Execute file batch.\n");
    printf("continue: Continue a background process that suspended.\n");
    printf("copy    : Copies a file to another location..\n");
    printf("date    : Display mm-dd-yy data.\n");
    printf("delete  : Deletes one or more files.\n");
    printf("dir     : Displays a list of files and subdirectories in a directory.\n");
    printf("exit    : Quit the Shell program.\n");
    printf("help    : Provides Help information for My Shell.\n");
    printf("kill_all: Kill all process\n");
    printf("kill_id : Kill a process by dwProcessID\n");
    printf("list    : List all process that called by My Shell\n");
    printf("open    : Create process that can be run background or foreground.\n");
    printf("pause   : Suspends processing.\n");
    printf("rename  : Renames a file. If old name and new name specify different \n          paths the file is moved to the new location.\n");
    printf("***************************************************************\n");
}

void DIRI() {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirSpec[MAX_PATH]; // directory specification
//    DWORD dwError;

    char *path;
    path = malloc(300 * sizeof(char));
    printf("> Path: "); gets(path);

    printf("Target directory is %s.\n", path);
    strncpy(DirSpec, path, strlen(path)+1);
    strcat(DirSpec, "\\*");

    hFind = FindFirstFile(DirSpec, &FindFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
//        printf("Invalid file handle. Error is %u\n", GetLastError());
        printf("Invalid file handle.\n");
    }
    else {
        printf("First file name is %s\n", FindFileData.cFileName);
        while(FindNextFile(hFind, &FindFileData) != 0){
            printf("Next file name is %s\n", FindFileData.cFileName);
        }

//        dwError = GetLastError();
        FindClose(hFind);
//        if(dwError != ERROR_NO_MORE_FILES) {
//            printf("FindNextFile error. Error is %u\n", dwError);
//        }
    }
    free(path);
}

void LIST(){
//    printf(" No  dwProcessId   hProcess   wShowWindow \n");
//    for (int i = 1;i <= n; i++) {
//        printf("%2d   %8d     %9p  %9s\n", i, pi[i].dwProcessId, pi[i].hProcess, si[i].wShowWindow);
//        printf("%2d   %8d      %9s", i, pi[i].dwProcessId, name[i]);
//    }
    printf("No     dwProcessId      fileName \n");
    if(n == 0) {
        printf("null      null           null\n");
    }
    for (int i = 1;i <= n; i++) {
        printf("%2d     %8d        %9s\n", i, pi[i].dwProcessId, name[i]);
    }
}

void KILL_ID(int id){
    int flag = 0;
    for (int i = 1;i <= n; i++) {
        if (id == pi[i].dwProcessId){
            flag = 1;
            TerminateProcess(pi[i].hProcess, 1);
            CloseHandle(pi[i].hProcess);
            CloseHandle(pi[i].hThread);
            for (int j = i; j < n; j++){
                pi[j] = pi[j + 1];
                si[j] = si[j + 1];
                strncpy(name[j], name[j+1], 20);
            }
            printf("Killed!!!\n");
            n--;
            break;
        }
    }
    if(flag == 0) printf("NOT EXISTED !!!\n");
}

void KILL_ALL(){
    for (int i = 1;i <= n; i++) {
        TerminateProcess(pi[i].hProcess, 1);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }
    printf("All process killed ... \n");
    n = 0;
}

void PAUSE(int id) {
    int flag = 0;
    for (int i = 1;i <= n; i++) {
        if (id == pi[i].dwProcessId){
            ++flag;
            SuspendThread(pi[i].hThread);
            break;
        }
    }
    if(flag == 0) printf("Not existed");
}

void CONTINUE(int id) {
    for (int i = 1;i <= n; i++) {
        if (id == pi[i].dwProcessId){
            ResumeThread(pi[i].hThread);
            break;
        }
    }
}

void BAT() {
    char* nameFile;
    printf("> File name: "); nameFile = malloc(10 * sizeof(char)); gets(nameFile);

    char line[255];
    FILE *file = fopen(nameFile, "r");
    while(fgets(line, 255, file)) {
        char chooseOfBat[10];
        int count = 0;
        while(line[count] != ' ' && line[count] != '\n'){
            chooseOfBat[count] = line[count];
            ++count;
        }
        chooseOfBat[count] = '\0';
        ++count;

        if (!strcmp(chooseOfBat, "date")) {    // OK
            time_t t;
            time(&t);
            printf("Current Time: %s", ctime(&t));
            printf("\n");
        }
        else if (!strcmp(chooseOfBat, "dir")){  // OK: WARNING???
            char filePath[MAX_PATH];
            int tempCount = count;
            int indexFilePath = 0;
            while(line[tempCount] != '\n') {
                filePath[indexFilePath] = line[tempCount];
                ++tempCount;
                ++indexFilePath;
            }
            filePath[indexFilePath] = '\0';
            DIR_BAT(filePath);
            printf("\n");
        }
        else if (!strcmp(chooseOfBat, "help")){  // OK
            SHOWMENU();
        }
        else if (!strcmp(chooseOfBat, "open")){
            int head = count;
            int pointer = count;
            while(line[pointer] != '\n') {
                ++pointer;
            }

            --pointer;
            char mode[11];
            mode[10] = '\0';
            int indexMode = 9;
            while(indexMode >= 0) {
                mode[indexMode] = line[pointer];
                --pointer;
                --indexMode;
            }

            --pointer;
            int size = pointer-head+1+1;
            char filePath[size];
            filePath[size-1] = '\0';
            int indexFilePath = size-2;
            while(indexFilePath >= 0) {
                filePath[indexFilePath] = line[pointer];
                --pointer;
                --indexFilePath;
            }

            OPEN_BAT(filePath, mode);

        }
        else if (!strcmp(chooseOfBat, "list")){  //OK
            LIST();
            printf("\n");
        }
        else if (!strcmp(chooseOfBat, "kill_all")){  // OK
            KILL_ALL();
            printf("\n");
        }
        else {
            printf("%10s: Not found!!!\n\n", chooseOfBat);
        }
     }
}

void OPEN() {
    ++n;
    char *file; file = malloc(100 * sizeof(char)); printf("> File name: "); gets(file);
    int count = 0;

    printf("> Mode: "); char *mode; mode = malloc(10 * sizeof(char)); gets(mode);

    if (!strcmp(mode, "background")) {
        while(file[count] != '\0') {
            name[n][count] = file[count];
            ++count;
        }
        ZeroMemory(&si[n], sizeof(si[n]));
        si[n].cb = sizeof(si[n]);
        ZeroMemory(&pi[n], sizeof(pi[n]));
        CreateProcess(file,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si[n],&pi[n]);
    }
    else if (!strcmp(mode, "foreground")) {
//        while(file[count] != '\0') {
//            name[n][count] = file[count];
//            ++count;
//        }
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        CreateProcess(file,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
        WaitForSingleObject(pi.hProcess,INFINITE);//INFINITE
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        --n;
    }
    else {
        printf("ERROR SYNTAX!!!!!\n");
        --n;
    }
    free(mode);
    free(file);
}

//---------------------------- function for BAT() -----------------------------------//
void DIR_BAT(char *path) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirSpec[MAX_PATH];
    printf("Target directory is %s.\n", path);
    strncpy(DirSpec, path, strlen(path)+1);
    strcat(DirSpec, "\\*");

    hFind = FindFirstFile(DirSpec, &FindFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Invalid file handle.\n");
    }
    else {
        while(FindNextFile(hFind, &FindFileData) != 0){
            printf("Next file name is %s\n", FindFileData.cFileName);
        }
        FindClose(hFind);
    }
    free(path);
}

void OPEN_BAT(char *file, char *mode) {
    ++n;
    int count = 0;
    if (!strcmp(mode, "background")) {
        while(file[count] != '\0') {
            name[n][count] = file[count];
            ++count;
        }
        ZeroMemory(&si[n], sizeof(si[n]));
        si[n].cb = sizeof(si[n]);
        ZeroMemory(&pi[n], sizeof(pi[n]));
        CreateProcess(file,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si[n],&pi[n]);
    }
    else if (!strcmp(mode, "foreground")) {
//        while(file[count] != '\0') {
//            name[n][count] = file[count];
//            ++count;
//        }
        ZeroMemory(&si[n], sizeof(si[n]));
        si[n].cb = sizeof(si[n]);
        ZeroMemory(&pi[n], sizeof(pi[n]));

        CreateProcess(file,NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si[n],&pi[n]);
        WaitForSingleObject(pi[n].hProcess,INFINITE);//INFINITE
        TerminateProcess(pi[n].hProcess, 0);
        CloseHandle(pi[n].hProcess);
        CloseHandle(pi[n].hThread);
        --n;
    }
    else {
        printf("ERROR SYNTAX!!!!!\n");
        --n;
    }
    free(mode);
    free(file);
}

// -------------------------------- function MAIN() -----------------------------------//
int main(){
    SHOWMENU();
    do {
        printf("MyShell\\> ");
        char *choose;
        choose = malloc(10 * sizeof(char));
        gets(choose);

        if (!strcmp(choose, "dir")) {
            DIRI();
            printf("\n");
        }
        else if (!strcmp(choose, "help")) {
            SHOWMENU();
        }
        else if (!strcmp(choose, "open")) {
            OPEN();
            printf("\n");
        }
        else if (!strcmp(choose, "list")) {
            LIST();
            printf("\n");
        }
        else if (!strcmp(choose, "pause")) {
            printf("> dwProcessId: "); int id; scanf("%d", &id); getchar();
            PAUSE(id);
            printf("\n");
        }
        else if (!strcmp(choose, "continue")) {
            printf("> dwProcessId: "); int id; scanf("%d", &id); getchar();
            CONTINUE(id);
            printf("\n");
        }
        else if (!strcmp(choose, "bat")) {
            BAT();
            printf("\n");
        }
        else if (!strcmp(choose, "date")) {
            time_t t;
            time(&t);
            printf("Current Time: %s", ctime(&t));
            printf("\n");
        }
        else if (!strcmp(choose, "kill_all")) {
            KILL_ALL();
            printf("\n");
        }
        else if (!strcmp(choose, "kill_id")) {
            printf("> dwProcessId: "); int id; scanf("%d", &id); getchar();
            KILL_ID(id);
            printf("\n");
        }
        else if (!strcmp(choose, "exit")) {
            for (int i = 1;i <= n; i++) {
                TerminateProcess(pi[i].hProcess, 1);
                CloseHandle(pi[i].hProcess);
                CloseHandle(pi[i].hThread);
            }
            exit(0);
            printf("\n");
        }
        else if (!strcmp(choose, "rename")) {
            char *oldName; oldName = malloc(100 * sizeof(char)); printf("> Old name: "); gets(oldName);
            char *newName; newName = malloc(100 * sizeof(char)); printf("> New name: "); gets(newName);
            int result= rename(oldName, newName);
            if (result == 0)
                printf("File successfully renamed");
            else
                printf("Error renaming file");
            printf("\n\n");
        }
        else if (!strcmp(choose, "delete")){
            char *fileName; fileName = malloc(100 * sizeof(char)); printf("> Path: "); gets(fileName);
            if (fileName[strlen(fileName)-1] == '*') {
                fileName[strlen(fileName)-2] = '\0';
            }

            if(remove(fileName) == -1){
                DIR *theFolder = opendir(fileName);
                struct dirent *next_file;
                char filepath[256];
                int flag = 0;

                while ( (next_file = readdir(theFolder)) != NULL)
                {
                    ++flag;
                    sprintf(filepath, "%s/%s", fileName, next_file->d_name);
                    remove(filepath);
                }
                if(flag == 0) {
                    printf("Error in deleting a file.\n\n");
                }
                else {
                    printf("File successfully deleted.\n\n");
                }
                closedir(theFolder);
            }
            else {
                printf("File successfully deleted.\n\n");
            }
        }
        else if (!strcmp(choose, "copy")) {
            FILE *fp1,*fp2;
            char ch,sourceName[1000],desName[1000];

            printf("> Source file: "); gets(sourceName);
            fp1=fopen(sourceName,"r");

            if(fp1==NULL)
            {
                printf("File could not open!!");
                printf("\n\n");
                continue;
            }

            printf("> Destination file: "); gets(desName);
            fp2=fopen(desName,"w");

            if(fp2 == NULL){
                printf("File could not open!!");
                printf("\n\n");
                continue;
            }
            while((ch=getc(fp1))!=EOF)
            putc(ch,fp2);
            printf("%s is created and copied\n\n", desName);

            fclose(fp1);
            fclose(fp2);
        }
        else {
            if(choose[0] == '\0'){
            }
            else {
                printf("%10s: Not found!!!\n\n", choose);
                free(choose);
            }
        }
    } while(1);

    return 0;
}
