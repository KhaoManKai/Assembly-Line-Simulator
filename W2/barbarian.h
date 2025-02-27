// Workshop 2
// RPG Game
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 20 OCT 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include "characterTpl.h"

namespace seneca {
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
    private:
        int m_baseDefense;
        int m_baseAttack;
        Ability_t m_ability;
        Weapon_t m_weapon[2];
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack) {
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }

        int getAttackAmnt() const override {
            int attack = m_baseAttack + static_cast<int>(static_cast<double>(m_weapon[0]) / 2) + static_cast<int>(static_cast<double>(m_weapon[1]) / 2);
            if (typeid(T) == typeid(seneca::InfiniteHealth)) {
                attack += 1;
            }
            return attack;
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            m_ability.useAbility(this);

            int damage = getAttackAmnt();
            m_ability.transformDamageDealt(damage);

            std::cout << "    Barbarian deals " << damage << " melee damage!" << std::endl;

            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            int reducedDamage = std::max(0, dmg - m_baseDefense);
            m_ability.transformDamageReceived(reducedDamage);

            CharacterTpl<T>::takeDamage(reducedDamage);
        }
    };
}

#endif
