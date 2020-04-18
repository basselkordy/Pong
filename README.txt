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

Ayman , 4 / 3

-Cleaning Main.cpp (no new functionality)
	• created a new header "menu options" that contains multiple functions handeling the switch statments of menus events
		-volChange
		-themeChange
		-pauseEvents
		-menuNav  (navigating options menu)
		-mainmenuEvents
		-menuReturn
		-nameInput
	• added new function also to menu options.h "textinit" which handels all texts initializations (the function has different overloads so pay attention to passed arguments)
	• added multiple search keywords to ease navigating the main (if they are not precise enough add more)
		-Keywords :
			• searchSound
			• searchMenus
			• searchGameComp (game components : ball ,pad ,etc..)
			• searchGameMechanics (collision , reset ,etc..)
			• searchLeaderboard
			• searchRender
-Bug fixes
	• ai_move :
		- smoothed the movement of ai controlled pad and prevented it  from unnecessary movement when already the ball in range
	• dynamic collision :
		- fixed the bug where the ball would return as a straight line when colliding with the very top or very bottom of the pad
-new
	•Powerup :
		-Prepaired for a new powerup "Reverse" that switches the input of the opponent if taken (you press up you go down)
		however the powerup is not functional yet
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

-----------------------------------------------------------------------
Badr 6/4

- modified the early VolumeChanger function
- added new function for volume input

------------------------------------------------------------------------
-Bavlly 7/4 
 
-- added mouse navigator function to navigate on menus (main menu / pause menu)
-- added text in option menu 

-------------------------------------------------------------------------
Ayman 9/4

-Added :
	-Maps :
		• mapNum controls which map is running (0 : none - 1 : two obstacles - 2 : one obstacle
		•set_Map : handles initializing of maps depending on mapNum
		•map_collision : handles collision with map components
		•Edited other functions to work with new maps
	-PowerUps :
		-"Reverse" powerUp (available at 2 players mood only) : reverses movement direction
		-Modified spawn positions depending on maps to prevent spawning on obstacles
		-Modified spawn rates 
		-Modified sizes 
	-Added slight pause (0.25 sec) on scoring and reset pads position 

-Edited :
	-RandomPos : added arguments ,changed spawn conditions of ball to prevent ball from spawning inside obstacle for map 2
	-boundcheck : added arguments for RandomPos
	- isColliding from left/right : 
		•added arguments, added an overload for general use without Dynamic Collision (to be used for obstacles)
		• Edited dynamic collision :
			-touching the ball when it's moving straight changes it's direction depending on which direction you were moving
			-Ai dynamic collision : ai eventually reflects the ball with an angle even if it hits it at the center
			-Decreased middle area for the ball to reflect straight
	-ai_move : added error to the movement of ai 
	-DrawGame , DrawPowerUps : added arguments for maps drawing


----------------------------------------------------------------------------------------------------
Bassel, 14/4
- Added a new function to BALL struct, "gain_velocity()"
	- if non of the players scored in the last 5 seconds the velocity increases 
	the proccess repeats until the added velocity reachs its maximum value (16)
	- added velocity increases as follows: (initially)0 --> 1 --> 2 --> 4 --> 8 --> 16
	- added velocity is reset to 0 when one of the players score
	- this feature is only enabled in map 0
	- can be easily enabled/disabled in Main file (search "Ball Movement")

- Modified isCollidingRight/Left slightly to handle higher velocites

- Added Classic theme

- Added a new map, map 3 (bot pads)


------------------------------------------------------------------------------------------------
Bavlly , 17/4 

-Added new texture fo menus buttons (as Rectangle shapes)

-Added path for maps (Badr's menu)... look at lines :
    - (150,334,672)--> in main menu
    - (276,377)--> menus option 
-Added texture for menu background

------------------------------------------------------------------------------------------------ 
Badr , 18/4

- added the map menu





