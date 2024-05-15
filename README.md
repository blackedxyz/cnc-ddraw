# cnc-ddraw
cnc-ddraw can fix compatibility issues in older 2D games, such as black screen, bad performance, crashes or defective Alt+Tab.

&nbsp;

### Features

 - Supports Windows 2000, XP, Vista, 7, 8, 10, 11, Wine (Linux/macOS/Android) and Virtual Machines
 - GDI / OpenGL / Direct3D 9 renderer (With automatic renderer selection)
 - Upscaling via glsl shaders - https://imgur.com/a/kxsM1oY | https://imgur.com/a/wjrhpFV
 - Windowed Mode / Fullscreen Exclusive Mode / Borderless Mode
 - Alt+Enter support to switch quickly between Fullscreen and Windowed mode
 - Automatically saves and restores window position/size/state
 - FPS Limiter
 - VSync
 - Optional mouse sensitivity scaling
 - Preliminary libretro shader support - https://github.com/libretro/glsl-shaders
 - ...
 
&nbsp;

### Instructions

1. Download [cnc-ddraw.zip](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip) and extract it into your game folder
2. Start the game

Wine (Linux/macOS) only: override `ddraw` in [winecfg](https://wiki.winehq.org/Winecfg#Libraries) manually or run cnc-ddraw config.exe once.

&nbsp;

If you use cnc-ddraw with a game that got its own windowed mode built in then **make sure you disable the games own windowed mode** first. You can enable windowed mode via cnc-ddraw config.exe instead.

&nbsp;

**If the game starts but it doesn't work perfectly** then open the config program and check the **Compatibility settings**.

&nbsp;

**cnc-ddraw does not support Direct3D/Glide**, it will only work with games that use a **DirectDraw (Software)** renderer. Usually you can tell by the look of the game if it's a 3D game or not, but you can also let cnc-ddraw generate a debug log and search for "IDirect3D" - Link: https://github.com/FunkyFr3sh/cnc-ddraw/issues/44

&nbsp;

Some games may require additional steps before they can be used with cnc-ddraw, please check the [wiki](https://github.com/FunkyFr3sh/cnc-ddraw/wiki) for more details.

&nbsp;

**If the game doesn't start at all or it's crashing**, [then please generate a debug log file and upload it.](https://github.com/FunkyFr3sh/cnc-ddraw/issues/44)  

&nbsp;

### Hotkeys
* [Alt] + [Enter]                  = Switch between windowed and fullscreen mode
* [Ctrl] + [Tab]                    = Unlock cursor
* [Right Alt] + [Right Ctrl]  = Unlock cursor
* [Alt] + [Page Down]        = Maximize window

&nbsp;

### Supported Games
- Age of Empires
- Age of Empires II
- Age of Wonders
- Age of Wonders 2
- Age of Wonders: Shadow Magic
- Alien Nations
- American Conquest (Steam+GOG)
- Amerzone
- Anstoss 3
- Arcanum
- Atomic Bomberman
- Atrox
- Baldr Force EXE
- Baldur's Gate
- Baldur's Gate 2
- Balls Of Steel
- Blade & Sword
- Caesar III (Sierra - 1998)
- Capitalism II
- Capitalism Lab
- Captain Claw
- Carmageddon
- Carmageddon 2
- Casino Empire (AKA Hoyle Casino)
- Chaos Gate
- Command & Conquer Gold
- Command & Conquer: Red Alert
- Command & Conquer: Red Alert 2
- Command & Conquer: Red Alert 2: Yuri's Revenge
- Command & Conquer: Tiberian Sun
- Commandos
- Commandos - Beyond The Call Of Duty
- Corsairs Gold
- Cossacks (Steam+GOG)
- Cultures 2
- Dark Reign: The Future of War
- Daytona USA (Sega - 1996)
- Desperados: Wanted Dead or Alive
- Diablo
- Diablo 2 + Lord of Destruction
- Divine Divinity
- Dragon Throne: Battle of Red Cliffs
- Dune 2000
- Dungeon Keeper
- Dungeon Keeper 2
- Economic War
- Eggsucker
- Enemy Infestation
- EV Nova
- F-16 Multirole Fighter
- F-22 Raptor
- Fairy Tale About Father Frost, Ivan and Nastya
- Fallout
- Fallout 2
- Future Cop L.A.P.D
- Grand Theft Auto
- Gruntz
- Hearts of Iron 2
- Heroes of Might and Magic II
- Heroes of Might and Magic III
- Heroes of Might and Magic IV
- Hooligans: Storm over Europe
- Hugo Gold
- Hugo Wild River
- Icewind Dale 2
- Infantry Online
- Jagged Alliance 2
- Jagged Alliance 2: Unfinished Business
- Jagged Alliance 2: Wildfire
- KKND Xtreme
- KKND2: Krossfire
- Knights and Merchants
- Kohan: Immortal Sovereigns
- Lionheart - Legacy of the Crusader
- Locomotion
- Mech Warrior 3
- Megaman X4
- Moorhuhn
- Moorhuhn 2
- Moorhuhn Winter Editon
- Nancy Drew: Secrets Can Kill
- Nancy Drew: Stay Tuned For Danger
- Need For Speed III: Hot Pursuit
- Need For Speed: High Stakes
- New Robinson
- NexusTk
- Nox
- Nox (Westwood - 2000)
- Oddworld: Abe's Exoddus
- Oddworld: Abe's Oddysee
- Outlaws
- Outlive
- Pharaoh (Sierra - 1999)
- Pizza Syndicate (AKA Fast Food Tycoon)
- Populous: The Beginning
- Quest for Glory 5
- Rage of Mages 2
- Red Baron 3D
- Reksio and Captain Nemo (AKA Reksio si Capitanul Nemo)
- Reksio and Kretes in Action (AKA Reksio si Kretes in Actiune)
- Reksio and the Pirate Treasure (AKA Reksio si Comoara Piratilor)
- Reksio and the Time Machine (AKA Reksio si Masina Timpului)
- Reksio and the UFO (AKA Reksio si OZN-ul)
- Reksio and the Wizards (AKA Reksio si Magicienii)
- Road Rash
- RollerCoaster Tycoon
- Septerra Core
- Settlers 3
- Sim City 3000
- Sim Copter
- Sim Theme Park (aka Theme Park World)
- Sole Survivor
- Space Rangers
- Star Wars Jedi Knight: Dark Forces II
- Star Wars: Galactic Battlegrounds
- StarCraft
- Starship Titanic
- Start Trek Armada
- Steel Panthers: World At War
- Stronghold Crusader HD
- Stronghold HD
- Theme Hospital
- Three Kingdoms: Fate of the Dragon
- Total Annihilation
- Total Annihilation (Unofficial Beta Patch v3.9.02)
- Total Annihilation: Kingdoms
- Twisted Metal
- Twisted Metal 2
- Tzar: The Burden of the Crown
- Vermeer
- Virtua Fighter PC
- War Wind
- Warcraft 2
- Wizardry 8
- Wizards and Warriors
- Worms 2
- Zeus: Master of Olympus
 - ...

There are a lot more games supported but I don't usually update the list, just give it a try and if it doesn't work then check the [wiki](https://github.com/FunkyFr3sh/cnc-ddraw/wiki) and the instructions above.


[![](https://img.shields.io/github/downloads/FunkyFr3sh/cnc-ddraw/total)](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip)
