#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define PROMPT "$ "
#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 128

void displayPrompt(void);
int parseUserInput(char *buffer, char *args[]);
void builtin_exit(void);
int commandExistsInPath(const char *command, const char *path);
void displayEnv(void);
void setEnv(const char *name, const char *value);
void unsetEnv(const char *name);
char ***getenviron(void);
void executeCommand(char *buffer, ssize_t n);
void displayExitStatus(int status);
void waitForChildProcess(pid_t child_pid, int *status);
void handleCommandNotFound(char *buffer, ssize_t n);
void executeChildProcess(char *buffer, ssize_t n);
void handleForkError(void);

#endif
