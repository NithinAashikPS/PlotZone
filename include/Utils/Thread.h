//
// Created by Aashik on 30-06-2024.
//

#pragma once

#include <Actor/Actor.h>

template<typename ActorType>
class Thread
{
public:
    template<typename... Args>
    explicit Thread(Args&&... args)
    {
        thread = std::thread([&]()
        {
            m_actor = std::make_shared<Actor<ActorType>>(std::forward<Args>(args)...);
        });
    }

    std::shared_ptr<Actor<ActorType>> actor()
    {
        return m_actor;
    }
private:
    std::thread thread;
    std::shared_ptr<Actor<ActorType>> m_actor;
};
