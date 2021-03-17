// based on an example by mykter

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define INPUTSIZE 100
enum ErrorCode
{
    Error = -1,
    Snake = 1,
    Head,
};

char *out;
char *rest;
int len, err;

int process(char *input)
{
    if (strncmp(input, "snake ", 6) == 0)
    {
        err = Snake;
        len = strtol(input + 6, &rest, 10);    // how many characters of the string to retain
        
        if (len < 0)
        {
            printf("Specified length %d must be positive!\n", len);
            return Error;
        }
        
        rest += 1;                             // skip the first char (should be a space)
        out = malloc(strlen(input) * 2 + len); // could be shorter, but play it safe
        if (len > INPUTSIZE * 2)
        {
            printf("Specified length %d was too large!\n", len);
            free(out);
            return Error;
        }
        else if (out == NULL)
        {
            printf("Failed to allocate memory\n");
            return Error;
        }

        int i = 0, j = 0;
        while (j < len)
        {
            if (rest[i] == '\n')
                break;
            if (rest[i] >= 'A' && rest[i] <= 'Z')
            {
                if (j > 0)
                    out[j++] = '_';
                out[j++] = rest[i++] + 32;
            }
            else
            {
                out[j++] = rest[i++];
            }
        }
        out[len] = '\0';
    }
    else if (strncmp(input, "head ", 5) == 0)
    {
        err = Head;
        if (strlen(input) > 6)
        {
            len = strtol(input + 5, &rest, 10);
            rest += 1;        // skip the first char (should be a space)

            // do not return more than the max # of bytes in <string>
            if (len > strlen(rest))
                len = strlen(rest);

            rest[len] = '\0'; // truncate string at specified offset
        }
        else
        {
            printf("Head input was too small!\n");
            return Error;
        }
    }
    else
    {
        err = Error;
    }

    return err;
}

int main(int argc, char *argv[])
{
    char *usage = "Usage: %s\n"
                  "String utility - accepts data on stdin and prints results to stdout.\n"
                  "\tInput              | Output\n"
                  "\t-------------------+-----------------------\n"
                  "\tsnake <N> <string> | Transform <string> into snake_case for up to <N> bytes.\n"
                  "\thead <N> <string>  | The first <N> bytes of <string>.\n";

    char input[INPUTSIZE] = {0};

    if (read(STDIN_FILENO, input, INPUTSIZE) < 0)
    {
        fprintf(stderr, "Couldn't read stdin.\n");
    }

    int ret = process(input);
    if (ret == Snake && *out)
    {
        printf("%s\n", out);
        free(out);
    }
    else if (ret == Head)
    {
        printf("%s\n", rest);
    }
    else if (ret == Error)
    {
        fprintf(stderr, usage, argv[0]);
    }

    return ret;
}
