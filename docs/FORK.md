\# Kontur MTA — карточка форка



\## База

\- Апстрим: https://github.com/multitheftauto/mtasa-blue

\- Базовый тег апстрима: v1.6.0

\- Базовый коммит: e3ed206f68896da32edbf77ef0806860ffdda392

\- Метка базы в своём репозитории: тег kontur-base

\- Основная ветка форка: kontur/main



\## Режим дистрибутива

MODE=A (bundled)

\- Файлы игры вкладываются в дистрибутив (папка bin) и внутрь установщика.

\- Патчи запекаются на сборочной машине функцией bake\_patches в tools/pack\_dist.py.

\- Локальная сборка: win-pack-dist.bat без аргументов (= режим A).

\- На CI только режим B: python tools/pack\_dist.py B — файлов игры на раннере нет.

\- Вес установщика 3-4 ГБ: GitHub Releases с лимитом 2 ГБ не подходит, нужен свой хостинг.

\- Юридический риск раздачи файлов Rockstar принят осознанно, публичные площадки не используем.



\## Требуемая версия игры

\- GTA: San Andreas 1.0 US, только она.

\- Допустимый размер gta\_sa.exe: 14383616 или 14405632 байт.

\- Размер нашего эталона: 14383616

\- MD5 нашего эталона: 84A781F30FAC7EBA030AF2497DA86930

\- Эталон лежит в D:\\kontur\\\_source\\gta\_sa\_1.0\_us, никогда не патчится и не запускается.



\## Сеть и версии

\- Порт игры 23003, HTTP-порт 23005. Тестовый сервер: 23013 и 23015.

\- Апстримные 22003 и 22005 не используются нигде.

\- Суффикс версии форка: kontur.1

\- minclientversion на сервере: 1.6.0-9.kontur.1

\- Мастер-лист, анонс, обновления, краши: только домены kontur-mta.example



\## Окружение сборки

\- Visual Studio 2022 (версия 17.x), нагрузка Desktop development with C++, MSVC v143, Windows 11 SDK, ATL.

\- Конфигурация только Release | Win32: клиента под x64 не существует.

\- Python 3.9+, NSIS 3.x с плагинами nsProcess и Inetc, Git + Git LFS, ripgrep, 7-Zip.

\- CEF: 114.2.10+g398e3c3+chromium-114.0.5735.110, дистрибутив windows32 MINIMAL (не standard, не sandbox, не client).

\- sha256 архива CEF: 28f848e2dd44870cb630c49090409e96b6574a12f01f7ab20a3263de0aeff49f

\- Архив хранится как vendor/cef3/temp.tar.bz2, распакованное — vendor/cef3/cef. В git не попадает.

\- Ручное восстановление CEF без сети: положить архив в vendor/cef3/temp.tar.bz2, удалить папку vendor/cef3/cef, запустить win-create-projects.bat.



\## Отличия от апстрима

1\. Файлы форка в корне: SOURCE-OFFER.txt, docs/FORK.md, дополненные .gitignore и .gitattributes. LICENSE апстрима не изменён.

2\. utils/buildactions/install\_cef.lua, функция make\_cef\_download\_url(): символ "+" кодируется как %2B заглавной буквой вместо http.escapeUrlParam. Зеркало cef-builds.spotifycdn.com чувствительно к регистру: с %2b отдаёт 403 Forbidden, из-за чего win-create-projects.bat падал на загрузке CEF. Правка в чужом файле — ждать конфликт при мерже апстрима.

3\. Шаг 3, ребрендинг: новый Shared/sdk/KonturBranding.h; version.h — порты и суффикс версии; Client/launch — targetname "Kontur MTA" и иконка; тексты меню, настроек, кредитов и все адреса.

4\. Шаг 4, портативность: путь к игре — подпапка bin рядом с EXE, реестр Rockstar не читается; профиль, логи, temp и кеш ресурсов внутри папки дистрибутива.

5\. Шаг 6, патчи игры: папка patches, manifest.json, новые Client/loader/KonturPatches.cpp и .h.

6\. Шаг 7, своя тема Kontur как тема по умолчанию плюс фолбэк при отсутствии папки темы.

7\. Шаг 8, белый список серверов: priv/server-ids.xml с подписью ed25519, новые Client/core/CKonturServerList.cpp и .h.

8\. Шаг 9, сервер: ase=0, отключённый LAN-броадкаст, minclientversion с суффиксом форка, ресурс kontur-core.



\## Ветки

\- kontur/main — основная.

\- Рабочие: kontur/branding, kontur/portable, kontur/patches, kontur/skins, kontur/whitelist, kontur/custom-models.

\- Порядок мержа строго: branding, portable, patches, skins, whitelist, custom-models.



\## Что не в git

\- D:\\kontur\\\_keys — приватные ключи ed25519 для подписи списка серверов и обновлений.

\- D:\\kontur\\\_source\\gta\_sa\_1.0\_us — чистая игра.

\- D:\\kontur\\\_dist — собранные дистрибутивы и установщики.

\- vendor/cef3 — скачивается скриптом install\_cef.lua.

