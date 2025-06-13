#pragma once

namespace dae {
    class Command {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
    };
}