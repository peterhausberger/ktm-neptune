#include "mw_circular_queue.h"

void mw_circular_queue_init(mw_circular_queue_t* q, int max_size) {
	q->max_size = max_size;
	q->read = 0;
	q->write = 0;
	q->size = 0;
}

int mw_circular_queue_enqueue(mw_circular_queue_t* q) {
	if (mw_circular_queue_is_full(q)) mw_circular_queue_dequeue(q); // Clear oldest element.
	int w = q->write;
	q->write = q->write + 1;
	if (q->write == q->max_size) q->write = 0;
	q->size = q->size + 1;
	return w;
}

int mw_circular_queue_dequeue(mw_circular_queue_t* q) {
	if (q->size == 0) return -1;
	int r = q->read;
	q->read = q->read + 1;
	if (q->read == q->max_size) q->read = 0;
	q->size = q->size - 1;
	return r;
}

int mw_circular_queue_peek(const mw_circular_queue_t* q) {
	if (q->size == 0) return -1;
	return q->read;
}

int mw_circular_queue_is_full(const mw_circular_queue_t* q) {
	return (q->size >= q->max_size);
}
