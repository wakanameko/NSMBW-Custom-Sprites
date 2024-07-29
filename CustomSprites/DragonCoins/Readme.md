# DragonCoins β1.0.0 <img src="https://github.com/wakanameko/NSMBW-Custom-Sprites/blob/main/CustomSprites/DragonCoins/Reggie/sprites/smwDragoncoin_0.png" width="32" align="center" />
*by ReaZ0n23*


## Requirements
- Knowledge about how to install this kind of stuff (at least the basics)
- Kamek 1.2.X (changes may have to be made for Newer 1.3X)
- [More sprites](https://github.com/Synell/NSMBW-Custom-Sprites/releases/tag/MoreSprites) by AboodXD & Nin0


## Kamek
- Add `src/smw_DragonCoins.cpp` and `src/smw_DragonCoins.h` in your `src` folder
- Add `smw_DragonCoins.yaml` in your `Kamek` folder
- Reference the `smw_DragonCoins.yaml` in your `NewerProject.yaml`
- Add the code for the "more sprite stuff" using `smwDCoin` for the ProfileID and SpriteID
- Compile your code


## Game
- Add the arc file into the `SpriteTex` folder


## Reggie
- Add the content of `spritedata.xml` into your `spritedata.xml` like every other sprites (replace XXX by the sprite ID)
- Add the content of `sprites.py` into your `sprites.py` like every other sprites (replace XXX by the sprite ID)
	> ⚠️ and don't forget to reference the 2 new classes in the list at the end ⚠️
- Add the images in the `sprites` folder into your `sprites` folder
- Restart reggie to apply the changes


## Change Log
 - β1.0
  Known issues: Once collected, it will not respawn even if you enter other levels.


*If I forgot some stuff or if you find a bug, be free to let me know*