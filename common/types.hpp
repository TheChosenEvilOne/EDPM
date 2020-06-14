#pragma once

#include <optional>
#include <string>
#include <vector>

#include "common/utilities.hpp"

namespace EDPM {

struct Entry {
    std::string name;
    std::string title;
    std::string username;
    std::string password;
    std::string URL;
    std::string notes;
};

struct Group {
    std::string name;
    std::vector<Entry> entries;
    std::vector<Group> groups;
};

struct Database {
    std::string name;
    Group rootGroup;

    //Tries to find a group with a passed identifier of the following format example:
    //rootGroup.group1
    //Throws GroupException(GroupException::DoesNotExist) if it cannot be found
    Group &GetGroup(const std::string &identifier) {
        const std::vector<std::string> tokens = Utils::Tokenise(identifier, "\\.");
        std::vector<std::string>::const_iterator tokenIterator = tokens.cbegin();

        Group &currentGroup = rootGroup;

        for (;;) {
            if (tokenIterator == tokens.cend()) break;

            if (!currentGroup.groups.size()) {
                throw GroupException(GroupException::DoesNotExist);
            }

            bool found = false;
            for (Group &group : currentGroup.groups) {
                if (group.name == *tokenIterator) {
                    currentGroup = group;
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw GroupException(GroupException::DoesNotExist);
            }
        }

        return currentGroup;
    }

    //Tries to find an entry with a passed identifier of the following format example:
    //rootGroup.group1.entryfoo
    Entry &GetEntry(const std::string &identifier) {
        std::string::size_type lastDot = identifier.find_last_of('.');
        if (lastDot == std::string::npos) throw GroupException(GroupException::MalformedIdentifier);

        std::string groupSubstring;
        std::string entrySubstring;

        std::copy(identifier.cbegin(), identifier.cbegin() + lastDot, std::back_inserter(groupSubstring));
        std::copy(identifier.cbegin() + lastDot + 1, identifier.cend(), std::back_inserter(entrySubstring));

        std::optional<std::reference_wrapper<Group>> groupopt;

        try {
            groupopt = GetGroup(groupSubstring);
        } catch (GroupException &e) { throw e; }

        Group &group = groupopt.value();

        if (!group.entries.size()) throw GroupException(GroupException::DoesNotExist, "Entry does not exist");

        for (Entry &entry : group.entries) {
            if (entry.name == entrySubstring) return entry;
        }

        throw GroupException(GroupException::DoesNotExist, "Entry does not exist");
    }
};

}