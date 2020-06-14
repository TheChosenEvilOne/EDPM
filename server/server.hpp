#pragma once

#include <unordered_map>
#include <string>

#include "common/exceptions.hpp"
#include "types.hpp"

namespace EDPM {

    class Server {
        public:
            Server();
            ~Server();

            bool DatabaseExists(std::string name) noexcept;

            //Might throw DatabaseException
            void MakeNewDatabase(std::string name);

        private:
            bool pendingFlush { false };
            std::unordered_map<std::string, Database> databases { };
    };

}