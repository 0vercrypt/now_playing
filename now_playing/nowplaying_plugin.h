/*
 * TeamSpeak 3 demo plugin
 *
 * Copyright (c) 2008, 2009 TeamSpeak Systems GmbH
 */
#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <vector>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#include "public_errors.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"
#include "plugin_events.h"

#include "shared.h"


#ifdef WIN32
#define PLUGINS_EXPORTDLL __declspec(dllexport)
#else
#define PLUGINS_EXPORTDLL __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum {
	PLAYER_APP_WINAMP = 1, 
	PLAYER_APP_VLC,
	PLAYER_APP_LIGHTALLOY,
	PLAYER_APP_GOOGLE,
	PLAYER_APP_SPOTIFY,
	PLAYER_APP_SPIDER,
	PLAYER_APP_WMP
};

/* Required functions */
PLUGINS_EXPORTDLL const char* ts3plugin_name();
PLUGINS_EXPORTDLL const char* ts3plugin_version();
PLUGINS_EXPORTDLL int ts3plugin_apiVersion();
PLUGINS_EXPORTDLL const char* ts3plugin_author();
PLUGINS_EXPORTDLL const char* ts3plugin_description();
PLUGINS_EXPORTDLL void ts3plugin_setFunctionPointers(const struct TS3Functions funcs);
PLUGINS_EXPORTDLL int ts3plugin_init();
PLUGINS_EXPORTDLL void ts3plugin_shutdown();

/* Optional functions */
PLUGINS_EXPORTDLL int ts3plugin_offersConfigure();
PLUGINS_EXPORTDLL void ts3plugin_configure(void* handle, void* qParentWidget);
PLUGINS_EXPORTDLL void ts3plugin_registerPluginID(const char* id);
PLUGINS_EXPORTDLL const char* ts3plugin_commandKeyword();
PLUGINS_EXPORTDLL int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command);
PLUGINS_EXPORTDLL void ts3plugin_pluginEvent(unsigned short data, const char* message);
PLUGINS_EXPORTDLL const char* ts3plugin_infoTitle();
PLUGINS_EXPORTDLL void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char** data);
PLUGINS_EXPORTDLL void ts3plugin_freeMemory(void* data);
PLUGINS_EXPORTDLL int ts3plugin_requestAutoload();
PLUGINS_EXPORTDLL void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon);
PLUGINS_EXPORTDLL void ts3plugin_initHotkeys(struct PluginHotkey*** hotkeys);

/* Clientlib */
PLUGINS_EXPORTDLL void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
PLUGINS_EXPORTDLL void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);
PLUGINS_EXPORTDLL void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage);
PLUGINS_EXPORTDLL void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
PLUGINS_EXPORTDLL void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage);
PLUGINS_EXPORTDLL int  ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage);
PLUGINS_EXPORTDLL void ts3plugin_onChannelSubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID);

/* Clientlib rare */
PLUGINS_EXPORTDLL void ts3plugin_onClientBanFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, uint64 time, const char* kickMessage);
PLUGINS_EXPORTDLL void ts3plugin_onClientDBIDfromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID);
PLUGINS_EXPORTDLL void ts3plugin_onClientNamefromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName);
PLUGINS_EXPORTDLL void ts3plugin_onClientNamefromDBIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName);
PLUGINS_EXPORTDLL void ts3plugin_onPluginCommandEvent(uint64 serverConnectionHandlerID, const char* pluginName, const char* pluginCommand);
PLUGINS_EXPORTDLL void ts3plugin_onServerTemporaryPasswordListEvent(uint64 serverConnectionHandlerID, const char* clientNickname, const char* uniqueClientIdentifier, const char* description, const char* password, uint64 timestampStart, uint64 timestampEnd, uint64 targetChannelID, const char* targetChannelPW);

/* Client UI callbacks */
PLUGINS_EXPORTDLL void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID);
PLUGINS_EXPORTDLL void ts3plugin_onHotkeyEvent(const char* keyword);
PLUGINS_EXPORTDLL void ts3plugin_onHotkeyRecordedEvent(const char* keyword, const char* key);

int loadInitSettings();
DWORD WINAPI MainLoop (LPVOID lpParam);
int FormatTitle (char *chDestination, unsigned int size, char *chFormat, struct TrackInfo info);
int GetRowForUser_Server ( uint64 serverConnectionHandlerID, anyID clientID, int* result);
int removeRecord(uint64 serverConnectionHandlerID, anyID clientID);
void removeAllServerHandlerRecords(uint64 serverConnectionHandlerID, int* removedRecords);
void processChannelSubOrMeMoved(uint64 serverConnectionHandlerID, uint64 channelID);
void processClientMoveKickVisCheck (uint64 serverConnectionHandlerID, anyID clientID, int visibility);
#ifdef ENABLE_QUEUED_SUB_CODE
void processQueuedSongRequest();
#endif
void togglePlayer(uint64 playerID);
void displayCurrentPlayerStatus();
void spamChannel(uint64 serverConnectionHandlerID, uint64 channelID);
void spamTarget(uint64 serverConnectionHandlerID, uint64 targetID, int targetIsClient);
void CheckIfAloneOnServers();
void CheckIfAlone(uint64 serverConnectionHandlerID);

#ifdef __cplusplus
}
#endif

#endif