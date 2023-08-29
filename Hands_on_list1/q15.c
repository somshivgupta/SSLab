#include <stdio.h>
#include <stdlib.h>

extern char **environ;
 
int main()
{
    for (char **envp = environ; *envp != NULL; envp++)
        printf("\n%s", *envp);
    getchar();
    return 0;
}
