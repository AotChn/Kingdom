# Comment to Last Committ :
    added conecpts: obstacles, paths
    Thought the obstacles are temporary added and drawn as white block.
    obstacles are intended to be unit entity OR tile entity;

# Concepts:
    Tile entity:
        var: mCost, coordinate(x,y), empty?
            empty?: is there any entity on that tile
            mCost: the movement cost to step into this tile
    Unit entity:
        var: mCost, coordinate(x,y), AP
            AP: Action point (move? attack?)
            mCost: if other friendly units want to pass through the tile of this unit standing, how much mCost will increase/decrease
    Controlable Unit (Player Units? Living Unit?) Vs Not-Controlable Unit(Obstacle? Dead Unit?)

# Objects (Classes)
    Unit
    
# Diaglogue 
    5/29/2023: 