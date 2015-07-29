# AntWorld
An Environment for several AI's, searching for food and other resources.
Nearly all the variables can be changed by the user.


Project done with Clion, written in C++

Used librarys: SFML, TinyXML2, TGUI (GUI for SFML)
(TinyXML not implemented yet)



works with CLion and any other IDEs working with CMake to build it's projects.
(you can get CLion here: https://www.jetbrains.com/clion/)



If you want to build it for yourself, you either need to redefine the 
SOURCES macro in GraphicsControl.h, main.cpp and ant.h (Please remind me 
if I have forgotten one) or copy the /resources/ folder to the given 
path (/usr/resources_coding/). Copying only works for Linux, on 
Windows you'd need to redefine it anyways.



Other Branches are usually more up-to-date, since I only merge if a 
new 'feature' or sth is finally working




(Further details are added soon)



## What I have in mind:

A GUI similar to the projects of the NetLogo library, where you can 
specify about everything, but improved direct control over the environment. 


Controllable variables:

the walls of the maze (you can remove them all or put one at every 
possible spot if you want to)

the resources (at first food only, I want to implement resources to level 
up the base or build new "Ants" later on) but not only where it is 
available, but how much at what rate is available too (except for 
some maybe ...)

if there's an AI to send out (everything higher than reactive bots) 
for special tasks or how to distribute the resources etc.

how many of them should be there and from which Base

if bases are allowed to make teams, etc.

several kinds of mazes (several maze generators and an edit mode is 
certain - two generators and the Edit mode already exist)

several kinds of AI's - from basic ants up to autonomic ones and maybe 
even more.

The best about it: you can click on any tile you want and get every 
information about that and surrounding tiles, including information 
about walls, if there is food, a scent, if there's an Ant (or more) 
on that tile too, then specific information about them is given too 
(things they are carrying, what type of AI they are, in what state
they are right now, etc. )

you can save and load your created and edited mazes, but first the 
state of everything else will not be supported.

well - at least that's the idea.


## checklist:

GUI: (parts missing: ...)

Maze - Check

changing wall states - Check

creation algorithms: Random and Perfect, as well as a reset - Check

searchAlgorithm A* - Check

showTile - Check

Ant - Check

showAnt - Check

tickSystem - in Progress (need someone else who knows more about it)

AntBase - Check

Resources - Check

Scent - not in Reactive Behaviour, but else check

Food system - Check

add saving / loading of files - starting soon



AI: (in work)

Reactive Ant-behaviour - half-finished (scent needs to be further optimized)

autonomous Ant-behaviour - in progress

half-cognitive Ant-behaviour - not yet
(the ant makes her own map of the maze, and plans as to what priority e.g. food is needed and decides to go search or go take up some or resarch the map further maybe with communication between them)

Maze from the view of the ant - not yet
(a drawn map of it and the difference to the actual one)

(map might be changing) - not yet

selectable Ant-behaviour - not yet

AntBase that signs tasks - not yet

.

.

.

so much about my ideas. Some of them might be on their way to 
realization in a different branch already, they are usually named 
after the aim for it. If you want, feel free to contribute to it, 
though I'd like to do the reactive behaviour and some critical parts 
of the autonomous behaviour myself.

.

.

.

.

.

## Sources:
Ant.png: https://www.iconfinder.com/icons/289355/animal_ant_bug_insect_icon#size=128
Home_1.png: https://www.iconfinder.com/icons/51304/black_house_home_house_icon#size=128
Home_2.png: https://www.iconfinder.com/icons/175315/home_icon#size=128
leaf.png: https://www.iconfinder.com/icons/175730/leaf_icon#size=128
Black.png: from TGUI
DejaVuSans.ttf: from TGUI
Black.conf: from TGUI

TGUI: https://tgui.eu/

