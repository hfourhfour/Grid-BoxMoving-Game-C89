Title:      		Box Game
Author:     		Jet Ng
Date/LastModified:  31/05/2023
Description:       	Project for COMP1000 
                    
                    Utilises game.c, UCPLinkedList.c, and terminal.c using user provided parameters via a 
                    file with game information (map size, player, box, goal, walls) to create 
                    a game map (2D array) with a border, a player, a goal position, walls,
                    and spawn a box for the player to push into the goal to win.

                    1. See map.txt for game information format:

                        LINE 1 = MAP SIZE (e.g 20 x 30 grid)
                        FOLLOWING LINES ARE FOR THE PLAYER, GOAL AND ANY WALLS ON THE MAP
                        x x O - walls
                        x x P - player position
                        x x G - goal position
                        x x B - box position

                        Make sure coordinates for the goal, box, player or walls are within the map size parameters on line 1.

                    2. Run makefile to create executeable for box game ('make' in terminal, or 'make PULL=1' to enable PULLING the box)

                    3. Run game using './box <MAPFILENAME>' in terminal. (e.g ./box map.txt)

                    4. If pulling does not work, make a small change in code file (delete a bracket and put it back, save, then remake)

                    Takes 'w','a','s','d' as user controls to move the player position on the map
                    in terminal(P). Player then aims to push the box into the goal by moving their
                    P position in a way that pushes the box(B) towards the goal (G).

                    I've made the player (P) yellow, to have the P figure on the terminal to be more prominent
                    and visually interact more pleasantly with the box trail rather than a clear/no background.

                    The user can also choose to undo their previous move by pressing 'u', which will move the 
                    game state one user action back.

                    The box (B) will have a blue-coloured trail to show where it has been and this is also
                    reversed as part of the undo action by pressing 'u'.

                    Player can also have the ability to PULL the box, 
                    if makefile is defined with PULL=1 (make PULL=1 in terminal)

                    Game finishes when the box is moved into the goal, goal turns from red
                    to green, win message is printed to terminal and game/main ends.

