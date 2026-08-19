\# Kontur MTA — карточка форка



\## База

\- Апстрим: https://github.com/multitheftauto/mtasa-blue

\- Базовый тег апстрима: 1.6.0-9.23456

\- Базовый коммит: e3ed206f68896da32edbf77ef0806860ffdda392

\- Метка базы в нашем репозитории: тег kontur-base



\## Режим дистрибутива

MODE=A (bundled)

Игра вкладывается в дистрибутив, папка bin собирается на сборочной машине,

патчи запекаются функцией bake\_patches в tools/pack\_dist.py.

Запасной режим B (импорт игры у игрока) остаётся рабочим: python tools/pack\_dist.py B



\## Требуемая версия GTA:SA 1.0 US

\- gta\_sa.exe размер: 14383616

\- gta\_sa.exe MD5: 84A781F30FAC7EBA030AF2497DA86930

\- допустимые размеры вообще: 14383616 или 14405632



\## Сеть и версии

\- Порт сервера: 23003

\- HTTP-порт: 23005

\- Тестовый сервер: 23013 / 23015

\- Суффикс версии клиента: kontur.1

\- minclientversion на сервере: 1.6.0-9.kontur.1



\## Отличия от апстрима (обновлять по мере работы)

\- Шаг 3: файл Shared/sdk/KonturBranding.h, переименование EXE, свои адреса

\- Шаг 4: портативные пути, реестр Rockstar не читается

\- Шаг 6: папка patches и накат патчей

\- Шаг 7: тема skins/Kontur по умолчанию

\- Шаг 8: подписанный список серверов priv/server-ids.xml



\## Ветки

kontur/main — релизная

kontur/branding, kontur/portable, kontur/patches, kontur/skins, kontur/whitelist, kontur/custom-models

Порядок мержа: branding, portable, patches, skins, whitelist, custom-models



\## Что НЕ в git

D:\\kontur\\\_keys — приватные ключи подписи

D:\\kontur\\\_source\\gta\_sa\_1.0\_us — чистая игра

D:\\kontur\\\_dist — собранные дистрибутивы

