#include "TaskQueue.h"

#include <unistd.h>
#include <iostream>

using namespace std;

wb::TaskQueue taskQueue;

int cnt = 0;

//排版线程
void* relayout(void* param)
{
    cout << "-----排版线程启动-----" << endl;

    while (true) {
        wb::Task t;
        t.data = cnt++;
        taskQueue.Put(t);

        cout << "Put data [" << t.data << "] in queue! size = " << taskQueue.Size() << endl;
    }
}

//绘制线程
void* draw(void* param)
{
    cout << "-----绘制线程启动-----" << endl;

    while (true) {
        wb::Task t = taskQueue.Get();
        cout << "Get data [" << t.data << "] of queue! size = " << taskQueue.Size() << endl;
    }
}

int main()
{
    pthread_t relayoutThread;
    pthread_t drawThread;

    pthread_create(&relayoutThread, NULL, relayout, NULL);
    pthread_create(&drawThread, NULL, draw, NULL);

    
    pthread_join(drawThread, NULL);
    pthread_join(relayoutThread, NULL);
}
