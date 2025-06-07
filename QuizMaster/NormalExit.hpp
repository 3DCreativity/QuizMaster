#pragma once

#include <exception>
#include "custom_string.h"

class NormalExit:std::exception
{
    private:
        custom_string msg;
    public:
        NormalExit(const custom_string message):msg(message) {}

        const char* what() const noexcept override {
            return msg.c_str();
        }
};