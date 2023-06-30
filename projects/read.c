include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define MAX_BLOCKS 10
#define MAX_PARAMS 3
#define LOG_FILE "./log/restart.txt"
#define BLOCKS_FILE "./blocks.txt"
#define RESTART_INTERVAL 3

typedef struct {
    char name[50];
    char params[MAX_PARAMS][50];
    int paramCount;
    int restartCount;
    time_t startTime;
    char reason[50];
} SoftwareBlock;

SoftwareBlock blocks[MAX_BLOCKS];
int blockCount = 0;

void readBlocksFromFile() {
    FILE* file = fopen(BLOCKS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL && blockCount < MAX_BLOCKS) {
        char* token = strtok(line, ";");
        strcpy(blocks[blockCount].name, token);

        token = strtok(NULL, ";");
        int paramIndex = 0;
        while (token != NULL) {
            strcpy(blocks[blockCount].params[paramIndex], token);
            paramIndex++;
            token = strtok(NULL, ";");
        }
        blocks[blockCount].paramCount = paramIndex;
        blockCount++;
    }

    fclose(file);
}

void initializeBlock(SoftwareBlock* block) {
    printf("Initializing block: %s\n", block->name);
    block->startTime = time(NULL);
    strcpy(block->reason, "Init");
}

void restartBlock(SoftwareBlock* block, const char* reason) {
    printf("Restarting block: %s\n", block->name);
    block->restartCount++;
    block->startTime = time(NULL);
    strcpy(block->reason, reason);

    FILE* file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    fprintf(file, "Block Name: %s\n", block->name);
    fprintf(file, "Restart Count: %d\n", block->restartCount);
    fprintf(file, "Start Time: %s", ctime(&block->startTime));
    fprintf(file, "Reason: %s\n\n", block->reason);

    fclose(file);
}

void childSignalHandler(int signal) {
    pid_t childPid;
    int status;

    while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
        int randomIndex = rand() % blockCount;
        SoftwareBlock* blockToRestart = &blocks[randomIndex];

        char restartReason[50];
        switch (signal) {
            case 1:
                snprintf(restartReason, sizeof(restartReason), "Signal(1)");
                kill(getpid(), SIGHUP);
                break;
            case 2:
                snprintf(restartReason, sizeof(restartReason), "Signal(2)");
                kill(getpid(), SIGINT);
                break;
            case 3:
                snprintf(restartReason, sizeof(restartReason), "Signal(3)");
                kill(getpid(), SIGQUIT);
                break;
            case 4:
                snprintf(restartReason, sizeof(restartReason), "Signal(4)");
                kill(getpid(), SIGTERM);
                break;
            default:
                snprintf(restartReason, sizeof(restartReason), "Signal(%d, Killed)", signal);
                break;
        }

        restartBlock(blockToRestart, restartReason);
    }
}

void spawnChildProcess() {
    pid_t pid = fork();
    if (pid < 0) {
        printf("Error forking process.\n");
        exit(1);
    } else if (pid == 0) {
        sleep(3);
        signal(SIGHUP, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
        exit(0);
    } else {
        signal(SIGCHLD, childSignalHandler);
    }
}

void printBlockStatus() {
    printf("%-15s%-15s%-25s%s\n", "S/W Block Name", "Restart Count", "Start Time", "Reason");
    for (int i = 0; i < blockCount; i++) {
        SoftwareBlock* block = &blocks[i];
        struct tm* timeinfo = localtime(&block->startTime);
        char startTimeStr[50];
        strftime(startTimeStr, sizeof(startTimeStr), "%c", timeinfo);
        printf("%-15s%-15d%-25s%s\n", block->name, block->restartCount, startTimeStr, block->reason);
    }
}

int main() {
    srand(time(NULL));

    readBlocksFromFile();

    for (int i = 0; i < blockCount; i++) {
        initializeBlock(&blocks[i]);
    }

    while (1) {
        sleep(RESTART_INTERVAL);
        int signalNumber = rand() % 4 + 1;  
        spawnChildProcess(signalNumber);
        printBlockStatus();
    }

    return 0;
}
