# 45° Cannon Extensions v1.0.0 <img src="https://github.com/NSMBW-Community/Reggie-Next/blob/master/reggiedata/sprites/cannon_multi_1.png" width="32" align="center" />
*by wakanameko*
　　
　　
## Requirements
- Knowledge about how to install this kind of stuff (at least the basics)　　
- Kamek 1.2.X (changes may have to be made for Newer 1.3X)　　
　　
## Kamek　　
- Add `src/airshipCannonHax.S` in your `src` folder　　
- Add `airshipCannonHax.yaml` in your `Kamek` folder　　
- Reference the `airshipCannonHax.yaml` in your `NewerProject.yaml`　　
- Add these addresses to your kamek_bass.x(kamek_pal.x):　　
```
  shotBombs = 0x808a1524;
  thisisball = 0x808a14f0;
  thisisbomb = 0x808a1504;
```
- Compile your code  
  
  
## Reggie
- Add the content of `spritedata.xml` into your `spritedata.xml` like every other sprites (replace XXX by the sprite ID)  
- Restart reggie to apply the changes  
  
  
## Change Log
- v1.0.0
> First release!  
> Known issues:  
> Type1 is not supported the rotation.  
> Limitless Bob-Omb option is broken. I'll fix this in next version.  
  
  
*If I forgot some stuff or if you find a bug, be free to let me know*
