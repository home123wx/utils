#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include <queue>
#include <pthread.h>

using std::queue;
namespace wb {

typedef struct Task {
    int data;
} Task;

class TaskQueue
{
public:
    TaskQueue();
    TaskQueue(int maxSize);
    virtual ~TaskQueue();

public:
    unsigned int Size();

    Task Get();
    void Put(const Task& task);

private:
    int             m_maxSize;
    pthread_mutex_t m_queueMutex;
    pthread_cond_t  m_threadCond;
    queue<Task>     m_taskQueue;
};
} //end namespace

#endif //_TASK_QUEUE_H_
