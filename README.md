# AntWorld
An Environment for several AI's, searching for food and other resources.
Nearly all the variables can be changed by the user.


Project done with Clion and Sublime Text, written in C++

Used librarys: SFML, TinyXML2, TGUI (GUI for SFML)

currently really needed:
master: SFML, TGUI
all other current branches: same as master



works with CLion and any other IDE working with CMake to build it's projects.
(you can get CLion here: https://www.jetbrains.com/clion/)





Further details are added soon



What I have in mind:

A GUI similar to the projects of the NetLogo library, where you can specify about everything, 
but improved direct control over the environment. 


Controllable variables:

the walls of the maze (you can delete them all or put one at every possible spot if you want to)

the resources (at first food only, I want to implement resources to level up the base or build new "Ants" later on)
but not only where it is available, but how much at what rate is available too (except for some maybe ...)

if there's an AI to send out (everything higher than reactive bots) for special tasks or how to contribute the resources etc.

several kinds of mazes (several maze generators and an edit mode is certain)

several kinds of AI's - from basic ants up to autonomic ones and maybe even more.

The best about it: you can click on any tile you want and get every information about that and surrounding tiles, 
including information about walls, if there is food, a scent, if there's an Ant (or more) on that tile too, 
then specific information about them is given too (things they are carrying, what type of AI they are, in what state
they are right now, etc. )

you can save and load your created and edited mazes, but first the state of everything else will not be supported.

well - at least that's the idea.


checklist:

GUI: (parts missing)
Maze - Check
changing wall states - Check
creation algorithms: Random and Perfect, as well as a reset - Check
searchAlgorithm A* - Check
showTile - Check
Ant - Check
showAnt - Check
tickSystem - in Progress (need someone else who knows more about it)
AntBase - in Progress (need to redefine it)
Resources - in Progress
Scent - yet to start

KI: (all missing)
Reactive Ant-behaviour
half-cognitive Ant-behaviour (map)
(map might be chaning)
selectable Ant-behaviour
AntBase that signs tasks




