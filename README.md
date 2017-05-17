# Talented-GM

## Disclaimer
*Wild Talents* was created by and belongs to Arc Dream Publishing. I am in no way affiliated with Arc Dream Publishing and do not make money off this program.

## Description
Talented GM is a simple tool for game masters (GMs) of the role-playing game *Wild Talents*. Using TalentedGM, one can create custom non-player characters (NPCs). This includes stats, skills, and hitboxes. These NPCs, along with minions, can be combined to make up custom locations. While a game is in process, one can load NPCs or locations into the current turn. Each turn also allows for intiative tracking and miscellaneous notes. After a game has finished, all turns can be exported into a log file.

At least, that is what will be possible once it is programmed. At the moment, virtually no features are available.

## Dependecies
 * Qt version 5 or above
 
## Installation
Installation is not currently automated, but I will have a make file ready at some point. There are finished binaries located in the /bin directory, but they may not always be up to date.

## Usage
The program is divided into four tabs: general, turns, templates, and editor. The general tab is for use before or after a game. The turn tab is used during combat or non-combat turns. The templates tab can be used to manage location, NPC, player, or note templates. Finally, the editor is where locations and NPCs can be created. Detailed information of each tab is included below.

### General tab
This tab contains a segment for general notes about the game. These notes are not tied to a turn and will not be included in the log file. The tab also contains buttons for creating new game files, saving game files, exporting files, etc.

### Turn tab
This tab contains all information for the current turn. In the bottom right, the "next turn" and "previous turn" buttons can be used to navigate through turns. From this menu, any location or NPC template can be loaded into the current turn. There is also a display for all NPC hitboxes on the top left and NPC info on the bottom left. The top right includes an initiative pane. Here, the actions of all players and NPCs are recorded. Finally, the bottom right includes an editor for turn notes. These notes are associated with the current turn and will be included in the log file.

### Templates tab
The templates tab is used for managing templates. Location and NPC templates can be deleted on the left side. The bottom right includes a note template. This is the default value for the turn notes and will be added to the turn notes whenever a new turn is created. Finally, the top right contains a template for the players in the game. This is used to determine the number of players in any new turn.

### Editor tab
The editor tab is used for editing locations and NPCs. The left side is for locations, the right for NPCs. On each side a template can be loaded and edited. When the "add to templates" button is clicked, all changes to the template are saved. Alternatively, the "add to turn" button will not modify the template but add the NPC or location to the current turn.

## Copyright
Copyright (C) 2017 Zoe Krueger

Copying and distributing this project, with or without modification, is conditionally permitted according to the LGPLv3 license, a copy of which is provided in this repository. 
