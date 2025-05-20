# CotAA
CotAA - аббривеатура из первых букв названия - "Curse of the Alchemical Abyss"
CotAA - abbreviation of the first letters - "Curse of the Alchemical Abyss"
# Ru:
Проект выполнен в рамках учебного плана производственной и преддипломных практик, а также выпускной квалификационной работы
студентом Южного Федерального университета кафедры МОП ЭВМ группы КТбо4-8: Демьяненко Д.А.
Научный руководитель: доцент Лутай В.Н.

## Цели разработки
Даный проект был разработан с целью демонстрации навыков полученных в ходе обучения и демонстрирует следующие компетенции:
- Проектирование систем
- Разработка приложений с использованием C++
- Использование паттернов проектирования
- Работа с большими наборами данных
- Составление плана тестирования и использование различных методик для его проведения

## Установка и запуск
В сохранённой в GitHub версии выложена исключительно Development, поскольку при упаковке игры в Shipping - часть файлов будет хеширована (имеется в виду - для экономии пространства жёстких дисков) или зашифрована и НЕ БУДЕТ доступна для чтения исходного кода.
В случае же упаковки игры в Shipping - будет .exe файл, который будет запускать уровень главного меню (указан в конфигах через редактор, как стартовый)

# Важное уведомление
Данный проект является **некоммерческим** и соответствует условиям всех используемых ассетов.
**Запрещается распространение оригинальных ассетов** - любое коммерческое использование или распространение исходных ассетов без разрешения правообладателей запрещено.

## Что в себя включает проект:
- Главное меню с возможностью начать новую игру, изменить некоторые настройки графики. Система сохранений и возможность сетевой игры - в разработке.
- Основной уровень являющийся дополненным демо: "POLYGON - SwampMarshland - Nature Biomes", с башней и некоторыми объектами из "POLYGON - Elven Realm" предоставленными компанией ООО "Тек Раунд".
- Основной уровень включает в себя:
    - прототип персонажа игрока: манекен UE4 с рядом компонент для взаимодействия с окружением и NPC
    - прототип собираемых объектов (растения, грибы и т.д.) в качестве материалов для зелий
    - прототип противников: перекрашенный в красный манекен UE4
    - прототип крафт.станции (в разработке)
- Игрок имеет инвентарь, созданный на основе ассета "Adventurer's Inventory Kit" https://www.fab.com/listings/9c88eecb-7907-4632-94cc-1e773a6722fb (часть логики реализована в
C++, а также имеются изменения под видение игры разработчиком)
- Таблицы данных о предметах для их хранения и взаимодействия

# En (translated using AI because it is faster)
Project developed as part of the academic curriculum for industrial and pre-graduation internships, as well as the final qualifying work by Demyanenko D.A., a student of Southern Federal University, Department of Computer Engineering, group KTbo4-8.  
Academic supervisor: Associate Professor Lutay V.N.

## Development Goals
This project was created to demonstrate skills acquired during studies and showcases the following competencies:
- System design
- C++ application development
- Design patterns implementation
- Working with large datasets
- Test planning and execution using various methodologies

## Installation and Launch
The GitHub repository contains only the Development version, as packaging the game in Shipping mode would:
- Hash/encrypt some files (to save disk space)
- Make source code unreadable  
When packaged in Shipping mode, the game will produce an .exe file that launches the main menu level (set as default in editor configurations).

## Important Notice
This project is **non-commercial** and complies with all used assets' licensing terms.  
**Redistribution of original assets is prohibited** - any commercial use or distribution of source assets without copyright holders' permission is forbidden.

## Project Contents:
- Main menu with options to:
  - Start new game
  - Adjust graphics settings
  - (Save system and multiplayer - in development)
- Main level based on enhanced "POLYGON - SwampMarshland - Nature Biomes" demo, featuring:
  - A tower and objects from "POLYGON - Elven Realm" (provided by Tek Round LLC)
- The main level contains:
  - Player character prototype: UE4 mannequin with environment/NPC interaction components
  - Collectible objects prototype (plants, mushrooms, etc.) for potion crafting
  - Enemy prototype: recolored red UE4 mannequin
  - Crafting station prototype (in development)
- Inventory system based on "Adventurer's Inventory Kit" (https://www.fab.com/listings/9c88eecb-7907-4632-94cc-1e773a6722fb) with:
  - Partial C++ implementation
  - Custom modifications aligning with developer's vision
- Item data tables for storage and interaction

## Информация о ходе разработки
- Перемещение персонажа игрока / Player Movement and basic controls √
- Система интеракций с внутриигровыми объектами / Player Interaction with in-game world objects system √
- Инвентарь персонажа   / Player Inventory √ 
- Данные о предметах, конкретно о материалах для создания зелий / Item's data tables, specifically materials for creating potions (частично/partially) √
- Главное меню с 3D-сценой на фоне / Main menu with 3D-scene on background √
- Меню настроек / Options menu (частично, есть только настройки графики / partially, only graphics) √
- Основной игровой уровень / Main Level √
- Интерактивные объекты / Interactables (частично, работа в процессе / partially, WIP)
- Станция создания зелий / Potion crafting station - WIP
- Тестовый противник\и / Testing enemies - WIP
- Система характеристик и эффектов для игрока и NPC / Characteristics and effects system for player and NPC - WIP

Возможно добавление мульиплеера (кооперативного режима) вида "Сервер-клиент", поскольку это входит в встроенный функционал Unreal Engine 5 с целью изучения данной области.
It is possible to add a multiplayer (cooperative mode) of the "Server-Client" type, since this is part of the built-in functionality of Unreal Engine 5 for the purpose of studying this area.

## Информация о лицензиях / License information
### POLYGON - SwampMarhsland
    Ссылка/Link: -
    Лицензия/License - Custom Academic License (Provided by Tek Round LLC)
### POLYGON - Elven Realm
    Ссылка/Link: -
    Лицензия/License - Custom Academic License (Provided by Tek Round LLC)
### 60 free icons
    Ссылка/Link: https://www.fab.com/listings/fc9f4a87-3168-4c9b-a71c-89b4bf31692e
    Лицензия/License: Personnel/Non-Commersial
### Craft Resources icons
    Ссылка/Link: https://www.fab.com/listings/3b8cee16-7a22-4ddc-bd63-9b7650813855
    Лицензия/License: Personnel/Non-Commersial
### RPG Music Pack: Starter Pack I
    Ссылка/Link: https://www.fab.com/listings/3b8cee16-7a22-4ddc-bd63-9b7650813855
    Лицензия/License: Personnel/Non-Commersial
### Low Poly Nature: Essentials
    Ссылка/Link: https://www.fab.com/listings/a607441d-b811-440b-a20c-59e74804c4ce
    Лицензия/License: Personnel/Non-Commersial
### UE5 Starter Pack Content
    Ссылка/Link: -
    Лицензия/License: Epic EULA

Developed with Unreal Engine 5
