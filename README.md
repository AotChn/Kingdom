
# Comment to Last Committ :
    decopule things within board: cursor, terrain, unit, grids
    and create corresponding classes
    Decopuling is made in new_board instead board.h file
            
# Concepts :
    Tile entity:
        var: mCost, coordinate(x,y), empty?
            empty?: is there any entity on that tile
            mCost: the movement cost to step into this tile
    Unit entity:
        var: mCost, coordinate(x,y), AP
            AP: Action point (move? attack?)
            mCost: if other friendly units want to pass through the tile of this unit standing, how much mCost will increase/decrease
    Controlable Unit (Player Units? Living Unit?) Vs Not-Controlable Unit(Obstacle? Dead Unit?)

# Objects (Classes) :
    Unit

# Folder_Tree (src only) :
    ├─src
    │  ├─app
    │  ├─bool_source
    │  ├─data
    │  ├─graphics
    │  │  ├─board
    │  │  ├─helper
    │  │  ├─object
    │  │  │  └─unit
    │  │  └─observer
    │  ├─network
    │  └─temp
# Diaglogue :
    5/30/2023;
        added window_observer and window_subject
        change the structure of processing event in animate & board.
    5/29/2023: 
        added:
            -Unit Class
            - bool board::u[] -> Map<cord_t, Unit_t> board::unit_q
    5/28/2023:
        added conecpts: obstacles, paths
        Though the obstacles are temporary added and drawn as white block.
        obstacles are intended to be unit entity OR tile entity;