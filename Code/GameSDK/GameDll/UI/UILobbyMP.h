////////////////////////////////////////////////////////////////////////////
//
//  Crytek Engine Source File.
//  Copyright (C), Crytek Studios, 2001-2012.
// -------------------------------------------------------------------------
//  File name:   UILobbyMP.h
//  Version:     v1.00
//  Created:     08/06/2012 by Michiel Meesters.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////
#ifndef __UILOBBYMP_H_
#define __UILOBBYMP_H_

#include "IUIGameEventSystem.h"
#include <IFlashUI.h>
#include "ICryStats.h"
#include "ICryLobby.h"
#include "Network/Lobby/GameLobbyData.h"
#include "ICryFriends.h"

class CUILobbyMP 
	: public IUIGameEventSystem
	, public IUIModule
{
public:
	CUILobbyMP();

	// IUIGameEventSystem
	UIEVENTSYSTEM( "UILobbyMP" );
	virtual void InitEventSystem();
	virtual void UnloadEventSystem();

	// IUIModule
	virtual void Reset();
	// ~IUIModule

	// UI functions
	void InviteAccepted();
	void SearchCompleted();
	void SearchStarted();
	void UpdateNatType();
	void ServerFound(SCrySessionSearchResult session, string sServerName);
	void PlayerListReturn(const SUIArguments& players, const SUIArguments& playerids);
	void ReadLeaderBoard();
	void WriteLeaderBoard();
	void RegisterLeaderBoard();
	void ShowLoadingDialog(const  char* sLoadingDialog);
	void HideLoadingDialog(const  char* sLoadingDialog);

	//Callback when session is found
	static void MatchmakingSessionSearchCallback(CryLobbyTaskID taskID, ECryLobbyError error, SCrySessionSearchResult* session, void* arg);
	static void ReadLeaderBoardCB(CryLobbyTaskID TaskID, ECryLobbyError Error, SCryStatsLeaderBoardReadResult *Result, void *Arg);
	static void RegisterLeaderboardCB(CryLobbyTaskID TaskID, ECryLobbyError Error, void *Arg);
	static void WriteLeaderboardCallback(CryLobbyTaskID TaskID, ECryLobbyError Error, void *Arg);
	static void GetFriendsCB(CryLobbyTaskID taskID, ECryLobbyError error, SFriendInfo* pFriendInfo, uint32 numFriends, void* pArg);
	static void InviteFriends(CryLobbyTaskID taskID, ECryLobbyError error, void* pArg);

private:
	// UI events
	void SearchGames(bool bLan);
	void AwardTrophy(int trophy);
	void JoinGame(unsigned int sessionID);
	void HostGame(bool bLan, string sMapPath, string sGameRules);
	void SetMultiplayer(bool bIsMultiplayer);
	void LockController( bool bLock );
	void LeaveGame();
	void GetPlayerList();
	void GetFriends();

private:
	enum EUIEvent
	{
		eUIE_ServerFound = 0,
		eUIE_PlayerListReturn = 1,
		eUIE_PlayerIdListReturn = 2,
		eUIE_InviteAccepted = 3,
		eUIE_SearchStarted = 4,
		eUIE_SearchCompleted = 5,
		eUIE_NatTypeUpdated = 6,
		eUIE_ShowLoadingDialog = 7,
		eUIE_HideLoadingDialog = 8,
	};

	SUIEventReceiverDispatcher<CUILobbyMP> m_eventDispatcher;
	SUIEventSenderDispatcher<EUIEvent> m_eventSender;
	IUIEventSystem* m_pUIEvents;
	IUIEventSystem* m_pUIFunctions;
	std::vector<SCrySessionSearchResult> m_FoundServers;
};


#endif // __UILOBBYMP_H_
