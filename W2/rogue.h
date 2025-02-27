// Workshop 2
// RPG Game
// Revision History
// -----------------------------------------------------------
// Name Hin Lum Lee     Date 20 OCT 2024   ID 132957234
// NBB  hllee13@myseneca.ca
/////////////////////////////////////////////////////////////////
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include <iostream>
#include "characterTpl.h"
#include "abilities.h"
#include "weapons.h"
namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
    private:
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        Dagger m_weapon;

    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) :CharacterTpl<T>(name, healthMax),
              m_baseDefense(baseDefense),m_baseAttack(baseAttack) {}
        
        int getAttackAmnt() const override {
            return (m_baseAttack + 1) + 2 * static_cast<int>(static_cast<double>(m_weapon));
        }
        
        Character* clone() const override{
            return new Rogue(*this);
        }
        int getDefenseAmnt() const override{
            return m_baseDefense;
        }

        void takeDamage(int dmg) override{
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;

            int reducedDamage = std::max(0, dmg - m_baseDefense);
            m_firstAbility.transformDamageReceived(reducedDamage);
            m_secondAbility.transformDamageReceived(reducedDamage);

            CharacterTpl<T>::takeDamage(reducedDamage);
        }
        void attack(Character* enemy) override{
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int damage = getAttackAmnt();
            m_firstAbility.transformDamageDealt(damage);
            m_secondAbility.transformDamageDealt(damage);

            std::cout << "    Rogue deals " << damage << " melee damage!" << std::endl;
            enemy->takeDamage(damage);
        }
    };
}

#endif  
