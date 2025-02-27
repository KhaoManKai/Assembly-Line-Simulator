#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Team {
    private:
        Character** m_members;
        size_t m_size;
        size_t m_capacity;
        std::string m_name;

        void resize() {
            size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
            Character** newMembers = new Character*[newCapacity];
            for (size_t i = 0; i < m_size; ++i) {
                newMembers[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newMembers;
            m_capacity = newCapacity;
        }

    public:
        Team() : m_members(nullptr), m_size(0), m_capacity(0), m_name("") {}

        Team(const char* name) : m_members(nullptr), m_size(0), m_capacity(0), m_name(name) {}

        Team(const Team& other) : m_members(nullptr), m_size(0), m_capacity(0), m_name(other.m_name) {
            for (size_t i = 0; i < other.m_size; ++i) {
                addMember(other.m_members[i]);
            }
        }

        Team(Team&& other):m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(std::move(other.m_name)) {
            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        Team& operator=(const Team& other) {
            if (this != &other) {
                for (size_t i = 0; i < m_size; ++i) {
                    delete m_members[i];
                }
                delete[] m_members;
                m_members = nullptr;

                m_size = 0;
                m_capacity = 0;
                m_name = other.m_name;

                for (size_t i = 0; i < other.m_size; ++i) {
                    addMember(other.m_members[i]);
                }
            }
            return *this;
        }

        Team& operator=(Team&& other){
            if (this != &other) {
                for (size_t i = 0; i < m_size; ++i) {
                    delete m_members[i];
                }
                delete[] m_members;

                m_members = other.m_members;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_name = std::move(other.m_name);

                other.m_members = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            return *this;
        }

        ~Team() {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
        }

        void addMember(const Character* c) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == c->getName()) {
                    return;
                }
            }
            if (m_size == m_capacity) {
                resize();
            }
            m_members[m_size++] = c->clone();
        }

        void removeMember(const std::string& name) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == name) {
                    delete m_members[i];
                    for (size_t j = i; j < m_size - 1; ++j) {
                        m_members[j] = m_members[j + 1];
                    }
                    --m_size;
                    return;
                }
            }
        }

        Character* operator[](size_t idx) const {
            if (idx < m_size) {
                return m_members[idx];
            }
            return nullptr;
        }

        void showMembers() const {
            if (m_size == 0) {
                std::cout << "No team." << std::endl;
            } else {
                std::cout << "[Team] " << m_name << std::endl;
                for (size_t i = 0; i < m_size; ++i) {
                    std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
                }
            }
        }
    };
}

#endif
