template <typename T>
LinkedQueue<T>::LinkedQueue() {
    this->head = nullptr;
    this->last = nullptr;
    this->length = 0;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    this->head = nullptr;
    this->last = nullptr;
    this->length = 0;
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
T LinkedQueue<T>::front() const {
    if (isEmpty())
        throw string("error, queue is empty, cannot access the front");
    return this->head->value;
}

template <typename T>
T LinkedQueue<T>::back() const {
    if (isEmpty())
        throw string("error, queue is empty, cannot access the back");
    return this->last->value;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem) {
    Node* newNode = new Node(elem);
    if (isEmpty()) {
        this->head = newNode;
        this->last = newNode;
    } else {
        this->last->next = newNode;
        this->last = newNode;
    }
    this->length++;
}

template <typename T>
void LinkedQueue<T>::dequeue() {
    if (isEmpty())
        throw string("error, queue is empty, cannot dequeue");
    Node* temp = this->head;
    this->head = this->head->next;
    if (this->head == nullptr)
        this->last = nullptr;
    delete temp;
    this->length--;
}

template <typename T>
void LinkedQueue<T>::clear() {
    while (!isEmpty())
        dequeue();
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    Node* curr = copyObj.head;
    while (curr != nullptr) {
        enqueue(curr->value);
        curr = curr->next;
    }
}

template <typename T>
int LinkedQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return this->length == 0;
}