Comment to Last Committ :
    added conecpts: obstacles, paths
    Thought the obstacles are temporary added and drawn as white block.
    obstacles are intended to be unit entity OR tile entity;

Concepts:
    Tile entity:
        var: mCost, coordinate(x,y), empty?
            empty?: is there any entity on that tile
            mCost: the movement cost to step into this tile
    Unit entity:
        var: AP, mCost, coordinate(x,y)
            AP: Action point (move? attack?)
            mCost: if other friendly units want to pass through the tile of this unit standing, how much mCost will increase/decrease
