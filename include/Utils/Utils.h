//
// Created by Aashik on 29-06-2024.
//

#pragma once
#include <algorithm>
#include <random>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

class Utils
{
public:
    static std::string UUID()
    {
        static std::random_device dev;
        static std::mt19937 rng(dev());

        std::uniform_int_distribution<int> dist(0, 15);

        auto v = "0123456789abcdef";
        constexpr bool dash[] = { false, false, false, false, true, false, true, false, true, false, true, false, false, false, false, false };

        std::string res;
        for (int i = 0; i < 16; i++) {
            if (dash[i]) res += "-";
            res += v[dist(rng)];
            res += v[dist(rng)];
        }
        return res;
    }

    static std::string fileName(const std::string& filePath) {
        const size_t pos = filePath.find_last_of("/\\");
        return (pos == std::string::npos) ? filePath : filePath.substr(pos + 1);
    }

    static std::string fileExtension(const std::string& filePath) {
        const size_t dotPos = filePath.find_last_of('.');
        const size_t slashPos = filePath.find_last_of("/\\");
        return dotPos == std::string::npos || (slashPos != std::string::npos && dotPos < slashPos) ?
                "" : filePath.substr(dotPos);
    }

    static std::string currentDir()
    {
        TCHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileName(nullptr, buffer, MAX_PATH );
        const std::string::size_type pos = std::string(buffer).find_last_of("/\\");
        std::string path = std::string(buffer).substr(0, pos);
        // std::ranges::replace(path, '\\', '/');
        return path;
    }
};
