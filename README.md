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
- Age of Empires II: The Conquerors
- Age of Empires: The Rise of Rome
- Age of Wonders
- Age of Wonders 2
- Age of Wonders: Shadow Magic
- Airline Tycoon Deluxe
- Alien Nations
- American Conquest (Steam+GOG)
- Amerzone
- Anno 1602
- Anstoss 3
- Arcanum
- Atlantis
- Atlantis 2
- Atlantis 3
- Atomic Bomberman
- Atrox
- Baldr Force EXE
- Baldur's Gate
- Baldur's Gate 2
- Balls Of Steel
- Blade & Sword
- Blood II - The Chosen
- Caesar III (Sierra - 1998)
- Call To Power 2
- Capitalism II
- Capitalism Lab
- Captain Claw
- Carmageddon
- Carmageddon 2
- Casino Empire (AKA Hoyle Casino)
- Chaos Gate
- Close Combat 2: A Bridge Too Far
- Close Combat 3: The Russian Front
- Close Combat 4: The Battle of the Bulge
- Close Combat 5: Invasion: Normandy
- Command & Conquer Gold
- Command & Conquer: Red Alert
- Command & Conquer: Red Alert 2
- Command & Conquer: Red Alert 2: Yuri's Revenge
- Command & Conquer: Sole Survivor
- Command & Conquer: Tiberian Sun
- Commandos
- Commandos - Beyond The Call Of Duty
- Corsairs Gold
- Cossacks (Steam+GOG)
- Cultures 2
- Dark Reign: The Future of War
- Daytona USA (Sega - 1996)
- Deadlock 2
- Desperados: Wanted Dead or Alive
- Diablo
- Diablo 2 + Lord of Destruction
- Diablo: Hellfire
- Divine Divinity
- Dragon Throne: Battle of Red Cliffs
- Dune 2000
- Dungeon Keeper
- Dungeon Keeper 2
- Economic War
- Eggsucker
- Enemy Infestation
- Escape Velocity Nova
- F-16 Multirole Fighter
- F-22 Raptor
- Fairy Tale About Father Frost, Ivan and Nastya
- Fallout
- Fallout 2
- Future Cop L.A.P.D
- G-Police
- Grand Theft Auto
- Grand Theft Auto: London 1961
- Grand Theft Auto: London 1969
- Gruntz
- Hard Truck: Road to Victory
- Hearts of Iron 2
- Heroes of Might and Magic II
- Heroes of Might and Magic III
- Heroes of Might and Magic IV
- Hooligans: Storm over Europe
- Hugo Gold
- Hugo Wild River
- Icewind Dale 2
- Infantry Online
- Interstate 76
- Invictus
- Jagged Alliance 2
- Jagged Alliance 2: Unfinished Business
- Jagged Alliance 2: Wildfire
- Kings Quest 8
- KKND Xtreme
- KKND2: Krossfire
- Knights and Merchants
- Kohan: Immortal Sovereigns
- Konung
- Konung 2
- Lionheart - Legacy of the Crusader
- Locomotion
- Majesty Gold
- Majesty Gold HD
- Mech Warrior 3
- Megaman X4
- Moorhuhn
- Moorhuhn 2
- Moorhuhn Winter Editon
- Nancy Draw: Last Train to Blue Moon Canyon
- Nancy Drew: Secrets Can Kill
- Nancy Drew: Stay Tuned For Danger
- Need For Speed III: Hot Pursuit
- Need For Speed: High Stakes
- New Robinson
- NexusTk
- Nox (Westwood - 2000)
- Oddworld: Abe's Exoddus
- Oddworld: Abe's Oddysee
- Outlaws
- Outlive
- Pax Imperia
- Pharaoh (Sierra - 1999)
- Pizza Syndicate (AKA Fast Food Tycoon)
- Populous: The Beginning
- Poseidon: Master of Atlantis
- Quest for Glory 5
- Rage of Mages 2
- Railroad Tycoon II
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
- Shadow Flare
- Shadow Watch
- Shogo - Mobile Armor Division
- Sim City 3000
- Sim Copter
- Sim Theme Park (aka Theme Park World)
- Space Rangers
- Star Wars Jedi Knight: Dark Forces II
- Star Wars: Galactic Battlegrounds
- Star Wars: Galactic Battlegrounds: Clone Campaigns
- StarCraft
- Starship Titanic
- Start Trek Armada
- Steel Panthers: World At War
- Stronghold Crusader Extreme HD
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
- Uprising
- Uprising 2
- Vermeer
- Virtua Fighter PC
- War Wind
- Warcraft 2
- Wizardry 8
- Wizards and Warriors
- Worms 2
- Worms Armageddon
- Zeus: Master of Olympus
 - ...

There are a lot more games supported but I don't usually update the list, just give it a try and if it doesn't work then check the [wiki](https://github.com/FunkyFr3sh/cnc-ddraw/wiki) and the instructions above.


[![](https://img.shields.io/github/downloads/FunkyFr3sh/cnc-ddraw/total)](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip)
