#ifndef MW_CIRCULAR_QUEUE_H
#define MW_CIRCULAR_QUEUE_H

typedef struct {
	int max_size;
	int read;
	int write;
	int size;
} mw_circular_queue_t;

void mw_circular_queue_init(mw_circular_queue_t* q, int max_size);

int mw_circular_queue_enqueue(mw_circular_queue_t* q);

int mw_circular_queue_dequeue(mw_circular_queue_t* q);

int mw_circular_queue_peek(const mw_circular_queue_t* q);

int mw_circular_queue_is_full(const mw_circular_queue_t* q);

#endif
