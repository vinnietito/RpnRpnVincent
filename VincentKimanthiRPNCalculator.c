        //VINCENT KIMANTHI NJUGUNA
        //SCT221-0690/2022

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int top;
    unsigned capacity;
    int* array;
} Stack;


Stack* createStack(unsigned capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}


void push(Stack* stack, int item)
{
    stack->array[++stack->top] = item;
}

int pop(Stack* stack)
{
    return stack->array[stack->top--];
}

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    else
        return 0;
}


void infixToPostfix(char* infix, char* postfix)
{
    Stack* stack = createStack(strlen(infix));
    int i, k;
    for (i = 0, k = -1; infix[i]; ++i) {
        if (isalnum(infix[i])) 
            postfix[++k] = infix[i];
        else if (infix[i] == '(') 
            push(stack, infix[i]);
        else if (infix[i] == ')') 
		{ 
            while (stack->top != -1 && stack->array[stack->top] != '(')
                postfix[++k] = pop(stack);
            if (stack->top != -1 && stack->array[stack->top] != '(')
                return;
            else
                pop(stack);
        } else 
		{ 
        
            while (stack->top != -1 && precedence(infix[i]) <= precedence(stack->array[stack->top]))
                postfix[++k] = pop(stack);
            push(stack, infix[i]);
        }
    }
    while (stack->top != -1)
        postfix[++k] = pop(stack);
    postfix[++k] = '\0';
}


int evaluatePostfix(char* postfix)
{
    Stack* stack = createStack(strlen(postfix));
    int i;
    for (i = 0; postfix[i]; ++i)
	{
        if (isdigit(postfix[i]))
            push(stack, postfix[i] - '0');
        else { 
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (postfix[i]) 
			{
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
                case '%':
                    push(stack, operand1 % operand2);
                    break;
            }
        }
    }
    return pop(stack);
}

int main() {
    char infix[100];
    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';  

    char postfix[100];
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}

