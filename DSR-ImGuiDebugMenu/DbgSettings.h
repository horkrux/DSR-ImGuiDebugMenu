#pragma once

typedef struct {
	bool debugBallDisplay;
	bool debugInfoDisp;
	bool damageWpnDmy;
	bool damageAtkParamRef;
} DamageManSettings;

typedef struct {
	float windowPosX;
	float windowPosY;
	float windowSizeX;
	float windowSizeY;
	float windowScaleX;
	float windowScaleY;
	float windowColorR;
	float windowColorG;
	float windowColorB;
	float windowColorA;
	float activeWindowColorR;
	float activeWindowColorG;
	float activeWindowColorB;
	float activeWindowColorA;
	float textHighlightColorR;
	float textHighlightColorG;
	float textHighlightColorB;
	float textHighlightColorA;
} DbgMenuSettings;

typedef struct {
	bool allDrawHit;
	bool npcDispLocalCtrl;
} WorldChrManDbgSettings;