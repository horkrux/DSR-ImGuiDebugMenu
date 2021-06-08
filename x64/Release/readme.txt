DSR DEBUG MENU v1.0

DESCRIPTION
-------------
This mod restores the debug menu for Dark Souls: Remastered and includes some additional debug enhancements 
to make modding the game more pleasant:

*Debug output console (LUA/ESD)
*Debug Dash movement (Fast speed, Noclip, No gravity)
*Debug config (game.properties)

HOW TO INSTALL/DELETE
-------------
Just drop game.properties and dinput8.dll from the archive into the game's folder. To deactivate the mod, remove or rename the dinput8.dll.
If you're already using a dinput8 mod and want to use it together with the debug menu, 
you can rename the other mod's dll and put this name between the ""
in game.properties under Misc->dinput8DllWrapper.

HOW TO USE
-------------
I recommend disabling TAA in the game's options, because it doesn't work too well with some of the debug draw.

The console can either be enabled from game.properties (Game->IsUseDbgConsole) or from the 
debug menu itself (GAME->WorldAiMan->LUA global name management...) by pressing X + A when the option is selected.
You can use the function ai:PrintText to print text from your custom AI. ESD debug output needs to be enabled for
each character separately (GAME->CHR INS->WORLD CHR MAN->(Chr entry)->Action->Delay init debug menu->EzState(From the check print)).
The original ESD function for printing was enhanced to support formatted strings.

Debug Menu Controls:
SELECT: 		Open Debug Menu
R1 + R2 + L1: 		Open New Window
R1 + DPAD: 		Move to Next Parent Node
R1 + L STICK: 		Move Window
R1 + L2: 		Move to Previous Window
R1 + L1: 		Move to Next Window
R1 + R2 + L2: 		Close Window
R1 + R2 + R STICK: 	Scale Window
R1 + R2 + L STICK:	Change Number of Lines Displayed

Gameplay Controls:
R1 + R2 + L2:		Open Gesture Menu
L3:			Activate Debug Dash

Debug Dash Controls:
L3:			Deactivate Debug Dash
L2:			Go Up
L1:			Go Down
R2 (Hold):		No Clip

CREDITS
-------------
Thanks to wulf2k for parts of the restoration code (which motivated me to take it further lol), 
and Meowmaritus and r3sus for providing SO much feedback
