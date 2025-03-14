#include <iostream>
#include <list>

using namespace std;

class Queue_LinkedList
{
private:
    list<int> data;

public:
    Queue_LinkedList() {}
    void enqueue(int value)
    {
        data.push_back(value);
    }
    int dequeue()
    {
        int result = data.front();
        data.pop_front();
        return result;
    }
    bool empty()
    {
        return data.size() == 0;
    }
};

class Queue_Array
{
private:
    int data[100];
    int writeIndex;
    int readIndex;
    int size;

public:
    Queue_Array()
    {
        writeIndex = 0;
        readIndex = 0;
        size = 100;
    }
    void enqueue(int value)
    {
        if ((writeIndex + 1) % size == readIndex)
        {
            cout << "queue full";
            exit(EXIT_FAILURE);
        }
        data[writeIndex] = value;
        writeIndex = (writeIndex + 1) % size;
    }
    int dequeue()
    {
        if (readIndex == writeIndex)
        {
            cout << "queue empty";
            exit(EXIT_FAILURE);
        }
        int result = data[readIndex];
        readIndex = (readIndex + 1) % size;
        return result;
    }
    bool empty()
    {
        return readIndex == writeIndex;
    }
};

int main()
{
    Queue_LinkedList q1;
    Queue_Array q2;

    cout << "Testing Queue_LinkedList\n";
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    while (!q1.empty())
    {
        cout << q1.dequeue() << " ";
    }
    cout << "\n";

    cout << "Testing Queue_Array\n";
    q2.enqueue(10);
    q2.enqueue(20);
    q2.enqueue(30);
    while (!q2.empty())
    {
        cout << q2.dequeue() << " ";
    }
    cout << "\n";

    return 0;
}