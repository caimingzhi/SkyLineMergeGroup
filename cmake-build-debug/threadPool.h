//
// Created by Admin on 2023/6/3.
//
#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#ifndef TESTSKYLINEINGROUP_THREADPOOL_H
#define TESTSKYLINEINGROUP_THREADPOOL_H

// 任务函数类型
template<typename F, typename... Args>
using TaskType = std::packaged_task<typename std::result_of<F(Args...)>::type()>;

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads)
            : stop(false)
    {
//        cout << endl << " the thread id in ThreadPool is ： " << this_thread::get_id() << endl;
        workers.reserve(numThreads);
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] { workerThread(); });
        }
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        // 创建任务函数
        auto task = std::make_shared<TaskType<F, Args...>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        // 获取任务的 future
        std::future<typename std::result_of<F(Args...)>::type> res = task->get_future();

        // 将任务加入队列
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.emplace([task]() { (*task)(); });
        }

        // 唤醒一个等待中的线程
        condition.notify_one();

        return res;
    }

    ~ThreadPool()
    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(500000));
//        cout << " Call the destructor of ~threadPool()  " << endl;
//        cout << endl << this_thread::get_id() << endl;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }

        // 唤醒所有线程，让它们退出
        condition.notify_all();

        // 等待所有线程完成

        for (std::thread & worker : workers) {
            if( worker.joinable() )
            {
                worker.join();
            }
//            cout << worker.get_id() << endl;
//            worker.join();
        }
//        std::this_thread::sleep_for(std::chrono::seconds(2 ));

    }

private:
    // 工作线程函数
    void workerThread()
    {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // 等待条件满足或线程池停止
                condition.wait(lock, [this] { return stop || !tasks.empty(); });

                // 线程池停止，退出循环
                if (stop && tasks.empty()) {
                    return;
                }

                // 取出一个任务
                if( !tasks.empty() )
                {
                    task = std::move(tasks.front());
                    tasks.pop();
                }

            }
//            cout << " this thread Id is " << this_thread::get_id() << endl;
            // 执行任务
            task();
        }
    }

    std::vector<std::thread> workers;                     // 工作线程
    std::queue<std::function<void()>> tasks;               // 任务队列
    std::mutex queueMutex;                                 // 任务队列互斥锁
    std::condition_variable condition;                     // 条件变量
    bool stop;                                             // 线程池停止标志
};

#endif //TESTSKYLINEINGROUP_THREADPOOL_H
