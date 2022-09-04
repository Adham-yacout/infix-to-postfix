#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
infix and postfix converter using stacks
*/
typedef union
{
    float f;
    char  c;
} item; // a union to choose whether we are dealing with floats or characters
typedef struct
{
    item items[100];
    int top;
} stack; //our stack
stack *initialize()
{
    stack *s=malloc(sizeof(stack));
    s->top=0;
    return s;
} //stack initializer
int isEmpty(stack *s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
} //function to check whether stack is empty or not
int full(stack*s) // function to check if stack is full
{
    if(s->top==100)
        return 1;
    else
        return 0;
}
item top(stack *s)
{
    return s->items[s->top-1];
} //return top of the stack

item pop(stack *s)
{
    item val;
    s->top--;
    val=s->items[s->top];
    return val;
}
void push(stack *s, item val)
{
    s->items[s->top]=val;
    s->top++;

}
float evaluate(char x,float a,float b) //function used as a calculator
{
    if (x=='+')
        return (a+b);
    else if (x=='-')
        return (a-b);
    else if (x=='/')
        return (a/b);
    else if (x=='%')
        return (fmod(a,b));
    else if (x=='*')
        return (a*b);
    else if (x=='^')
        return (pow(a,b));
    else
        return 0;
}
int priority(char c) //maths priority checker
{
    switch(c)
    {
    case('*'):
    case '/':
    case '%':
        return 1;
    case '+':
    case '-':
        return 0;
    case '(':
        return 3;
    case '^':
        return 2;

    }
}

void infixToPostfix(char* infix, char* postfix)
{
    stack*s=initialize();
    char*token=strtok(infix," "); //strtok function to divide our string and start pushing in stack to convert to postfix
    while(token!=NULL)
    {

        if(isdigit(token[0]) || (token[0]=='-' && strlen(token)>1)) //checking if first character is a digit ot a egative number and string greater than 1
        {
            if(postfix==NULL)
            {
                strcpy(postfix,token);//copies content of token to postfix
                strcat(postfix," ");
            }
            else
            {
                strcat(postfix,token); //concatenates content of token to postfix
                strcat(postfix," ");
            }
        }
        else if (token[0]==')') //we reached an end of the open bracket a matematical operation should be handled
        {
            while(!isEmpty(s)&&top(s).c!='(') //untill reaching the open bracket
            {
                char temp[2];
                temp[0]=pop(s).c;
                temp[1]='\0';
                strcat(postfix,temp);
                strcat(postfix," ");
            }
            pop(s); //pop the (


        }
        else if (isEmpty(s))
        {
            item y;
            y.c=token[0];
            push(s,y);
        }
        else
        {
            while(!isEmpty(s) && priority(top(s).c)>=priority(token[0]) && top(s).c!='(')
            {
                char temp[2];
                temp[0]=pop(s).c;
                temp[1]='\0';
                strcat(postfix,temp);
                strcat(postfix," ");
            }
            item y;
            y.c=token[0];
            push(s,y);
        }
        token=strtok(NULL," ");
    }
    while(!isEmpty(s))
    {
        char temp[2];
        temp[0]=pop(s).c;
        temp[1]='\0';

        strcat(postfix,temp);
        strcat(postfix," ");
    }
}
float evaluatepostfix(char*postfix)
{
    stack*s=initialize();
    float a,b,val;
    char *token=strtok(postfix," ");
    while(token!=NULL)
    {
         if(isdigit(token[0]) || (token[0]=='-' && strlen(token)>1))
         {
             item x;
             x.f=atof(token); //convert to string
             push(s,x);
         }
         else {
        b=pop(s).f;
        a=pop(s).f;
        item z;
         z.f=evaluate(token[0],a,b);
         push(s,z);}


    token=strtok(NULL," ");
    }
    val=pop(s).f;
    strcpy(postfix," ");
return val;
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("please enter epressions with spaces i between\n");
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: \n");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatepostfix(postfixExpr);
         printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
