//
// Created by Aashik on 27-06-2024.
//

#pragma once

#include <tuple>
#include <utility>

#include <Actor/IMessage.h>

template<typename ActorType, typename Func, typename... Args>
class Message final : public IMessage {
public:
    Message(ActorType* actor, Func&& func, Args&&... args)
        : actor_(actor), func_(std::forward<Func>(func)), args_(std::forward<Args>(args)...) {}

    using ReturnType = std::invoke_result_t<Func, ActorType*, Args...>;
    Message(ActorType* actor, Func&& func, std::promise<ReturnType>&& promise, Args&&... args)
        : actor_(actor), promise_(std::move(promise)), func_(std::forward<Func>(func)), args_(std::forward<Args>(args)...) {}


    void execute() override {
        // std::apply(func_, std::tuple_cat(std::make_tuple(std::ref(actor_)), args_));
        if constexpr (std::is_void_v<ReturnType>) {
            std::apply(func_, std::tuple_cat(std::make_tuple(actor_), args_));
            promise_.set_value();
        } else {
            try {
                ReturnType result = std::apply(func_, std::tuple_cat(std::make_tuple(actor_), args_));
                promise_.set_value(result);
            } catch (...) {
                promise_.set_exception(std::current_exception());
            }
        }
    }

private:
    ActorType* actor_;
    std::promise<ReturnType> promise_;
    Func func_;
    std::tuple<Args...> args_;
};
