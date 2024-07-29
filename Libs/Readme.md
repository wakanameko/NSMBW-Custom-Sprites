# wakanaLib v1.0.0
*by wakanameko*


## Requirements
- Knowledge about how to install this kind of stuff (at least the basics)
- Kamek 1.2.X (changes may have to be made for Newer 1.3X)


## Kamek
- Add `Libs/wakanalib.h` in your `include` folder
- Add these addresses to your kamek_bass.x(kamek_pal.x):
```
	addRest = 0x80060460;
	incRestAll = 0x800e20b8;
	oneUPPopup = 0x800b35b0;
	DisplayScoreAddPopup = 0x800B3540;
	AddScore = 0x80060690;
	zoneZoomFloat = 0x8042c030;
	aP_rcha_2 = 0x8098c41c;
	pakkunYoshiFumiJumpSet = 0x8002daa0;
	yoshiFumiJumpSet = 0x80096760;
```
- Let's begin writting custom codes!

