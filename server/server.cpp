#include "server.hpp"

namespace EDPM {

Server::Server() {

}

Server::~Server() {

}

bool Server::DatabaseExists(std::string name) noexcept {
    return (databases.find(name) != databases.end());
}

void Server::MakeNewDatabase(std::string name) {
    if (DatabaseExists(name)) throw DatabaseException(DatabaseException::AlreadyExists, name);

    pendingFlush = true;

    databases.insert({name, Database()});
}

}