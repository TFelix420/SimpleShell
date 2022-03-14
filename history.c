#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

char *history[20][50]; /// array of separated strings
int historyCounter = 0; /// created a counter for vacant entries to store commands.

void addToHistory(char *commandArray[50]) {
    ///trying to add all the input line into an entry of history.
    int i = 0;
    while (commandArray[i] != NULL) {
        history[historyCounter][i] = malloc(sizeof(commandArray[i]));
        strcpy(history[historyCounter][i], commandArray[i]);
        i++;
    }
    ///incrementing the counter for next vacant entry.
    /// keeping it circular by checking the counter vs size of array.
    if (historyCounter == sizeof(history) / sizeof(history[0]) - 1)
        historyCounter = 0; ///kinda sus to me, idk if it works
    else historyCounter++;
}

void printHistory() {
    int i = 0;
    char curCommand[512];
    while (history[i][0] != NULL) {
        strcpy(curCommand, "");
        int j = 0;
        while (history[i][j] != NULL)
            strcat(curCommand, history[i][j++]);
        printf("%d %s\n", i + 1, curCommand);
        i++;
    }
}

void executePreviousCommand() {
    const char *token;
    if (history[historyCounter - 2] == NULL) {   /// looking for if the invocation is valid and can be executed.
        printf("%s\n", "There is no previous command.");
        return;
    }
    /*token = strtok(history[historyCounter - 1], " "); ///parsing the command in new array got problem
    /// for multiple parameters commands.
    char *commandInvoked[50];
    int i = 0;
    while (token != NULL) {
        printf(">%s\n", token);
        commandInvoked[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    printf("Trying to execute: %s\n", commandInvoked);*/
    readInput(history[historyCounter - 2]); /// executing the command
}

void executeNthCommand(char *commandArray[50]) {
    const char *token;
    int historyIndex;
    const char *delimiter = "!";   /// getting right index
    commandArray[0] = strtok(commandArray[0], delimiter);

    historyIndex = atoi(commandArray[0]);
    historyIndex -= 1;
    /// checking if it's a right invoke.
    if ((history[historyIndex] == NULL) || (historyIndex == historyCounter)) {
        printf("%s\n", "Invocation invalid, try again.");
        return;
    } /// checking if it's history.
    if (strcmp(history[historyIndex], "history") != 0) {
        token = strtok(history[historyIndex], " ");
        char *commandInvoked[50];

        int i = 0;
        while (token != NULL) {
            commandInvoked[i] = token;

            token = strtok(NULL, " ");
            i++;
        }

        readInput(commandInvoked);
    } else {
        int i = 0;
        while (history[i] != NULL) {
            printf("%d %s\n", i + 1, *(history + i));
            i++;
        }
    }
}

void executeInverseNthCommand(char *commandArray[50]) {
    const char *token;
    int historyIndex;
    const char *delimiter = "!-";
    commandArray[0] = strtok(commandArray[0], delimiter); /// parsing to get the right index
    historyIndex = atoi(commandArray[0]);
    historyIndex = historyCounter - historyIndex;
    /// looking for if the invocation is valid and can be executed.
    if ((history[historyIndex] == NULL) || (historyIndex == historyCounter)) {
        printf("%s\n", "Invocation invalid, try again.");
        return;
    }
    /// looking for whether it's a valid index to invoke.
    if ((historyIndex >= 0) && (historyIndex < 20)) {
        if (strcmp(history[historyIndex], "history") != 0) {
            token = strtok(history[historyIndex], " ");
            char *commandInvoked[50];
            int i = 0;
            while (token != NULL) {  ///usual parsing, dont like multiple parameter strings.
                commandInvoked[i] = token;

                token = strtok(NULL, " ");
                i++;
            }
            readInput(commandInvoked);
        } else {
            int i = 0; /// usual printing if it's asked for.
            while (history[i] != NULL) {
                printf("%d %s\n", i + 1, *(history + i));
                i++;
            }
        }
    }
}