/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarenou <dcarenou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:42:32 by dcarenou          #+#    #+#             */
/*   Updated: 2023/12/27 00:51:37 by dcarenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "./lexer/lexer.h"

typedef enum TokenType
{
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_IN_APPEND,
    TOKEN_REDIRECT_OUT_APPEND,
    TOKEN_PIPE,
    TOKEN_COMMAND,
    TOKEN_BUILTIN,
    TOKEN_ENV_VAR,
    TOKEN_DOUBLE_QUOTE,
    TOKEN_SINGLE_QUOTE,
    TOKEN_ARGUMENT,
    TOKEN_REDIRECT_FILE,
    TOKEN_UNKNOWN
} TokenType;

typedef enum NodeType
{
    NODE_COMMAND,
    NODE_REDIRECT_IN,
    NODE_REDIRECT_OUT,
    NODE_REDIRECT_IN_APPEND,
    NODE_REDIRECT_OUT_APPEND,
    NODE_PIPE,
    NODE_ENV_VAR,
    NODE_DOUBLE_QUOTE,
    NODE_SINGLE_QUOTE,
    NODE_REDIRECT_FILE,
    NODE_UNKNOWN
} NodeType;

typedef enum LexerState
{
    STATE_START,
    STATE_IN_COMMAND,
    STATE_AFTER_COMMAND,
    STATE_AFTER_REDIRECT
} LexerState;

typedef struct ASTNode
{
    NodeType type;
    char *value;
    char **args; // New field for arguments
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

typedef struct Token
{
    TokenType type;
    char *value;
    struct Token *next;
} Token;

typedef struct StackNode
{
    ASTNode *data;
    struct StackNode *next;
} StackNode;

typedef struct Stack
{
    StackNode *top;
} Stack;

// Function to create a new stack
Stack *createStack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Function to delete a stack
void deleteStack(Stack *stack)
{
    while (stack->top != NULL)
    {
        StackNode *temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}

// Function to push a node onto the stack
void pushStack(Stack *stack, ASTNode *data)
{
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a node from the stack
ASTNode *popStack(Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }
    StackNode *temp = stack->top;
    ASTNode *data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to peek at the top node of the stack
ASTNode *peekStack(Stack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }
    return stack->top->data;
}

// Function to check if the stack is empty
int isEmptyStack(Stack *stack)
{
    return stack->top == NULL;
}

// Function to get the size of the stack
int getSizeStack(Stack *stack)
{
    int size = 0;
    StackNode *current = stack->top;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

int getPriority(ASTNode *node)
{
    switch (node->type)
    {
    case NODE_COMMAND:
        return 1;
    case NODE_REDIRECT_IN:
    case NODE_REDIRECT_OUT:
    case NODE_REDIRECT_IN_APPEND:
    case NODE_REDIRECT_OUT_APPEND:
        return 3;
    case NODE_PIPE:
        return 4;
    case NODE_ENV_VAR:
        return 5;
    case NODE_DOUBLE_QUOTE:
    case NODE_SINGLE_QUOTE:
        return 6;
    default:
        return 0;
    }
}

Token *create_token(TokenType type, char *value)
{
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

void add_token(Token **head, TokenType type, char *value)
{
    Token *new_token = create_token(type, value);
    if (*head == NULL)
    {
        *head = new_token;
    }
    else
    {
        Token *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_token;
    }
}

TokenType identify_token(char *value, LexerState *state)
{
    if (strcmp(value, ">") == 0 || strcmp(value, ">>") == 0 || strcmp(value, "<") == 0 || strcmp(value, "<<") == 0)
    {
        *state = STATE_AFTER_REDIRECT;
        if (value[0] == '>')
        {
            if (value[1] == '>')
            {
                return TOKEN_REDIRECT_OUT_APPEND;
            }
            else
            {
                return TOKEN_REDIRECT_OUT;
            }
        }
        else if (value[1] == '<')
        {
            return TOKEN_REDIRECT_IN_APPEND;
        }
        else
        {
            return TOKEN_REDIRECT_IN;
        }
    }
    else if (strcmp(value, "|") == 0)
    {
        *state = STATE_START;
        return TOKEN_PIPE;
    }
    else if (strcmp(value, "\"") == 0)
    {
        return TOKEN_DOUBLE_QUOTE;
    }
    else if (strcmp(value, "'") == 0)
    {
        return TOKEN_SINGLE_QUOTE;
    }
    else if (*state == STATE_START && isalpha(value[0]))
    {
        *state = STATE_IN_COMMAND;
        return TOKEN_COMMAND;
    }
    else if (*state == STATE_IN_COMMAND)
    {
        return TOKEN_ARGUMENT;
    }
    else if (*state == STATE_AFTER_REDIRECT)
    {
        *state = STATE_IN_COMMAND;
        return TOKEN_REDIRECT_FILE;
    }
    else if (value[0] == '$')
    {
        return TOKEN_ENV_VAR;
    }
    else
    {
        *state = STATE_IN_COMMAND;
        return TOKEN_ARGUMENT;
    }
}

void lex(char *input, Token **tokens)
{
    LexerState state = STATE_START;
    char *nextp;
    char *current = strtok_s(input, " ", &nextp);
    while (current != NULL)
    {
        TokenType type = identify_token(current, &state);
        add_token(tokens, type, current);
        current = strtok_s(NULL, " ", &nextp);
    }
}

ASTNode *parse(Token *tokens)
{
    Stack *stack = createStack();
    Token *current = tokens;
    while (current != NULL)
    {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->value = strdup(current->value);
        node->args = NULL;
        node->left = NULL;
        node->right = NULL;

        switch (current->type)
        {
        case TOKEN_COMMAND:
            node->type = NODE_COMMAND;
            node->args = malloc(sizeof(char *)); // Allocate space for arguments
            node->args[0] = NULL;                // Initialize with no arguments
            break;
        case TOKEN_ARGUMENT:
            // Add argument to the last command node
            ASTNode *last_command = peekStack(stack);
            if (last_command != NULL && last_command->type == NODE_COMMAND)
            {
                int arg_count = 0;
                while (last_command->args[arg_count] != NULL)
                {
                    arg_count++;
                }
                last_command->args = realloc(last_command->args, (arg_count + 2) * sizeof(char *)); // Allocate space for new argument
                last_command->args[arg_count] = strdup(current->value);                             // Add new argument
                last_command->args[arg_count + 1] = NULL;                                           // Null-terminate the argument list
            }
            free(node); // We don't need the argument node anymore
            current = current->next;
            continue;
        case TOKEN_REDIRECT_IN:
            node->type = NODE_REDIRECT_IN;
            break;
        case TOKEN_REDIRECT_OUT:
            node->type = NODE_REDIRECT_OUT;
            break;
        case TOKEN_REDIRECT_IN_APPEND:
            node->type = NODE_REDIRECT_IN_APPEND;
            break;
        case TOKEN_REDIRECT_OUT_APPEND:
            node->type = NODE_REDIRECT_OUT_APPEND;
            break;
        case TOKEN_REDIRECT_FILE:
            node->type = NODE_REDIRECT_FILE;
            break;
        case TOKEN_PIPE:
            node->type = NODE_PIPE;
            break;
        case TOKEN_ENV_VAR:
            node->type = NODE_ENV_VAR;
            break;
        case TOKEN_DOUBLE_QUOTE:
            node->type = NODE_DOUBLE_QUOTE;
            break;
        case TOKEN_SINGLE_QUOTE:
            node->type = NODE_SINGLE_QUOTE;
            break;
        default:
            node->type = NODE_UNKNOWN;
            break;
        }

        while (!isEmptyStack(stack) && getPriority(peekStack(stack)) < getPriority(node))
        {
            node->left = popStack(stack);
        }

        if (!isEmptyStack(stack))
        {
            peekStack(stack)->right = node;
        }

        pushStack(stack, node);
        current = current->next;
    }

    while (getSizeStack(stack) > 1)
    {
        ASTNode *node = popStack(stack);
        peekStack(stack)->right = node;
    }

    ASTNode *root = popStack(stack);
    deleteStack(stack);
    return root;
}

void execute(ASTNode *node)
{
    int pipefd[2];
    pid_t pid;
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case NODE_COMMAND:
        // Execute the command using execve
        if (fork() == 0)
        {
            // Child process
            char *path = getenv("PATH");
            char *path_copy = strdup(path);
            char *dir = strtok(path_copy, ":");
            while (dir != NULL)
            {
                char *exec_path = malloc(strlen(dir) + strlen(node->value) + 2);
                strcpy(exec_path, dir);
                strcat(exec_path, "/");
                strcat(exec_path, node->value);
                if (access(exec_path, X_OK) == 0)
                {
                    // Found executable
                    execve(exec_path, node->args, NULL);
                    // If execve returns, there was an error
                    perror("execve");
                    exit(EXIT_FAILURE);
                }
                free(exec_path);
                dir = strtok(NULL, ":");
            }
            free(path_copy);
            // If we get here, the executable was not found
            fprintf(stderr, "Command not found: %s\n", node->value);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for child process to finish
        }
        break;
    case NODE_REDIRECT_IN:
        // Redirect input from a file
        int in = open(node->value, O_RDONLY);
        dup2(in, STDIN_FILENO);
        close(in);
        execute(node->left);
        break;
    case NODE_REDIRECT_OUT:
        // Redirect output to a file
        char *filename;
        if (node->right && node->right->type == NODE_REDIRECT_FILE)
        {
            filename = node->right->value;
        }
        else
        {
            filename = node->value;
        }
        int out = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        dup2(out, STDOUT_FILENO);
        close(out);
        execute(node->left);
        break;
    case NODE_REDIRECT_IN_APPEND:
    case NODE_REDIRECT_OUT_APPEND:
        printf("Redirecting %s\n", node->value);
        break;
    case NODE_PIPE:
        // Create a pipe and fork a new process
        pipe(pipefd);
        pid = fork();
        if (pid == 0)
        {
            close(pipefd[0]);               // close reading end in the child
            dup2(pipefd[1], STDOUT_FILENO); // send stdout to the pipe
            close(pipefd[1]);               // this descriptor is no longer needed
            execute(node->left);
        }
        else
        {
            close(pipefd[1]);              // close writing end in the parent
            dup2(pipefd[0], STDIN_FILENO); // receive input from pipe
            close(pipefd[0]);              // this descriptor is no longer needed
            execute(node->right);
        }
        break;
    case NODE_ENV_VAR:
        printf("Environment variable %s\n", node->value);
        break;
    case NODE_DOUBLE_QUOTE:
    case NODE_SINGLE_QUOTE:
        printf("Quoted string %s\n", node->value);
        break;
    default:
        printf("Unknown node type %d\n", node->type);
        break;
    }

    // Recursively execute the left and right children.
    execute(node->left);
    execute(node->right);
}

int main()
{
    char input[] = "ls -l > output.txt";
    Token *tokens = NULL;
    lex(input, &tokens);
    ASTNode *ast = parse(tokens);
    execute(ast);
    // Don't forget to free the tokens and the AST
    return 0;
}