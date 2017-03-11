#include <thread_pool.hpp>
#include <thread>
#include <gperftools/profiler.h>

// to build this, install: https://github.com/gperftools/gperftools

int main(){
    ProfilerStart("/tmp/prof.out");
    ThreadPool pool;
    
    //stall for 2 sec (thread pool does nothing)
    std::this_thread::sleep_for(std::chrono::seconds(20));

    MPMCBoundedQueue<std::future<int>> queue(1024);

    // two sec of heavy job
    for(int i=0; i<1000; i++){
        auto &&f = pool.process([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(4));
            return i;
        });
        queue.push(std::move(f));
    }

    std::future<int> item;
    while (queue.pop(item)) {
        item.get(); // join
    }

    ProfilerStop();

    return 0;
}