#ifndef MYSTD_H
#define MYSTD_H

#define NOT_POSSIBLE 99
#define OK 0

template<typename QueueItemType>
class CircularQueue {
public:
	CircularQueue(int max_size);
	~CircularQueue();
	void add(QueueItemType evt);
	QueueItemType get();
	QueueItemType look_ahead(int offset);
	void remove(int count);
	int size();
private:
	int next_in;
	int next_out;
	int max_size;
	QueueItemType * queue_data;
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
CircularQueue<QueueItemType>::CircularQueue(int max_size_) {
	next_in = 0;
	next_out = 0;
	max_size = max_size_ + 1; //capacity is one element less
	queue_data = new QueueItemType[max_size];
}

template<typename QueueItemType>
CircularQueue<QueueItemType>::~CircularQueue() {
	delete[] queue_data;
}
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

	if (size() > 0) {
		QueueItemType temp = queue_data[next_out];

		next_out++;
		if (next_out >= max_size) {
			next_out = 0;
		}

		return temp;
	}

	return *new QueueItemType;
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

/**
 * Create double linked list
 */
template<typename ListItemType>
LinkedList<ListItemType>::LinkedList() {
	first_node = 0;
	last_node = 0;
	iterator = 0;
	size_int = 0;
}

/**
 * Destroy list
 */
template<typename ListItemType>
LinkedList<ListItemType>::~LinkedList() {
	while (size_int > 0) {
		this->removeLast();
	}
}

/**
 * Moves the list pointer to the next element.
 * Returns true if move was successfull or false if
 * there is no next element to move to.
 */
template<typename ListItemType>
bool LinkedList<ListItemType>::next() {
	if (iterator->next != 0) {
		iterator = iterator->next;
		return true;
	} else {
		return false;
	}
}

/**
 * Moves the list pointer to the first element of the list.
 */
template<typename ListItemType>
void LinkedList<ListItemType>::first() {
	iterator = first_node;
}

/**
 * Moves the list pointer to the last element of the list.
 */
template<typename ListItemType>
void LinkedList<ListItemType>::last() {
	iterator = last_node;
}

/**
 * Append the given item to the end of the linked list.
 */
template<typename ListItemType>
void LinkedList<ListItemType>::append(ListItemType r) {

	node *tmp = new node;
	tmp->item = r;
	tmp->prev = 0;
	tmp->next = 0;

	if (size_int == 0) {
		//first item inserted to the list
		first_node = tmp;
		iterator = tmp;

	} else {
		//append to list
		last_node->next = tmp;
		tmp->prev = last_node;
	}

	//set new last item
	last_node = tmp;
	size_int++;

}

/**
 * Returns the list item the list pointer currently points to.
 */
template<typename ListItemType>
ListItemType LinkedList<ListItemType>::get() {
	return iterator->item;
}

/**
 * Removes the item currently pointed to by the list pointer from the list.
 */
template<typename ListItemType>
void LinkedList<ListItemType>::remove() {
	if (size_int > 0) {
		node *curr_item = iterator;

		if (size_int > 1) {
			if (curr_item == last_node) {
				//last element in list deleted -> move last
				last_node = curr_item->prev;
				//alter next pointer in prev element
				curr_item->prev->next = 0;
				//move iterator to previous element
				iterator = curr_item->prev;

			}
			if (curr_item == first_node) {
				//first element in list deleted -> move first
				first_node = curr_item->next;
				//alter prev pointer in next element
				curr_item->next->prev = 0;
				//move iterator to next element
				iterator = curr_item->next;

			} else {
				//alter prev element
				curr_item->prev->next = iterator->next;
				//alter next element
				curr_item->next->prev = iterator->prev;
			}

		} else if (size_int == 1) {
			first_node = 0;
			last_node = 0;
			iterator = 0;
		}

		delete curr_item;
		size_int--;
	}
}

/**
 * Removes the last item from the linked list.
 */
template<typename ListItemType>
inline void LinkedList<ListItemType>::removeLast() {
	this->last();
	this->remove();
}

/**
 * Returns the current size of the list.
 */
template<typename ListItemType>
int LinkedList<ListItemType>::size() {
	return size_int;
}

/**
 * Returns true if the list is empty, false otherwise.
 */
template<typename ListItemType>
bool LinkedList<ListItemType>::isEmpty() {
	if (size_int == 0) {
		return true;
	} else {
		return false;
	}
}
template<class T>
class LinkedList;
template<class T>
class CircularQueue;





template<typename ArrayListItemType>
class ArrayList {
private:
	int max_size;
	int size;

	ArrayListItemType data[];

public:
	ArrayList(int max_size);
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
ArrayList<ArrayListItemType>::ArrayList(int max_size) {
	this->max_size = max_size;
	this->size = 0;
	this->data = new ArrayListItemType[max_size];
}

/**
 * Destroy list
 */
template<typename ArrayListItemType>
ArrayList<ArrayListItemType>::~ArrayList() {
	delete[] data;
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
    if(position > getSize() - 1){
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
	if (getSize() >= max_size + 1){
		return NOT_POSSIBLE;
	} else {
		for(int i = insert_position; i < getSize(); i++){
			data[(i+1)] = data[i];
		}
		data[insert_position] = item;
		size++;
		return OK;
	}
}

template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::append(ArrayListItemType item) {
	return insertAt(getSize(), item);
}
/**
 * removes the element at the given position
 */
template<typename ArrayListItemType>
int ArrayList<ArrayListItemType>::remove(int position){
    if(position > getSize() - 1){
        return NOT_POSSIBLE;
    } else {
        for(int i = position; i < getSize(); i++){
            data[i] = data[(i+1)];
            size--;
        }
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

