#include <asm_setup.S>

.text
.set sp, 1
.align 4

# This patch is use r25~r27 registers. This is wakanameko's first time ASM hack.

# externs
.extern shotBombs		# 0x808a1524
.extern thisisball		# 0x808a14f0
.extern thisisbomb		# 0x808a1504

.global nolimitBombs
nolimitBombs:
	lwz r0, 0x639(r3)
	cmpwi r0, 0x1
	beq shotBombsB
	blr
shotBombsB:
	b shotBombs

.global prepareShotEverythingsASM	# replace 0x808a14ec
prepareShotEverythingsASM:
	# Check nybble 9
	lwz r0, 0x640(r31)
	cmpwi r0, 0x0
	beq thisisType1
	cmpwi r0, 0x1
	beq thisisType2
	cmpwi r0, 0x2
	beq thisisType2
	cmpwi r0, 0x3
	beq thisisType1
	cmpwi r0, 0x4
	beq thisisType2
	b thisisbomb					# b 0x808a1504 (restore instruction)  
thisisType1:
	b thisisball
thisisType2:
	b thisisbomb

.global doShotEverythingsASMType1	# replace 0x808a1214
doShotEverythingsASMType1:
	# this patch use r27 registers
	# is this patch enabled
	lwz r27, 4(r3)					# get sprite setting
	rlwinm r27, r27, 20, 24, 31		# 0000 "0"000
	cmpwi r27, 0x3
	beq continueT1
	li r3, 0x15b					# restore instruction
	b cleanupT1
continueT1:
	# get ActorID
	lwz r27, 4(r3)
	rlwinm r27, r27, 12, 20, 31		# "000"0 0000
	# set ActorID
	mr r3, r27
cleanupT1:
	li r27, 0x0
	blr

.global prepareShotEverythingsASMType2	# replace 0x808a1334
prepareShotEverythingsASMType2:
	lwz r0, 0x640(r3)
	lwz r26, 0x640(r3)				# get sprite setting nybble9
	lwz r25, 4(r3)
	blr

.global doShotEverythingsASMType2	# replace 0x808a1368
doShotEverythingsASMType2:
	# is this patch enabled
	cmpwi r26, 0x4
	beq continueT2
	li r3, 0x85						# restore instruction
	b cleanupT2
continueT2:
	# get ActorID
	rlwinm r25, r25, 12, 20, 31
	# set ActorID
	mr r3, r25
cleanupT2:
	li r25, 0x0
	li r26, 0x0
	blr
