#include "CustomGameState.h"


ACustomGameState::ACustomGameState()
{
    Player1Turn = true;

    PlayerHasWon = false;

    Player1HasSpellslot = true;
    Player2HasSpellslot = true;
    SpellSlotBeingUsed = false;

    for (int x=0; x < BlockStateSize; ++x)
    {
        BlockStateArray.Add(BlockStates::ENone);
    }
}

ACustomGameState::~ACustomGameState()
{
}
