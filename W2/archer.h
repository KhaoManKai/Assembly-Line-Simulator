// Workshop 2
// RPG Game
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 20 OCT 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include "characterTpl.h"
#include "weapons.h"
namespace seneca {
    template <typename Weapon_t>
    class Archer : public CharacterTpl<SuperHealth> {
    private:
        int m_baseDefense;
        int m_baseAttack;
        Weapon_t m_weapon;

    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon): CharacterTpl<SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

        int getAttackAmnt() const {
            return static_cast<int>(1.3 * m_baseAttack);
        }

        int getDefenseAmnt() const {
            return static_cast<int>(1.2 * m_baseDefense);
        }
        void attack(Character* enemy) {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            int damage = getAttackAmnt();

            std::cout << "    Archer deals " << damage << " ranged damage!" << std::endl;

            enemy->takeDamage(damage);
        }

        Character* clone() const {
            return new Archer(*this);
        }

        void takeDamage(int dmg) {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            int defense = getDefenseAmnt();
            std::cout << "    Archer has a defense of " << defense << ". Reducing damage received." << std::endl;
            int reducedDamage = std::max(0, dmg - defense);
            
            CharacterTpl<SuperHealth>::takeDamage(reducedDamage);
        }
    };
}

#endif  
