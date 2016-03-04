#ifndef MYSTD_H
#define MYSTD_H

#define NOT_POSSIBLE 99
#define OK 0

#ifndef NULL
    #define NULL 0
#endif

template<typename QueueItemType>
class CircularQueue {
public:
	CircularQueue(QueueItemType data[], int max_size);
	//~CircularQueue();
	void add(QueueItemType evt);
	QueueItemType get();
	QueueItemType look_ahead(int offset);
	void remove(int count);
	int size();
private:
	int next_in;
	int next_out;
	int max_size;
	QueueItemType* queue_data;
};

template<typename ListItemType>
class LinkedList {
	struct node {
		ListItemType item;
		node* next;
		node* prev;
	};
private:
	node* first_node;
	node* last_node;
	node* iterator;
	int size_int;

	void removeLast();

public:
	LinkedList();
	~LinkedList();

	bool next();
	void first();
	void last();

	void append(ListItemType r);
	ListItemType get();
	void remove();

	int size();
	bool isEmpty();

};
/**
 * Create a new circular queue (circular buffer) with the given max_size.
 * The queue works first in, first out.
 */
template<typename QueueItemType>
CircularQueue<QueueItemType>::CircularQueue(QueueItemType data[], int max_size_) {
	next_in = 0;
	next_out = 0;
	max_size = max_size_ + 1; //capacity is one element less
	queue_data = data;
}

/*template<typename QueueItemType>
CircularQueue<QueueItemType>::~CircularQueue() {
	delete[] queue_data;
    queue_data = NULL;
}*/
/**
 * Add the given item to the current end of the circular queue.
 */
template<typename QueueItemType>
void CircularQueue<QueueItemType>::add(QueueItemType itm) {

	//if queue is full the oldest input gets overwritten
	if (size() >= max_size - 1) {
		next_out++;
		if (next_out >= max_size) {
			next_out = 0;
		}
	}

	queue_data[next_in] = itm;

	next_in++;
	if (next_in >= max_size) {
		next_in = 0;
	}
}

/**
 * Returns the oldest (foremost) item within the queue and REMOVEs it from the queue.
 */
template<typename QueueItemType>
QueueItemType CircularQueue<QueueItemType>::get() {
//todo removed sizecheck
    QueueItemType temp = queue_data[next_out];

    next_out++;
    if (next_out >= max_size) {
        next_out = 0;
    }

    return temp;
}

/**
 * returns the next element in the queue specified by offset
 */
template<typename QueueItemType>
QueueItemType CircularQueue<QueueItemType>::look_ahead(int offset) {

	if (size() > offset) {
		int item_wanted = next_out + offset;
		if(item_wanted >= max_size){
			item_wanted = item_wanted - max_size;
		}

		QueueItemType temp = queue_data[item_wanted];

		return temp;
	}

	return *new QueueItemType;
}

/**
 * Removes the next "count" items from the queue
 */
template<typename QueueItemType>
void CircularQueue<QueueItemType>::remove(int count) {
	int temp_next_out = next_out + count;
	if (temp_next_out >= max_size) {
		next_out = temp_next_out - max_size;
	} else {
		next_out = temp_next_out;
	}
}


/**
 * Returns the number of elements within the queue.
 */
template<typename QueueItemType>
int CircularQueue<QueueItemType>::size() {
	if (next_in > next_out) {
		return next_in - next_out;

	} else if (next_in < next_out) {
		return (max_size - next_out) + next_in;
	}

	return 0;
}

template<class T>
class CircularQueue;

template<typename ArrayListItemType>
class ArrayList {
private:
	int max_size;
	int size;

	ArrayListItemType* data;

public:
	ArrayList(ArrayListItemType data[], int max_items);
	~ArrayList();

	int insertAt(int insert_position, ArrayListItemType item);
	int append(ArrayListItemType item);
    int remove(int position);
    int set(int position, ArrayListItemType item);
	ArrayListItemType get(int position);

	int getSize();
	bool isEmpty();

};

/**
* Create array list
*/
template<typename ArrayListItemType>
ArrayList<ArrayListItemType>::ArrayList(ArrayListItemType data[], int max_items) {
	this->max_size = max_items;
	this->size = 0;
    this->data = data;
}

/**
 * Destroy list
 */
template<typename ArrayListItemType>
ArrayList<ArrayListItemType>::~ArrayList() {
}

/**
 * Get the wanted element
 */
template<typename ArrayListItemType>
ArrayListItemType ArrayList<ArrayListItemType>::get(int position) {
	return data[position];
}
/**
 * set (overwrite) the element in the given position
 */
template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::set(int position, ArrayListItemType item){
    if(position > size - 1){
        return NOT_POSSIBLE;
    } else {
        data[position] = item;
        return OK;
    }
}

/**
 * Moves the list pointer to the last element of the list.
 */
template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::insertAt(int insert_position, ArrayListItemType item) {
	if (size + 1 >= max_size ){
		return NOT_POSSIBLE;
	} else {
		for(int i = insert_position; i < size; i++){
			data[(i+1)] = data[i];
		}
		data[insert_position] = item;
		size++;
		return OK;
	}
}

template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::append(ArrayListItemType item) {
	return insertAt(size, item);
}
/**
 * removes the element at the given position
 */
template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::remove(int position){
    if(position > size - 1){
        return NOT_POSSIBLE;
    } else {
        for(int i = position; i < (size-1); i++){
            data[i] = data[(i+1)];
        }
        size--;
        return OK;
    }

}


/**
 * Returns the current size of the list.
 */
template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::getSize() {
	return size;
}

/**
 * Returns true if the list is empty, false otherwise.
 */
template<typename ArrayListItemType>
bool ArrayList<ArrayListItemType>::isEmpty() {
	if (size == 0) {
		return true;
	} else {
		return false;
	}
}

template<class T>
class ArrayList;

#endif /*MYSTD_H*/

