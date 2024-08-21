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

Wine (Linux/macOS/Android) only: override `ddraw` in [winecfg](https://wiki.winehq.org/Winecfg#Libraries) manually or run cnc-ddraw config.exe once.

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

Need help and don't have a github account? Ask your questions on [Discord](https://discord.gg/afWXJNDDF5) (No registration required)

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
- American Girls Dress Designer
- Amerzone
- Anno 1602: Creation of a New World
- Anstoss 3
- Arcanum: Of Steamworks and Magick Obscura
- Arthur's Pet Chase
- Arthur's Sand Castle Contest
- Arthur's Wilderness Rescue
- Atlantis 2: Beyond Atlantis
- Atlantis 3: The New World
- Atlantis: The Lost Tales
- Atomic Bomberman
- Atrox
- Baldr Force EXE
- Baldur's Gate
- Baldur's Gate 2
- Barbie(tm) Beach Vacation(tm)
- Barbie(R) Photo Designer
- Batman: Justice Unbalanced
- Batman: Toxic Chill
- Blade & Sword
- Blood II - The Chosen
- Blue's 123 Time Activities
- Blue's Treasure Hunt
- Caesar III (Sierra - 1998)
- Callus 95 - CPS-1 (Capcom Play System 1) emulator
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
- ClueFinders 3rd Grade Adventures
- ClueFinders 4th Grade Adventures
- ClueFinders 5th Grade Adventures
- ClueFinders 6th Grade Adventures
- ClueFinders Math Adventures 1.0
- ClueFinders Math Adventures 2.0
- ClueFinders Mystery Mansion
- ClueFinders Search and Solve Adventures
- ClueFinders The Incredible Toy Store Adventure
- ClueFinders(R) Reading Adventures Ages 9-12
- Command & Conquer Gold
- Command & Conquer: Red Alert
- Command & Conquer: Red Alert 2
- Command & Conquer: Red Alert 2: Yuri's Revenge
- Command & Conquer: Sole Survivor
- Command & Conquer: Tiberian Sun
- Commandos
- Commandos - Beyond The Call Of Duty
- Commandos 2
- Constructor
- Corsairs Gold
- Cossacks (Steam+GOG)
- Cultures - The Discovery of Vinland
- Cultures 2
- Cyberchase Carnival Chaos
- Cyberchase Castleblanca Quest
- Dark Reign: The Future of War
- Daytona USA (Sega - 1996)
- Deadlock 2
- Desperados: Wanted Dead or Alive
- Diablo
- Diablo 2
- Diablo 2: Lord of Destruction
- Diablo: Hellfire
- Disciples
- Disciples 2 - Rise of the Elves
- Divine Divinity
- Dragon Throne: Battle of Red Cliffs
- DuelSavior
- DuelSavior: Justice
- Dune 2000
- Dungeon Keeper
- Dungeon Keeper 2
- Economic War
- Eggsucker
- Emperor: Rise of the Middle Kingdom
- Enemy Infestation
- Escape Velocity Nova
- F-16 Multirole Fighter
- F-22 Raptor
- Fairy Tale About Father Frost, Ivan and Nastya
- Fallout
- Fallout 2
- Final fantasy VII
- Final fantasy VIII
- Freddi Fish
- Freddi Fish 4
- Freddi Fish's One-Stop Fun Shop
- Freddi Fish: Maze Madness
- Freddi Fish: The Case of the Creature of Coral Cove
- Freddi Fish: The Case of the Haunted Schoolhouse
- Freddi Fish: The Case of the Hogfish Rustlers of Briny Gulch
- Freddi Water Worries
- Future Cop L.A.P.D
- G-Police
- Grand Theft Auto
- Grand Theft Auto: London 1961
- Grand Theft Auto: London 1969
- Gruntz
- Gorasul: The Legacy of the Dragon
- Hamtaro: Wake Up Snoozer!
- Hard Truck: Road to Victory
- Hearts of Iron 2
- Heroes of Might and Magic II
- Heroes of Might and Magic III
- Heroes of Might and Magic IV
- Hooligans: Storm over Europe
- Hugo Gold
- Hugo Wild River
- Icewind Dale
- Icewind Dale 2
- Infantry Online
- Interstate 76
- Invictus: In the Shadow of Olympus
- Jagged Alliance 2
- Jagged Alliance 2: Unfinished Business
- Jagged Alliance 2: Wildfire
- Jazz Jackrabbit 2
- Killing Time
- Kings Quest 8: Mask of Eternity
- KKND Xtreme
- KKND2: Krossfire
- Knights and Merchants: The Peasants Rebellion
- Knights and Merchants: The Shattered Kingdom
- Kohan: Immortal Sovereigns
- Konung
- Konung 2
- Lapis (lapis.mgame.com)
- Lionheart - Legacy of the Crusader
- Little Bear Kindergarten Thinking Adventures
- Little Bear Preschool Thinking Adventures
- Little Bear Rainy Day Activities
- Little Bear Toddler Discovery Adventures
- Locomotion
- Lode Runner 2
- Madeline 1st Grade Math
- Madeline 2nd Grade Math
- Majesty Gold
- Majesty Gold HD
- ​M.A.X. 2 Mechanized Assault & Exploration
- Mech Warrior 3
- Megaman X4
- Metal Gear Solid
- Mob Rule (AKA Constructor: Street Wars / Street Wars: Constructor Underworld)
- Moorhuhn
- Moorhuhn 2
- Moorhuhn Winter Editon
- Moto Racer
- Moto Racer 2
- Nancy Drew: Danger on Deception Island
- Nancy Drew: Last Train to Blue Moon Canyon
- Nancy Drew: Message in a Haunted Mansion
- Nancy Drew: Secrets Can Kill
- Nancy Drew: Stay Tuned For Danger
- Nancy Drew: The Secret of Shadow Ranch
- Nancy Drew: Treasure in the Royal Tower
- Need For Speed III: Hot Pursuit
- Need For Speed: High Stakes
- New Robinson
- NexusTk
- Nox (Westwood - 2000)
- Oddworld: Abe's Exoddus
- Oddworld: Abe's Oddysee
- Outlaws
- Outlive
- Pacific General
- Pajama Sam
- Pajama Sam 3
- Pajama Sam's Games to Play on Any Day
- Pajama Sam's One-Stop Fun Shop
- Pajama Sam(r): Life is Rough When You Lose Your Stuff(tm)
- Pajama Sam: No Need to Hide When It's Dark Outside
- Pajama Sam 3: You Are What You Eat From Your Head To Your Feet
- Patrician 3
- Pax Imperia
- Pharaoh (Sierra - 1999)
- Pizza Syndicate (AKA Fast Food Tycoon)
- Populous: The Beginning
- Poseidon: Master of Atlantis
- Pro Pinball - Big Race USA
- Pro Pinball - Fantastic Journey
- Putt-Putt and Pep's Balloon-o-Rama
- Putt-Putt and Pep's Dog On A Stick
- Putt-Putt Joins the Circus
- Putt-Putt Saves The Zoo
- Putt-Putt's One-Stop Fun Shop
- Putt-Putt: Pep's Birthday Surprise
- Putt-Putt: Travels Through Time
- Quest for Glory 5
- Rage of Mages 2
- Railroad Tycoon II
- Reader Rabbit 1st Grade
- Reader Rabbit 2nd Grade
- Reader Rabbit Dreamship Tales
- Reader Rabbit Kindergarten
- Reader Rabbit Learn To Read With Phonics
- Reader Rabbit Learning Creations
- Reader Rabbit Math Ages 4-6
- Reader Rabbit Preschool 2002
- Reader Rabbit Reading Ages 4-6
- Reader Rabbit Reading Ages 6-9
- Reader Rabbit Thinking Ages 4-6 (US)
- Reader Rabbit Toddler
- Reader Rabbit's(R) Math Ages 6 - 9 (2002)
- Real War
- Red Baron 3D
- Reksio and the Pirate Treasure (Reksio i Skarb Piratów)
- Reksio and the UFO (Reksio i Ufo)
- Reksio and the Wizards (Reksio i Czarodzieje)
- Reksio and the Time Machine (Reksio i Wehikuł Czasu)
- Reksio and Captain Nemo (Reksio i Kapitan Nemo)
- Reksio and Kretes in Action (Reksio i Kretes w Akcji!)
- Road Rash
- Robin Hood - The Legend of Sherwood
- RollerCoaster Tycoon
- Sanitarium
- Scooby-Doo(TM), Case File #2 The Scary Stone Dragon
- Scooby-Doo(TM), Phantom of the Knight(TM)
- Scooby-Doo(TM), Showdown in Ghost Town(TM)
- Sega Rally
- Sega Touring Car
- Septerra Core
- Settlers 3
- Shadow Flare
- Shadow Watch
- Shogo - Mobile Armor Division
- Sim City 3000
- Sim Copter
- Sim Theme Park (aka Theme Park World)
- SimCoaster / Theme Park Inc
- Sonic 3D Blast
- Space Rangers
- SpongeBob SquarePants: Typing
- SPY Fox : Some Assembly Required
- SPY Fox in Dry Cereal
- SPY Fox: Hold the Mustard
- SPY Fox: Operation Ozone
- Star Wars Jedi Knight: Dark Forces II
- Star Wars: Galactic Battlegrounds
- Star Wars: Galactic Battlegrounds: Clone Campaigns
- StarCraft
- StarCraft: Broodwars
- StarFlyers Alien Space Chase
- StarFlyers Royal Jewel Rescue
- Starship Titanic
- Start Trek Armada
- Steel Panthers: World At War
- Strawberry Shortcake: Amazing Cookie Party
- Stronghold Crusader Extreme HD
- Stronghold Crusader HD
- Stronghold HD
- Sudden Strike 2
- The Missing on Lost Island
- The Powerpuff Girls - Princess Snorebucks
- The Powerpuff Girls(TM) Mojo Jojo's Clone Zone
- The X-Files DVD
- Theme Hospital
- Three Kingdoms: Fate of the Dragon
- Throne of Darkness
- Total Annihilation
- Total Annihilation (Unofficial Beta Patch v3.9.02)
- Total Annihilation: Kingdoms
- Twisted Metal
- Twisted Metal 2
- Tzar: The Burden of the Crown
- Uprising 2: Lead and Destroy
- Uprising: Join or Die
- Vermeer
- Virtua Fighter PC
- War Wind
- War Wind II - Human Onslaught
- WarCraft 2000: Nuclear Epidemic
- Warcraft 2
- Warlords 3: Darklords Rising
- Warlords Battlecry
- Warlords Battlecry 2
- Warlords Battlecry 3
- Wizardry 8
- Wizards and Warriors
- Worms 2
- Worms Armageddon
- Zeus: Master of Olympus
- Zoombinis Island Odyssey
- Zoombinis Logical Journey
- Zoombinis Mountain Rescue
- Zuma Deluxe
 - ...

There are a lot more games supported but I don't usually update the list, just give it a try and if it doesn't work then check the [wiki](https://github.com/FunkyFr3sh/cnc-ddraw/wiki) and the instructions above.


[![](https://img.shields.io/github/downloads/FunkyFr3sh/cnc-ddraw/total)](https://github.com/FunkyFr3sh/cnc-ddraw/releases/latest/download/cnc-ddraw.zip)
