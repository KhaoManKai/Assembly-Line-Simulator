// Workshop 2
// RPG Game
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 20 OCT 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include <iostream>
#include <algorithm>
#include "character.h"
#include "health.h"

namespace seneca {
    template <typename T>
    class CharacterTpl : public Character {
    private:
        int m_healthMax;
        T m_health;

    public:
        CharacterTpl(const char* name, int maxHealth): Character(name), m_healthMax(maxHealth), m_health(maxHealth){}

        void takeDamage(int dmg) override {
            int currentHealth = static_cast<int>(m_health);
            currentHealth = std::max(0, currentHealth - dmg); // health must >= 0
            m_health = static_cast<T>(currentHealth);
            if (currentHealth <= 0) {
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << "    " << getName() << " took " << dmg << " damage, "
                          << currentHealth << " health remaining." << std::endl;
            }
        }

        int getHealth() const override {
            return std::max(0, static_cast<int>(m_health));
        }


        int getHealthMax() const override {
            return m_healthMax;
        }


        void setHealth(int health) override {
            m_health = static_cast<T>(std::max(0, health));
        }

        void setHealthMax(int health) override {
            m_healthMax = std::max(0, health);
            setHealth(m_healthMax);
        }
    };

    // SuperHealth type
    template <>
    class CharacterTpl<SuperHealth> : public Character {
    private:
        int m_healthMax;
        SuperHealth m_health;

    public:
        CharacterTpl(const char* name, int maxHealth): Character(name), m_healthMax(maxHealth), m_health() {
            m_health = maxHealth;
        }

    
        void takeDamage(int dmg) override {
            m_health -= dmg;
            int currentHealth = std::max(0, static_cast<int>(m_health));
            if (currentHealth <= 0) {
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            } else {
                std::cout << "    " << getName() << " took " << dmg << " damage, "
                          << currentHealth << " health remaining." << std::endl;
            }
        }

       
        int getHealth() const override {
            return std::max(0, static_cast<int>(m_health));
        }

        int getHealthMax() const override {
            return m_healthMax;
        }


        void setHealth(int health) override {
            m_health = std::max(0, health);
        }

      
        void setHealthMax(int health) override {
            m_healthMax = std::max(0, health);
            setHealth(m_healthMax);
        }
    };

    //InfiniteHealth type
    template <>
    class CharacterTpl<InfiniteHealth> : public Character {
    private:
        int m_healthMax;
        InfiniteHealth m_health;

    public:
        CharacterTpl(const char* name, int maxHealth)
            : Character(name), m_healthMax(maxHealth), m_health() {}

        void takeDamage(int dmg) override {
            std::cout << "    " << getName() << " is invincible and took no damage!" << std::endl;
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }

        int getHealthMax() const override {
            return m_healthMax;
        }

        void setHealth(int) override {}//no change

        void setHealthMax(int health) override {
            m_healthMax = std::max(0, health);
        }
    };
}

#endif /* SENECA_CHARACTERTPL_H */
