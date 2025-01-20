#include <iostream>
using namespace std;

template <class Type>
class Queue {
private:
    Type* queue;   // Pointer to dynamic array
    int front, rear, count, MaxSize;

public:
    Queue(int nelements = 128) {
        queue = new Type[nelements];
        front = 0;
        rear = -1;
        count = 0;
        MaxSize = nelements;
    }

    Queue(const Queue<Type>& original) : MaxSize(original.MaxSize), front(original.front), rear(original.rear), count(original.count)
    {
        queue = new Type[MaxSize];

        for (int i = 0; i < MaxSize; i++)
        {
            queue[i] = original.queue[i];
        }
    }

    ~Queue() {
        delete[] queue;
    }

    void enqueue(Type el) {
        if (count == MaxSize) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % MaxSize;
        queue[rear] = el;
        count++;
    }

    void dequeue(Type& el) {
        if (count == 0) {
            cout << "Queue is empty!" << endl;
            return;
        }
        el = queue[front];
        front = (front + 1) % MaxSize;
        count--;
    }

    bool IsEmpty() const {
        return count == 0;
    }

    int Length() const {
        return count;
    }
};

template <class T>
class StackLinkedList {
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* topNode;
    int count;
public:
    StackLinkedList() : topNode(nullptr), count(0) {}
    ~StackLinkedList()
    {
        Node* temp;
        while (topNode)
        {
            temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
    void Push(const T& data) {
        Node* newNode = new Node(data);
        newNode->next = topNode;
        topNode = newNode;
        ++count;
    }

    void Pop(T& el) {
        if(IsEmpty())
        {
            cout << "Stack Is Empty. cannot pop." << endl;
            return;
        }
        el = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    T Top() {
        if (IsEmpty())
        {
            throw underflow_error("Stack is empty: No top element.");
        }
        return topNode->data;
    }

    bool IsEmpty() const {
        return topNode == nullptr;
    }

    int Size() const {
        return count;
    }
};


// Reverse the queue using a stack
template<class T>
void ReverseQueue(Queue<T>& q)
{
    StackLinkedList<T> stk;
    T el;
    while (!q.IsEmpty())
    {
        q.dequeue(el);
        stk.Push(el);
    }
    
    while (!stk.IsEmpty())
    {
        stk.Pop(el);
        q.enqueue(el);
    }
}

template<class T>
void PrintQueue(const Queue<T>& q)
{
    Queue<T> temp = q; // use copy constructor

    T el;
    cout << "{ ";
    while (!temp.IsEmpty())
    {
        temp.dequeue(el);
        cout << el << ", ";
    }
    cout << "}\n";
}


// A queue (Q) contains an even number of elements. Write a
// function Split (Q,Q1,Q2) to copy the 1st half of (Q) into (Q1) and
// the 2nd half into (Q2), leaving the original queue unchanged.
void SplitQueue(const Queue<int>& Q, Queue<int>& Q1, Queue<int>& Q2)
{
    Queue<int> temp = Q; // using copy constructor
    int length = temp.Length()/2;

    int el;
    for (int i = 0; i < length; i++)
    {
        temp.dequeue(el);
        Q1.enqueue(el);
    }
    
    length = temp.Length();

    for (int i = 0; i < length; i++)
    {
        temp.dequeue(el);
        Q2.enqueue(el);
    }
}


// Write a recursive function Append (Q1,Q2) to append a queue
// (Q2) to the end of a queue (Q1), leaving Q2 empty.
void Append(Queue<int>& Q1, Queue<int>& Q2)
{
    if(Q2.IsEmpty())
        return;

    int el;
    Q2.dequeue(el);
    Q1.enqueue(el);
    Append(Q1, Q2);
}

// Write a function NthElement (Q) to return the nth element in a
// queue (Q), leaving the queue without that element.
template< class T>
T NthElement(Queue<T>& q, int nthElement)
{
    int length = q.Length();
    T el;
    T result;
    for (int i = 1; i <= length; i++)
    {
        if(i != nthElement)
        {
            q.dequeue(el);
            q.enqueue(el);
        }
        
        if(i == nthElement)
            q.dequeue(result);
    }
    return result;

}

// Write a boolean function EqualQueues ( Q1 , Q2 ) which receives
// two queues Q1 and Q2 and returns True if they are identical and
// False otherwise. The function should leave the queues unchanged.
bool EqualQueues(const Queue<int>& Q1, const Queue<int>& Q2)
{
    if(Q1.Length() != Q2.Length()) 
        return false;

    Queue<int> Q3 = Q1; // use copy constructor
    Queue<int> Q4 = Q2; // use copy constructor
    int el1, el2;
    while(!Q3.IsEmpty() && !Q4.IsEmpty())
    {
        Q3.dequeue(el1);
        Q4.dequeue(el2);
        if(el1 != el2)
            return false;
    }
    return true;
}

// Implement a method that find the minimum item in a queue
// without changing the queue elements.
int FindMinItem(const Queue<int>& q)
{
    Queue<int> temp(q);
    int el;
    int min;
    temp.dequeue(min);

    while (!temp.IsEmpty())
    {
        temp.dequeue(el);
        if(el < min)
            min = el;
    }
    return min;
}

// Implement a method that find the maximum item in a queue
// without changing the queue elements.
int FindMaxItem(const Queue<int>& q)
{
    Queue<int> temp(q);
    int el;
    int max;
    temp.dequeue(max);

    while (!temp.IsEmpty())
    {
        temp.dequeue(el);
        if(el > max)
            max = el;
    }
    return max;
}


void SplitEvenOdd(Queue<int>& Q, Queue<int>& evenQueue, Queue<int>& oddQueue) {
    int size = Q.Length();
    int element;
    for (int i = 0; i < size; i++) {
        Q.dequeue(element);

        if (element % 2 == 0) {
            evenQueue.enqueue(element);
        } else {
            oddQueue.enqueue(element);
        }

        Q.enqueue(element);
    }
}

int main() {
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.enqueue(6);

    cout << "q1 elements:\n";
    PrintQueue(q1);

    ReverseQueue(q1);

    cout << "\nq1 elements after reverse:\n";
    PrintQueue(q1);

    Queue<int> q2, q3;

    SplitQueue(q1, q2, q3);

    cout << "\nq2 elements:\n";
    PrintQueue(q2);

    cout << "\nq3 elements:\n";
    PrintQueue(q3);

    cout << q1.Length() << endl;
    cout << "the fifth element in q1: " << NthElement(q1, 5) << endl;

    cout << "\nq1 elements:\n";
    PrintQueue(q1);

    cout << "\n min element in q1: " << FindMinItem(q1) << endl;
    cout << "\n max element in q1: " << FindMaxItem(q1) << endl;

    Queue<int> evenQueue, oddQueue;

    SplitEvenOdd(q1, evenQueue, oddQueue);

    cout << "\nq1 elements:\n";
    PrintQueue(q1);

    cout << "\nevenQueue elements:\n";
    PrintQueue(evenQueue);

    cout << "\noddQueue elements:\n";
    PrintQueue(oddQueue);
}

