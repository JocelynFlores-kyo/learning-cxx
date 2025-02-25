﻿#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) {
        ptr->record('r');
        // std::cout << "r" << std::endl;
    }
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) {
        ptr->record('d');
        // std::cout << "d" << std::endl;
    }
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) {
    ptr->record('f');
    // std::cout << "f" <<std::endl;
    }
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);
    // std::cout << "0结束" << std::endl;
    // for (const auto& str : problems[0]) {
    //     std::cout << str << std::endl;
    // }

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);
    // std::cout << "1结束" << std::endl;
    // for (const auto& str : problems[1]) {
    //     std::cout << str << std::endl;
    // }

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);
    // for (const auto& str : problems[2]) {
    //     std::cout << str << std::endl;
    // }

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        // std::cout << problems[i].size() << std::endl;
        // std::cout << answers[i].size() << std::endl;
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            // std::cout << "i,j: " << i << j << std::endl;
            // std::cout << std::strcmp(problems[i][j].c_str(), answers[i][j]) << std::endl;
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
