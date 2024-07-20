//
// Created by Aashik on 27-06-2024.
//

#pragma once

class IMessage {
public:
    virtual ~IMessage() = default;
    virtual void execute() = 0;
};
