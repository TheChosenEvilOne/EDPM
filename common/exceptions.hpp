#pragma once

#include <exception>
#include <sstream>
#include <string>
#include <unordered_map>

namespace EDPM {
    struct DatabaseException : public std::exception {
        enum EType {
            AlreadyExists,
            DoesNotExist
        } type;

        const std::unordered_map<EType, std::string> ETypeString {
            {AlreadyExists, "AlreadyExists"},
            {DoesNotExist, "DoesNotExist"},
        };

        std::string whatString;

        DatabaseException(EType type, std::string name) : type(type) {
            std::ostringstream oss;
            oss<<"Database: "<<name<<", error: "<<ETypeString.at(type);
            whatString = oss.str();
        }

        const char *what() const throw() {
            return whatString.c_str();
        }
    };

    struct GroupException : public std::exception {
        enum EType {
            DoesNotExist,
            MalformedIdentifier
        } type;

        const std::unordered_map<EType, std::string> ETypeString {
            {DoesNotExist, "DoesNotExist"},
            {MalformedIdentifier, "MalformedIdentifier"},
        };

        std::string whatString;

        GroupException(EType type, std::string message = "") {
            std::ostringstream oss;
            oss<<"Error: "<<ETypeString.at(type);
            if (message != "") {
                oss<<", message: "<<message;
            }
            oss<<std::endl;
        }

        const char *what() const throw() {
            return whatString.c_str();
        }
    };
}