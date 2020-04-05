Bassel, 22 / 3

- added forest theme sound effects
- fixed bugs with background sounds and theme music
- modified setTheme function to load each theme's sound effects
- blocked the user from pressing return during Getplayername (bad stuff happens)
- fixed a bug where if a pad dissapeared and the user returns
to the main menu and plays again the pad will remain dissapeared
- same thing with slow, the pad's rect fill color will remain red

-----------------------------------------------------------------------

Bassel, 26 / 3
(none of the follwing adds any new functionalty)
- added clock and sound to pUp struct 
- added 3 booleans to PAD struct, isFrozen, isSlow, isInvis
- modified Get_Movement function to handle pad movement when the pad is slowed or frozen 
- added Get_Movement function to PAD struct 
- added Boundcheck function to PAD struct
- created a new function inside the PAD struct, "ResetPad", resests all pad attributes 
- created a new function, "DrawGame", handles drawing pads, ball, and background

- created a new headerfile, "powerups.h", should contain any powerup related functionalty
    - moved elongate function to powerups.h
    - created a new function, "initialize_powerups", sets textures, radii, and sounds to powerups
    - created a new function, "DrawPowerups", handles drawing powerups
    - created a new function, "isTakenPowerup", activates powerups if they're took
    - created a new function, "SpawnPowerups", handles spawing powerups
    - created a new function, "DeactivatePowerups", handles powerup deactivation

-----------------------------------------------------------------------
Badr 4/4

- added the new option menu
- made all the needed functions in one header file
-----------------------------------------------------------------------
Perry 5/4

- added character limit to username
- added getPlayerName to both users in two player mode
- prohibted the user from adding spaces into their name
- added two booleans to check whether the user is saving name 1 or name 2 (savePlayer1, savePlayer2)
- created a new function, "addToLog" in log.h which takes two inputs as follows: addToLog(Name of winner, name of loser)
