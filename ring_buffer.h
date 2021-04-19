/*
 FIFO
 ===============================================
 -- first : the last popped data pointer
 -- last  : the last pushed data pointer
 -- if empty , first == last
 -- if full, (last + 1) / QUEUE_SIZE == first
 -- the elements can be save is QUEUE_SIZE - 1
 ===============================================
 */
#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <ctype.h>
#include "stdio.h"
// uint32_t
#include <stdint.h>
// strlen(); memcpy()
#include <string.h>
//#include <stdio.h>
//#include <stddef.h>

// array size 2048 + 65
#define QUEUE_SIZE 2112
// real availabledata count
#define QUEUE_AVAILABLE_MAX (QUEUE_SIZE -1)
class MyQueue
{
public:
	uint32_t first; // the last popped data pointer
	uint32_t last; // the last pushed data pointer
	char elements[QUEUE_SIZE];

	MyQueue();
	MyQueue(char chr);
	bool IsQueueFull();
	bool IsQueueEmpty();
	uint32_t Available();
	uint32_t Count();
	uint8_t EnQueue(char c);
	uint32_t EnQueue(char *str, uint32_t len);
	uint8_t DeQueue(char *buff);
	uint32_t DeQueue(char *buff, uint32_t len);
	bool ReadLine(char *buff);
};

void print_queue(MyQueue _queue);

#ifdef __cplusplus
}
#endif
#endif //__RING_BUFFER_H
