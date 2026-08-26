//
// Shared/version.h
//
#pragma once

/*****************************************************************************
 * Note for fork developers:
 *
 * If you don't follow these guidelines, you may suffer from inadequate or even
 * zero anti-cheat support, when you release a fork client to the public with a
 * misconfigured deployment pipeline. Never use build type VERSION_TYPE_CUSTOM in
 * a public release of your fork.
 *
 * Please read the wiki article at https://wiki.multitheftauto.com/wiki/Forks for
 * more information, guidelines and security considerations.
 *
 * To compile a client for mass consumption by your player base (as a public release):
 *   1. Set MTASA_VERSION_TYPE to VERSION_TYPE_UNSTABLE
 *   2. Use netc.dll from https://mirror-cdn.multitheftauto.com/bdata/fork-support/netc.dll
 *   3. Switch to Nightly build configuration
 *
 * To develop and test a client locally or in a trustworthy closed group (local or private release):
 *  a. With active anti-cheat:
 *      1. Set MTASA_VERSION_TYPE to VERSION_TYPE_UNSTABLE
 *      2. Use netc.dll from https://mirror-cdn.multitheftauto.com/bdata/netc.dll (preferably run utils/buildactions/install_data.lua)
 *  b. Without anti-cheat:
 *      1. Set MTASA_VERSION_TYPE to VERSION_TYPE_CUSTOM
 *      2. Use netc.dll from https://mirror-cdn.multitheftauto.com/bdata/netc.dll (preferably run utils/buildactions/install_data.lua)
 *
 * To compile and host an official public server (anyone on official MTA client can connect):
 *      1. Copy net.dll or net.so from a nightly release (see https://nightly.multitheftauto.com/)
 *      2. Set MTASA_VERSION_TYPE to VERSION_TYPE_RELEASE
 *      3. Set MTASA_VERSION_BUILD to the build number from the network library (see file version information)
 *      4. Switch to Nightly build configuration
 *
 * To compile and host a custom public server (only custom MTA clients can connect):
 *      1. Use `<disableac>5,6,21</disableac>` in your mtaserver.conf (may not be needed in the future)
 *      2. Use regular developer net.dll or net.so (preferably run utils/buildactions/install_data.lua)
 *      3. Set MTASA_VERSION_TYPE to VERSION_TYPE_UNSTABLE
 *      4. Switch to Nightly build configuration
 *
 *****************************************************************************/

/*****************************************************************************
 * Kontur MTA fork (наши правила, не удалять при мерже):
 *
 * KONTUR_PUBLIC_RELEASE 0 = локальная разработка и закрытые тесты.
 *      Тип сборки CUSTOM, античита практически нет, netc.dll и net.dll берутся
 *      из win-install-data.bat. Такой клиент игрокам раздавать нельзя.
 *
 * KONTUR_PUBLIC_RELEASE 1 = публичная сборка Kontur MTA для игроков.
 *      Тип сборки UNSTABLE (обязательно: на CUSTOM поддержка античита падает
 *      с 15% до 1%), netc.dll подменяется файлом из
 *      https://mirror-cdn.multitheftauto.com/bdata/fork-support/netc.dll,
 *      сборка идёт в конфигурации Nightly, KONTUR_FORK_BUILD увеличивается.
 *
 * Сервер Kontur в обоих режимах: net.dll из win-install-data.bat, плюс строка
 * <disableac>5,6,21</disableac> в mtaserver.conf.
 *
 * Трафик клиента до серверов MTAHQ блокировать запрещено: без него форк
 * остаётся совсем без античита.
 *
 * ЗАПРЕЩЕНО править вручную _CLIENT_NET_MODULE_VERSION,
 * _SERVER_NET_MODULE_VERSION и _NETCODE_VERSION: эти числа обязаны совпадать
 * с бинарными netc.dll и net.dll. При мерже апстрима они берутся из
 * upstream/master как есть; нашими строками остаются только
 * _NETCODE_VERSION_BRANCH_ID и блок KONTUR_*.
 *****************************************************************************/

// Kontur MTA fork settings
#define KONTUR_FORK              1
#define KONTUR_FORK_VERSION      "kontur.1"
#define KONTUR_PUBLIC_RELEASE    0            // 0 = dev/closed test, 1 = public Kontur release
#define KONTUR_FORK_BUILD        1            // increment for every public Kontur build

// New version info
#define MTASA_VERSION_MAJOR       1
#define MTASA_VERSION_MINOR       7
#define MTASA_VERSION_MAINTENANCE 0
#if KONTUR_PUBLIC_RELEASE
    #define MTASA_VERSION_TYPE    VERSION_TYPE_UNSTABLE
    #define MTASA_VERSION_BUILD   KONTUR_FORK_BUILD
#else
    #define MTASA_VERSION_TYPE    VERSION_TYPE_CUSTOM
    #define MTASA_VERSION_BUILD   0
#endif

#include "../build_overrides.h"

// Old version info
#define MTA_DM_VERSION (((MTASA_VERSION_MAJOR) << 8) | ((MTASA_VERSION_MINOR) << 4) | ((MTASA_VERSION_MAINTENANCE) << 0))

#if MTASA_VERSION_MAINTENANCE == 0
    #define MTA_DM_VERSIONSTRING QUOTE_DEFINE(MTASA_VERSION_MAJOR) "." QUOTE_DEFINE(MTASA_VERSION_MINOR)
#else
    #define MTA_DM_VERSIONSTRING QUOTE_DEFINE(MTASA_VERSION_MAJOR) "." QUOTE_DEFINE(MTASA_VERSION_MINOR) "." QUOTE_DEFINE(MTASA_VERSION_MAINTENANCE)
#endif

#ifdef MTA_CLIENT
    #define MTA_DM_FULL_STRING "Kontur MTA Client"          // Kontur: upstream "MTA:SA Client"
#else
    #define MTA_DM_FULL_STRING "Kontur MTA Server"          // Kontur: upstream "MTA:SA Server"
#endif

// MTA_MAETRO is defined in premake5.lua

// Compile types
#define VERSION_TYPE_CUSTOM       0x01
#define VERSION_TYPE_EXPERIMENTAL 0x03
#define VERSION_TYPE_UNSTABLE     0x05
#define VERSION_TYPE_UNTESTED     0x07
#define VERSION_TYPE_RELEASE      0x09

#define QUOTE_DEFINE2(c) #c
#define QUOTE_DEFINE(x)  QUOTE_DEFINE2(x)

// Implement compile types
#if MTASA_VERSION_TYPE == VERSION_TYPE_CUSTOM
    #define MTA_DM_BUILDTYPE      "custom"
    #define MTA_DM_BUILDTAG_SHORT MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE
    #define MTA_DM_BUILDTAG_LONG  MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE
#elif MTASA_VERSION_TYPE == VERSION_TYPE_UNSTABLE
    #define MTA_DM_BUILDTYPE      "unstable"
    #define MTA_DM_BUILDTAG_SHORT MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE "-" QUOTE_DEFINE(MTASA_VERSION_BUILD)
    #define MTA_DM_BUILDTAG_LONG  MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE "-" QUOTE_DEFINE(MTASA_VERSION_BUILD)
#elif MTASA_VERSION_TYPE == VERSION_TYPE_UNTESTED
    #define MTA_DM_BUILDTYPE      "untested"
    #define MTA_DM_BUILDTAG_SHORT MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE "-" QUOTE_DEFINE(MTASA_VERSION_BUILD)
    #define MTA_DM_BUILDTAG_LONG  MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE "-" QUOTE_DEFINE(MTASA_VERSION_BUILD)
    #define MTA_DM_PUBLIC_CONNECTIONS
    #define MTA_DM_EXPIRE_DAYS 60
#elif MTASA_VERSION_TYPE == VERSION_TYPE_RELEASE
    #define MTA_DM_BUILDTYPE      "release"
    #define MTA_DM_BUILDTAG_SHORT MTA_DM_VERSIONSTRING
    #define MTA_DM_BUILDTAG_LONG  MTA_DM_VERSIONSTRING "-" MTA_DM_BUILDTYPE "-" QUOTE_DEFINE(MTASA_VERSION_BUILD)
    #define MTA_DM_PUBLIC_CONNECTIONS
#else
    #error "Incorrect MTASA_VERSION_TYPE"
#endif

// Kontur: строка версии форка для меню, титров и логов.
// Upstream-макросы MTA_DM_BUILDTAG_* специально не меняем, их парсят внутри MTA.
#define KONTUR_VERSION_STRING MTA_DM_BUILDTAG_LONG "-" KONTUR_FORK_VERSION

#define _ASE_VERSION               QUOTE_DEFINE(MTASA_VERSION_MAJOR) "." QUOTE_DEFINE(MTASA_VERSION_MINOR)
#define _NETCODE_VERSION_BRANCH_ID 0x5    // Kontur fork branch (upstream trunk = 0x4). Меняется только вместе с пересборкой клиента И сервера
#define _CLIENT_NET_MODULE_VERSION 0x0B5  // (0x000 - 0xfff) Lvl9 wizards only. Kontur: не трогать, должно совпадать с netc.dll
#define _SERVER_NET_MODULE_VERSION 0x0AD  // (0x000 - 0xfff) Lvl9 wizards only. Kontur: не трогать, должно совпадать с net.dll
#define _NETCODE_VERSION           0x1DF  // (0x000 - 0xfff) Increment when net messages change (pre-release)

// (0x000 - 0xfff) Update bitstream.h when net messages change (post-release). (Changing will also require additional backward compatibility code).
#define MTA_DM_BITSTREAM_VERSION eBitStreamVersion::Latest

// To avoid user confusion, make sure the ASE version matches only if communication is possible
#if defined(MTA_DM_PUBLIC_CONNECTIONS)
    #define MTA_DM_ASE_VERSION               _ASE_VERSION
    #define MTA_DM_NETCODE_VERSION           _NETCODE_VERSION
    #define MTA_DM_CLIENT_NET_MODULE_VERSION _CLIENT_NET_MODULE_VERSION
    #define MTA_DM_SERVER_NET_MODULE_VERSION _SERVER_NET_MODULE_VERSION
#else
    #if _NETCODE_VERSION_BRANCH_ID < 1 || _NETCODE_VERSION_BRANCH_ID > 15
        #error "_NETCODE_VERSION_BRANCH_ID wrong"
    #endif
    #define MTA_DM_ASE_VERSION               _ASE_VERSION "n"
    #define MTA_DM_NETCODE_VERSION           (_NETCODE_VERSION + (_NETCODE_VERSION_BRANCH_ID << 12))
    // Kontur: число 4 здесь — это версия бинарного модуля netc.dll (0x40B5), а не наш branch id. Не заменять на _NETCODE_VERSION_BRANCH_ID!
    #define MTA_DM_CLIENT_NET_MODULE_VERSION (_CLIENT_NET_MODULE_VERSION + (4 << 12))
    #define MTA_DM_SERVER_NET_MODULE_VERSION _SERVER_NET_MODULE_VERSION
#endif

// Handy self compile message
#ifndef MTA_DM_PUBLIC_CONNECTIONS
    // Kontur: для форка тип сборки заведомо не RELEASE, поэтому предупреждение выключено
    #if defined(SHOW_SELF_COMPILE_WARNING) && !defined(CI_BUILD) && !defined(MTA_CLIENT) && !defined(KONTUR_FORK)
        #pragma message( \
            "\n\
----------------------------------------------------------------------\n\
MTASA_VERSION_TYPE is not set to VERSION_TYPE_RELEASE\n\
Server will not work with release clients\n\
-------------------------------------------------------------------------\n\
If you want the server to work with release clients\n\
set MTASA_VERSION_TYPE to VERSION_TYPE_RELEASE in Server/version.h\n\
\n\
Client can't enter the game? Use Server net.dll from an official build.\n\
(Official dll uses VERSION_TYPE_RELEASE, win-install-data gives UNSTABLE.)\n\
-------------------------------------------------------------------------")
    #endif
#endif