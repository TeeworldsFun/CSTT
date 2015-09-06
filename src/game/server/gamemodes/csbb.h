#ifndef GAME_SERVER_GAMEMODES_CSBB_H
#define GAME_SERVER_GAMEMODES_CSBB_H
#include <game/server/gamecontroller.h>
#include <game/server/entity.h>

#define MAX_BOMBAREAS 10
#define MAX_PICKUPS 1024
#define MAX_DROPPABLES 30


enum GameStateCSBB
{
	CSBB_NEWBASE,
	CSBB_DEFENDING,
	CSBB_ENDING,
};


class CGameControllerCSBB : public IGameController
{
private:
	bool m_DroppablesCreated;
	
	int m_RoundTick;
	
	int m_Base;
	
	int m_HoldingTeam;
	
	
	void Restart();
	
	void NewBase();
	void CaptureBase();
	
	void RoundWinLose();
	void RoundRewards(int WinningTeam);
	
	int CheckLose();
	void AutoBalance();
		
	bool m_NewGame;
	
	bool m_aDefusing[MAX_CLIENTS];
	
	int m_BroadcastTimer;
	
	int m_BombSoundTimer;
	int m_BombActionTimer;
	
	
	int CountPlayers();
	int CountPlayersAlive();
		
	bool m_Timeout;
	
	// 
	class CBomb *m_pBomb; // red flag
	class CFlag *m_apBombArea[MAX_BOMBAREAS]; // blue flags
	int m_BombAreaCount;
	
	int m_BombDefuseTimer;
	bool m_BombDefused;
	
	
	int m_BombCarrierTurn;
	
	void GiveBombToPlayer();
	
	// store pickup pointers
	class CPickup *m_apPickup[MAX_PICKUPS];
	int m_PickupCount;
	
	// for item drops
	int m_PickupDropCount;
	
	void CreateDroppables();
	
	void RespawnPickups();
	void ClearPickups();


public:
	CGameControllerCSBB(class CGameContext *pGameServer);
	
	virtual void DoWincheck();
	virtual bool CanBeMovedOnBalance(int ClientID);
	virtual void Snap(int SnappingClient);
	virtual void Tick();
	
	virtual void DropPickup(vec2 Pos, int PickupType, vec2 Force, int PickupSubtype = -1);
	void FlashPickups();
	
	
	
	virtual bool OnEntity(int Index, vec2 Pos);
	int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
	void OnCharacterSpawn(class CCharacter *pChr, bool RequestAI = false);
	
	class CBomb *GetBomb();
	class CFlag *GetClosestBombArea(vec2 Pos);
	
	bool CanCharacterSpawn(int ClientID);
};
#endif
