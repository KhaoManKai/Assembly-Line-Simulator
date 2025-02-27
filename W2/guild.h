#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Guild {
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
        Guild() : m_members(nullptr), m_size(0), m_capacity(0), m_name("") {}

        Guild(const char* name) : m_members(nullptr), m_size(0), m_capacity(0), m_name(name) {}

        Guild(const Guild& other) : m_members(nullptr), m_size(0), m_capacity(other.m_capacity), m_name(other.m_name) {
            if (other.m_size > 0) {
                m_members = new Character*[m_capacity];
                for (size_t i = 0; i < other.m_size; ++i) {
                    m_members[i] = other.m_members[i];
                }
                m_size = other.m_size;
            }
        }

        Guild(Guild&& other): m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity), m_name(std::move(other.m_name)) {
            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        Guild& operator=(const Guild& other) {
            if (this != &other) {
                delete[] m_members;

                m_name = other.m_name;
                m_capacity = other.m_capacity;
                m_size = other.m_size;

                if (other.m_size > 0) {
                    m_members = new Character*[m_capacity];
                    for (size_t i = 0; i < other.m_size; ++i) {
                        m_members[i] = other.m_members[i];
                    }
                } else {
                    m_members = nullptr;
                }
            }
            return *this;
        }

        Guild& operator=(Guild&& other) {
            if (this != &other) {
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

        ~Guild() {
            delete[] m_members;
        }

        void addMember(Character* c) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i] == c) {
                    return;
                }
            }
            if (m_size == m_capacity) {
                resize();
            }
            c->setHealthMax(c->getHealthMax() + 300);
            m_members[m_size++] = c;
        }

        void removeMember(const std::string& name) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_members[i]->getName() == name) {
                    m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
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
            if (m_size == 0 && m_name.empty()) {
                std::cout << "No guild." << std::endl;
            } else {
                std::cout << "[Guild] " << m_name << std::endl;
                for (size_t i = 0; i < m_size; ++i) {
                    std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
                }
            }
        }
    };
}

#endif
