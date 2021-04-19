#include "ring_buffer.h"

MyQueue::MyQueue()
{
	first = 0;
	last = 0;
	memset(elements, 0x00, MAX_CMD_LENQUEUE_SIZE);
//    for (int i = 0; i < QUEUE_SIZE; i++)
//    {
//        elements[i] = 0;
//    }
}

// Initial buffer with specified char
MyQueue::MyQueue(char chr)
{
	first = 0;
	last = 0;
	memset(elements, chr, MAX_CMD_LENQUEUE_SIZE);
//	for (int i = 0; i < QUEUE_SIZE; i++)
//	{
//		elements[i] = chr;
//	}
}

// check queue empty
bool MyQueue::IsQueueEmpty()
{
	return (first == last);
}

// check queue full
bool MyQueue::IsQueueFull()
{
	uint32_t next = (last + 1) % QUEUE_SIZE;
	return (next == first);
}

// if push successful, return 1, else 0
uint8_t MyQueue::EnQueue(char c)
{
	uint32_t next;
	if (IsQueueFull())
		return 0;
	next = (last + 1) % QUEUE_SIZE;
	last = next;
	elements[last] = c;
	return 1;
}

// return: real data been copied
uint32_t MyQueue::EnQueue(char *str, uint32_t len)
{
	uint32_t available = Available();
	if (available == 0)
		return 0;
	else
	{
		// clamp len
		if (len > available)
			len = available;

		if (first > last)
		{
			memcpy(elements + last + 1, str, len);
			last += len;
			return len;
		}
		else
		{
			uint32_t len_copied = QUEUE_AVAILABLE_MAX - last;
			if (len <= len_copied)
			{
				memcpy(elements + last + 1, str, len);
				last += len;
			}
			else
			{
				memcpy(elements + last + 1, str, len_copied);
				uint32_t len_remained = len - len_copied;
				memcpy(elements, str + len_copied, len_remained);
				last = len_remained - 1;
			};
			return len;
		}
	}
}

// if queue empty, return 0, else return 1
uint8_t MyQueue::DeQueue(char *buff)
{
	if (IsQueueEmpty())
		return 0;         // queue empty

	first++;
	first %= QUEUE_SIZE;

	*buff = elements[first];
	return 1;
}

// return real read data
uint32_t MyQueue::DeQueue(char *buff, uint32_t len)
{
	if (IsQueueEmpty())
		return 0;         // queue empty

	if (last > first)
	{
		if (len > Count())
		{
			len = Count();
		}
		memcpy(buff, elements + first + 1, len);
		first += len;
		return len;
	}
	else
	{
		uint32_t len_copied = QUEUE_AVAILABLE_MAX - first;
		if (len <= len_copied)
		{
			// if the request number <= QUEUE_AVAILABLE_MAX - first,
			// just coopy the request nuber of data
			memcpy(buff, elements + first + 1, len);
			first += len;
			return len;
		}
		else
		{
			// copy the data from first + 1 to the end of array
			memcpy(buff, elements + first + 1, len_copied);
			//  calculate the remaining data count
			uint32_t len_tobe_copied = len - len_copied;
			// clamp the data count
			if (len_tobe_copied > (last + 1))
				len_tobe_copied = last + 1;
			// copy the remaining data from the begin of array to last
			memcpy(buff + len_copied, elements, len_tobe_copied);
			first = len_tobe_copied - 1;
			return (len_copied + len_tobe_copied);
		}
	}
}

// read string until \n
bool MyQueue::ReadLine(char *buff)
{
	if (IsQueueEmpty())
		return false;

	uint32_t next = first;
	if (last > first)
	{
		while (true)
		{
			if (++next > last)
			{
				return false;
			}
			if (elements[next] == '\n')
			{
				memcpy(buff, elements + first + 1, next - first);
				first = next;
				return true;
			}
		}
	}
	else
	{
		while (true)
		{
			if (++next > QUEUE_AVAILABLE_MAX)
			{
				next = 0;
			}

			if ((next > last) && (next < first))
			{
				return false;
			}

			if (elements[next] == '\n')
			{
				if (next > first)
				{
					memcpy(buff, elements + first + 1, next - first);
				}
				else
				{
					memcpy(buff, elements + first + 1,
							QUEUE_AVAILABLE_MAX - first);
					memcpy(buff + QUEUE_AVAILABLE_MAX - first, elements,
							next + 1);
				}
				first = next;
				return true;
			}
		}
	}
}

////// available to push
uint32_t MyQueue::Available()
{
	if (IsQueueEmpty())
		return QUEUE_AVAILABLE_MAX;
	else if (IsQueueFull())
		return 0;
	else
	{
		if (last > first)
			return (QUEUE_AVAILABLE_MAX - (last - first)); // max size is QUEUE_SIZE - 1
		else
			return (first - last - 1);
	}
}

////// saved data count
uint32_t MyQueue::Count()
{
	return QUEUE_AVAILABLE_MAX - Available();
}

void print_queue(MyQueue _queue)
{
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("---");
	}
	printf("\n");
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("%02d", i);
		if (i != QUEUE_AVAILABLE_MAX)
			printf(",");
	}
	printf("\n");

	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("---");
	}
	printf("\n");
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("%02X", _queue.elements[i]);
		if (i != QUEUE_SIZE - 1)
			printf(",");
	}
	printf("\n");
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("---");
	}
	printf("\n");

	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		if ((_queue.elements[i]) != '\n')
		{
			if (isascii(_queue.elements[i]))
				printf("%2c", _queue.elements[i]);
			else
				printf("  ");
		}
		else
			printf("\\n");

		if (i != QUEUE_SIZE - 1)
			printf(",");
	}
	printf("\n");
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		printf("---");
	}
	printf("\n");

	printf("==>first:last:available:count = %d : %d : %d : %d\n", _queue.first,
			_queue.last, _queue.Available(), _queue.Count());
	printf("\n");
}
