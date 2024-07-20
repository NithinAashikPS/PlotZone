//
// Created by Aashik on 29-06-2024.
//

#pragma once
#include <future>
#include <string>

struct Input
{
    std::string name;
    std::string extension;
    std::string path;

    [[nodiscard]] bool isValid() const
    {
        return !name.empty() && !extension.empty() && !path.empty();
    }
};

struct Data
{
    Data() { data_future = data_promise.get_future(); }
    std::string id;
    std::string gpkg;
    Input input;
    bool isReady = false;

    void release()
    {
        isReady = true;
        data_promise.set_value();
    }
    void wait() const
    {
        if (!isReady)
            data_future.wait();
    }
    [[nodiscard]] bool isValid() const
    {
        return !id.empty() && input.isValid();
    }

    friend std::ostream& operator<<(std::ostream& os, const Data& data);

private:
    std::promise<void> data_promise;
    std::future<void> data_future;
};

inline std::ostream& operator<<(std::ostream& os, const Data& data)
{
    os  << "{\n\tID: " << data.id << ",\n";
    os  << "\tInput {" << "\n"
        << "\t\tName: " << data.input.name << "\n"
        << "\t\tExtension: " << data.input.extension << "\n"
        << "\t\tPath: " << data.input.path << "\n"
        << "\t\tIsValid: " << data.input.isValid() << "\n"
        << "\t}\n}";
    return os;
}