# Dao Project Overview

The majority of files were given to students by the professor to provide
a common abstract interface for the Dao game.

Dao is an abstract game played on a 4x4 board. Each player has 4 pieces, 
which they take turns moving until a winning position occurs.

I have used a min/max algorithm of 6-ply depth (3 full moves for each
player) as the strategy for my game playing agent (dao_2/player1.h). The
heuristic used takes a look at all the possilbe winning positons, and 
tries to guage which player is closer to winning at each possible board
state.

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named to get the project to work on Visual Studio.
