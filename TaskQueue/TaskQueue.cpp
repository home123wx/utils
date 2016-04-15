#include "TaskQueue.h"

#define DEFAULE_MAX_SIZE 100

namespace wb {

TaskQueue::TaskQueue()
{
    m_maxSize = DEFAULE_MAX_SIZE;
    pthread_mutex_init(&m_queueMutex, NULL);
    pthread_cond_init(&m_threadCond, NULL);
}

TaskQueue::TaskQueue(int maxSize)
{
    m_maxSize = maxSize;
    TaskQueue();
}

TaskQueue::~TaskQueue()
{
    pthread_mutex_destroy(&m_queueMutex);
    pthread_cond_destroy(&m_threadCond);
}

void TaskQueue::Put(const Task& task)
{
    pthread_mutex_lock(&m_queueMutex);

    if (m_taskQueue.size() == m_maxSize) {
        pthread_cond_wait(&m_threadCond, &m_queueMutex);
    }

    m_taskQueue.push(task);
    if (m_taskQueue.size() == 1) {
        pthread_cond_signal(&m_threadCond);
    }
    pthread_mutex_unlock(&m_queueMutex);
}

Task TaskQueue::Get()
{
    pthread_mutex_lock(&m_queueMutex);

    if (m_taskQueue.empty()) {
        pthread_cond_wait(&m_threadCond, &m_queueMutex);
    }

    Task t = m_taskQueue.front();
    m_taskQueue.pop();

    if (m_taskQueue.size() < m_maxSize) {
        pthread_cond_signal(&m_threadCond);
    }
    pthread_mutex_unlock(&m_queueMutex);

    return t;
}

unsigned int TaskQueue::Size()
{
    return m_taskQueue.size();
}

} //end namespace
