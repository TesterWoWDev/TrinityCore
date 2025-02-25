/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Trainer_h__
#define Trainer_h__

#include "Common.h"
#include <array>
#include <vector>

class Creature;
class ObjectMgr;
class Player;

namespace Trainer
{
    enum class Type : uint32
    {
        Class = 0,
        Mount = 1,
        Tradeskill = 2,
        Pet = 3
    };

    enum class SpellState : uint8
    {
        Available = 0,
        Unavailable = 1,
        Known = 2
    };

    enum class FailReason : uint32
    {
        Unavailable = 0,
        NotEnoughMoney = 1,
        NotEnoughSkill = 2
    };

    struct TC_GAME_API Spell
    {
        uint32 SpellId = 0;
        uint32 MoneyCost = 0;
        uint32 ReqSkillLine = 0;
        uint32 ReqSkillRank = 0;
        std::array<uint32, 3> ReqAbility = { };
        uint8 ReqLevel = 0;
        // @tswow-begin
        uint32 classMask = 0;
        uint32 raceMask = 0;
        // @tswow-end

        bool IsCastable() const;
    };

    class TC_GAME_API Trainer
    {
    public:
        // @tswow-begin
        Trainer(uint32 trainerId, Type type, uint32 requirement, std::string greeting, uint32 classMask, uint32 raceMask, std::vector<Spell> spells);
        // @tswow-end

        Spell const* GetSpell(uint32 spellId) const;
        std::vector<Spell> const& GetSpells() const { return _spells; }
        void SendSpells(Creature const* npc, Player const* player, LocaleConstant locale) const;
        bool CanTeachSpell(Player const* player, Spell const* trainerSpell) const;
        void TeachSpell(Creature const* npc, Player* player, uint32 spellId) const;

        Type GetTrainerType() const { return _type; }
        uint32 GetTrainerRequirement() const { return _requirement; }
        bool IsTrainerValidForPlayer(Player const* player) const;

    private:
        SpellState GetSpellState(Player const* player, Spell const* trainerSpell) const;
        void SendTeachFailure(Creature const* npc, Player const* player, uint32 spellId, FailReason reason) const;
        void SendTeachSucceeded(Creature const* npc, Player const* player, uint32 spellId) const;
        std::string const& GetGreeting(LocaleConstant locale) const;

        friend ObjectMgr;
        void AddGreetingLocale(LocaleConstant locale, std::string greeting);

        uint32 _trainerId;
        Type _type;
        uint32 _requirement;
        // @tswow-begin
        uint32 _classMask;
        uint32 _raceMask;
        // @tswow-endk
        std::vector<Spell> _spells;
        std::array<std::string, TOTAL_LOCALES> _greeting;
    };
}

#endif // Trainer_h__
