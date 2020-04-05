/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "Opcodes.h"
#include "SharedDefines.h"
#include "WorldSession.h"
#include "WorldPacket.h"

#include <map>
#include <set>
#include <list>

void WorldSession::SendAuthResponse(uint8 code, bool queued, uint32 queuePos)
{
    uint8 count5 = 1;
    std::string realmName = sWorld->GetRealmName();
    std::string trimmedName = sWorld->GetTrimmedRealmName();

    QueryResult classResult = LoginDatabase.PQuery("SELECT class, expansion FROM realm_classes WHERE realmId = %u", realmID);
    QueryResult raceResult = LoginDatabase.PQuery("SELECT race, expansion FROM realm_races WHERE realmId = %u", realmID);

    if (!classResult || !raceResult)
    {
        TC_LOG_ERROR("network", "Unable to retrieve class or race data.");
        return;
    }

    TC_LOG_DEBUG("network", "SMSG_AUTH_RESPONSE");
    WorldPacket packet(SMSG_AUTH_RESPONSE, 80);

    packet.WriteBit(code == AUTH_OK);

    if (code == AUTH_OK)
    {
        packet.WriteBits(0, 21); // Send current realmId

        for (uint8 i = 0; i < count5; ++i)
        {
            packet.WriteString(realmName);
            packet.WriteString(trimmedName);
            packet << uint32(realmID);
        }

        packet.WriteBits(classResult->GetRowCount(), 23);
        packet.WriteBits(0, 21);
        packet.WriteBit(0);
        packet.WriteBit(0);
        packet.WriteBit(0);
        packet.WriteBit(0);
        packet.WriteBits(raceResult->GetRowCount(), 23);
        packet.WriteBit(0);
    }

    packet.WriteBit(queued);

    if (queued)
        packet.WriteBit(1);                             // Unknown

    packet.FlushBits();

    if (queued)
        packet << uint32(0);                            // Unknown

    if (code == AUTH_OK)
    {
        for (uint8 i = 0; i < count5; ++i)
        {
            packet.WriteBit(1);
            packet.WriteBits(realmName.size(), 8);
            packet.WriteBits(trimmedName.size(), 8);
        }

        do
        {
            Field* fields = raceResult->Fetch();

            packet << fields[1].GetUInt8();
            packet << fields[0].GetUInt8();
        }
        while (raceResult->NextRow());

        do
        {
            Field* fields = classResult->Fetch();

            packet << fields[1].GetUInt8();
            packet << fields[0].GetUInt8();
        }
        while (classResult->NextRow());

        packet << uint32(0);
        packet << uint8(Expansion());
        packet << uint32(Expansion());
        packet << uint32(0);
        packet << uint8(Expansion());
        packet << uint32(0);
        packet << uint32(0);
        packet << uint32(0);
    }

    packet << uint8(code);                             // Auth response ?

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}

void WorldSession::SendBattlePay()
{
    WorldPacket data(SMSG_BATTLE_PAY_GET_DISTRIBUTION_LIST_RESPONSE, 7);
    data << uint32(0);
    data.WriteBits(0, 19);
    data.FlushBits();
    SendPacket(&data);
}

void WorldSession::SendDisplayPromo(int32 promo)
{
    WorldPacket data(SMSG_DISPLAY_PROMOTION, 7);
    data << promo;
    SendPacket(&data);
}