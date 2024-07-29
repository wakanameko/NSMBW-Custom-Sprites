#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <profile.h>
#include <wakanalib.h>
#include "smw_DragonCoins.h"

const char* smwDCarcNameList [] = {
	"smwDragoncoin",
	NULL	
};

// externs
extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);
extern "C" void GetPositionOfEntrance();

u8 collected[32];
u8 collectedCheckPoint[32];

Vec PlayerPos;

class daSMW_DragonCions_c : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;
	m3d::anmChr_c animationChr;
	nw4r::g3d::ResFile resFile;

	u64 eventFlag;
	s32 timer;
	u32 delay;

	u32 effect;
	u8 type;

	Vec playerPos;

	// Reggie
	int color;		// 6
	u8 numWorld;	// 7
	u8 numLevel;	// 8
	u8 dCoinID;		// 11

	void updateModelMatrices();
	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther);

	USING_STATES(daSMW_DragonCions_c);

	public: static dActor_c *build();
};

dActor_c *daSMW_DragonCions_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daSMW_DragonCions_c));
	return new(buffer) daSMW_DragonCions_c;
}

const SpriteData smwDCoinSpriteData = { ProfileId::smwDCoin, 8, -8, 0, 0, 0x100, 0x100, 0, 0, 0, 0, 0 };
Profile smwDCoinProfile(&daSMW_DragonCions_c::build, SpriteId::smwDCoin, &smwDCoinSpriteData, ProfileId::smwDCoin, ProfileId::smwDCoin, "smwDCoin", smwDCarcNameList, 0);


void daSMW_DragonCions_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) { 
	nw4r::snd::SoundHandle GetCoinshandle;

	this->playerPos = GetSpecificPlayerActor(0)->pos;	// get 1P(id:0)'s pos
	

	collectedDCoinID[collectionDCoin] = this->dCoinID;				// 獲得したコインのIDを配列に保存	// [0] <- dCoinID + 1
	OSReport("collected coin ID : [%d]\n", dCoinID - 1);	// 獲得したコインのID

	for (int i = 0; i < 16; i++) {
		OSReport("Now Array : [%d]\n", collectedDCoinID[i]);	// Check Array
	}

	collectionDCoin += 1;
	OSReport("collected [%d] coins\n", collectionDCoin);	// 獲得したコインの総量


	if(collectionDCoin < 5){			// I want to do 1000*2(n-1) ;;
		PlaySoundWithFunctionB4(SoundRelatedClass, &GetCoinshandle, SE_OBJ_GET_DRAGON_COIN, 1);
		if(collectionDCoin == 1){		// 1,2
			AddScore(1000 * collectionDCoin, apOther->owner->which_player);	// howmany, playerID
		}
		else if(collectionDCoin == 3){	//3
			AddScore(4000, apOther->owner->which_player);
		}
		else if(collectionDCoin == 4){	//4
			AddScore(8000, apOther->owner->which_player);
		}
	}
	else{
		PlaySoundWithFunctionB4(SoundRelatedClass, &GetCoinshandle, SE_OBJ_GET_DRAGON_COIN_COMPLETE, 1);
		// Apply lives to everyone
		oneUPPopup(this->playerPos);	// Known Issue: The 1UP popup is appear only 1P position. // 既知の問題: 1Pの座標にしか1UPが表示されない。
		for (int i = 0; i < 4; i++) {
			if (Player_Active[i]) {
				addRest(i, 1, true);
			}
		}
	}

	S16Vec nullRot = {0,0,0};
	Vec oneVec = {1.0f, 1.0f, 1.0f};
	SpawnEffect("Wm_ob_starcoinget_gl", 0, &this->pos, &nullRot, &oneVec);

	this->Delete(1);
}
void daSMW_DragonCions_c::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	playerCollision(apThis, apOther);
}

bool daSMW_DragonCions_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	playerCollision(apThis, apOther);
	return true;
}
bool daSMW_DragonCions_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat7_GroundPound(apThis, apOther);
}
bool daSMW_DragonCions_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	playerCollision(apThis, apOther);
	return true;
}
bool daSMW_DragonCions_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	playerCollision(apThis, apOther);
	return true;
}
bool daSMW_DragonCions_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) { 
	return false;
}
bool daSMW_DragonCions_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) { 
	return true;
}
bool daSMW_DragonCions_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daSMW_DragonCions_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daSMW_DragonCions_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daSMW_DragonCions_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}

int daSMW_DragonCions_c::onCreate() {
	// Reggie settings
	this->color = this->settings >> 24 & 0xF;				// 0000 0"0"00 0000 0000	// nybble 6
	this->numWorld = (this->settings >> 20 & 0xF) + 1;		// 0000 00"0"0 0000 0000	// nybble 7
	this->numLevel = (this->settings >> 16 & 0xF) + 1;		// 0000 000"0" 0000 0000	// nybble 8
	this->dCoinID = (this->settings >> 4 & 0xF) + 1;		// 0000 0000 00"0"0 0000	// nybble 11

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	char resName[16];
	sprintf(resName, "g3d/t%02d.brres", this->color);
	resName[strlen(resName)] = 0;

	resFile.data = getResource("smwDragoncoin", resName);
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("smwDragoncoin");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&bodyModel, 0);

	allocator.unlink();
	
	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;
	HitMeBaby.xDistToEdge = 8.0;
	HitMeBaby.yDistToEdge = 12.5;
	HitMeBaby.category1 = 0x5;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0x200;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->scale.x = 1.0;
	this->scale.y = 1.0;
	this->scale.z = 1.0;

	this->pos.x += 0.0;
	this->pos.z = 3000.0;
	
	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z -= 0x14000;

	this->onExecute();

	for (int i = 0; i < 16; i++) {
		if(this->dCoinID == collectedDCoinID[i]){	// dCoinID + 1
			this->Delete(1);
		}
	}
	return true;
}


int daSMW_DragonCions_c::onDelete() {
	return true;
}

int daSMW_DragonCions_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daSMW_DragonCions_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daSMW_DragonCions_c::onExecute() {
	updateModelMatrices();
	
	// this->rot.y += 0x200;
	return true;
}