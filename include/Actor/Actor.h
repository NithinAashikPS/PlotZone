//
// Created by Aashik on 27-06-2024.
//

#pragma once
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include <Actor/Message.h>

template<typename ActorType>
class Actor {
public:
    template<typename... Args>
    explicit Actor(Args&&... args)
        : actor_(std::make_unique<ActorType>(std::forward<Args>(args)...)), worker_(&Actor::run, this) {}

    ~Actor() {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            stop_ = true;
        }
        condVar_.notify_one();
        worker_.join();
    }

    template<typename Func, typename... Args>
    void invoke(Func&& func, Args&&... args) {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            messageQueue_.emplace(new Message<ActorType, Func, Args...>(actor_.get(), std::forward<Func>(func), std::forward<Args>(args)...));
        }
        condVar_.notify_one();
    }

    template<typename Func, typename... Args>
    auto ask(Func&& func, Args&&... args) {
        using ReturnType = std::invoke_result_t<Func, ActorType*, Args...>;
        std::promise<ReturnType> promise;
        auto future = promise.get_future();

        {
            std::unique_lock<std::mutex> lock(mutex_);
            messageQueue_.emplace(new Message<ActorType, Func, Args...>(actor_.get(), std::forward<Func>(func), std::move(promise), std::forward<Args>(args)...));
        }
        condVar_.notify_one();

        return future;
    }

private:
    void run() {
        while (true) {
            std::unique_ptr<IMessage> msg;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                condVar_.wait(lock, [this] { return !messageQueue_.empty() || stop_; });
                if (stop_ && messageQueue_.empty()) break;
                msg = std::move(messageQueue_.front());
                messageQueue_.pop();
            }
            msg->execute();
        }
    }

    std::unique_ptr<ActorType> actor_;
    std::queue<std::unique_ptr<IMessage>> messageQueue_;
    std::mutex mutex_;
    std::condition_variable condVar_;
    bool stop_{};
    std::thread worker_;
};
