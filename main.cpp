#include <iostream>

using namespace std;

#include "my_queue.h"

MyQueue fifo;

char test_str[16] = "test_fifo";

int cnt = 0;
int temp;
char buffer[64] = {0};
char data = '0';;

void test1();
void test2();

int main()
{
    cout << "FIFO Test" << endl;
    print_queue(fifo);
    test2();

    return 0;
}

void test1()
{
    // push 40 data to queue
    printf("==== push 40 data\n");
    for (int i = 0; i < 40; i++)
    {
        if (fifo.EnQueue(i + 17) == 0)
        {
            printf("queue full at i = %d\n", i);
            break;
        }
    }
    print_queue(fifo);

    // pop all queue
    printf("==== pop all queue\n");
    cnt = 0;
    while (true)
    {
        if (fifo.IsQueueEmpty())
        {
            printf("\ntotal cnt = %d\n", cnt);
            break;
        }
        else
        {
            fifo.DeQueue(&data);
            printf("%02X,", data);
            cnt ++;
        }
    }
    print_queue(fifo);

    // push 40 data to queue again
    printf("==== push 40 data\n");
    for (int i = 0; i < 40; i++)
    {
        if (fifo.EnQueue(i + 17) == 0)
        {
            printf("queue full at i = %d\n", i);
            break;
        }
    }
    print_queue(fifo);

    // pop all queue
    printf("==== pop all queue\n");
    cnt = 0;
    while (true)
    {
        if (fifo.IsQueueEmpty())
        {
            printf("\ntotal cnt = %d\n", cnt);
            break;
        }
        else
        {
            fifo.DeQueue(&data);
            printf("%02X,", data);
            cnt ++;
        }
    }
    print_queue(fifo);

    // push 31 data to queue again
    printf("==== push 31 data\n");
    for (int i = 0; i < 31; i++)
    {
        if (fifo.EnQueue(i + 17) == 0)
        {
            printf("queue full at i = %d\n", i);
            break;
        }
    }
    print_queue(fifo);

    // copy string
    printf("copy %d data from string to fifo\n", fifo.EnQueue(test_str, strlen(test_str)));
    print_queue(fifo);

    // pop 5 data
    printf("==== pop 5 data\n");
    for (int i = 0; i < 5; i++)
    {
        if (fifo.DeQueue(&data) == 0)
        {
            printf("\ntotal cnt = %d\n", i);
            break;
        }
        else
        {
            printf("%02X,", data);
        }
        printf("\n");
    }
    print_queue(fifo);

    // copy string
    printf("copy %d data from string to fifo\n", fifo.EnQueue(test_str, strlen(test_str)));
    print_queue(fifo);


    // pop 10 data
    printf("==== pop 10 data\n");
    for (int i = 0; i < 10; i++)
    {
        if (fifo.DeQueue(&data) == 0)
        {
            printf("\ntotal cnt = %d\n", i);
            break;
        }
        else
        {
            printf("%02X,", data);
        }
        printf("\n");
    }
    print_queue(fifo);

    // copy string
    printf("copy %d data from string to fifo\n", fifo.EnQueue(test_str, strlen(test_str)));
    print_queue(fifo);

    // pop 12 data
    printf("==== pop 12 data\n");
    for (int i = 0; i < 12; i++)
    {
        if (fifo.DeQueue(&data) == 0)
        {
            printf("\ntotal cnt = %d\n", i);
            break;
        }
        else
        {
            printf("%02X,", data);
        }
        printf("\n");
    }
    print_queue(fifo);

    // copy string with size 6
    printf("copy %d data from string to fifo\n", fifo.EnQueue(test_str, 6));
    print_queue(fifo);

    // pop 12 data
    printf("pop %d data from fifo\n", fifo.DeQueue(buffer, 12));
    print_queue(fifo);

    // pop 25 data
    printf("pop %d data from fifo\n", fifo.DeQueue(buffer, 25));
    print_queue(fifo);
}

void test2()
{
    char command[64] = {0};
    char cmd1[20] = "test cmd1\n";
    char cmd2[20] = "test cmd2\n";


    for (int i = 0; i < 10; i++)
    {
        // push commands

        printf("\ni = %d Available = %d Write Command1\n", i, fifo.Available());
        if (fifo.EnQueue(cmd1, strlen(cmd1)) < strlen(cmd1))
            printf("Buffer Full!!\n");

        printf("Available = %d Write Command2\n", fifo.Available());
        if (fifo.EnQueue(cmd2, strlen(cmd2)) < strlen(cmd2))
            printf("Buffer Full!!\n");

        printf("Available = %d\n", fifo.Available());
        if (fifo.ReadLine(command) == false)
        {
            printf("No commands!!\n",fifo.Available());
        }
        else
            printf("----%s",command);
        printf("Available = %d\n", fifo.Available());
    }

    while (true)
    {
        if (fifo.ReadLine(command) == false)
        {
            printf("No commands!!\n");
            break;
        }
        printf("----%s\n",command);
    }
}
