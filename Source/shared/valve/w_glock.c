/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

enum
{
	GLOCK_IDLE1,
	GLOCK_IDLE2,
	GLOCK_IDLE3,
	GLOCK_SHOOT,
	GLOCK_SHOOT_EMPTY,
	GLOCK_RELOAD_EMPTY,
	GLOCK_RELOAD,
	GLOCK_DRAW,
	GLOCK_HOLSTER
};

void w_glock_precache(void)
{
	precache_model("models/v_9mmhandgun.mdl");
	precache_model("models/w_9mmhandgun.mdl");
	precache_model("models/p_9mmhandgun.mdl");
	precache_sound("weapons/pl_gun3.wav");
}
string w_glock_vmodel(void)
{
	return "models/v_9mmhandgun.mdl";
}
string w_glock_wmodel(void)
{
	return "models/w_9mmhandgun.mdl";
}
string w_glock_pmodel(void)
{
	return "models/p_9mmhandgun.mdl";
}
string w_glock_deathmsg(void)
{
	return "";
}

void w_glock_pickup(void)
{
#ifdef SSQC
	player pl = (player)self;
	pl.glock_mag = bound(0, pl.glock_mag + 18, 18);
#endif
}

void w_glock_draw(void)
{
#ifdef SSQC
	player pl = (player)self;
	Weapons_ViewAnimation(GLOCK_DRAW);
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, __NULL__);
#endif
}
void w_glock_holster(void)
{
#ifdef SSQC
	Weapons_ViewAnimation(GLOCK_HOLSTER);
#endif
}
void w_glock_primary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

#ifdef CSQC
	if (!pl.a_ammo1) {
		return;
	}

	if (pl.a_ammo1) {
		Weapons_ViewAnimation(GLOCK_SHOOT);
	} else {
		Weapons_ViewAnimation(GLOCK_SHOOT_EMPTY);
	}

	Weapons_ViewPunchAngle([-2,0,0]);
#else
	if (!pl.glock_mag) {
		return;
	}

	TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, 8, [0.01,0,01]);

	pl.glock_mag--;

	Weapons_PlaySound(pl, CHAN_WEAPON, "weapons/pl_gun3.wav", 1, ATTN_NORM);
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, __NULL__);
#endif

	pl.w_attack_next = 0.3f;
	pl.w_idle_next = 5.0f;
}
void w_glock_secondary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0) {
		return;
	}

#ifdef CSQC
	if (!pl.a_ammo1) {
		return;
	}
	
	if (pl.a_ammo1) {
		Weapons_ViewAnimation(GLOCK_SHOOT);
	} else {
		Weapons_ViewAnimation(GLOCK_SHOOT_EMPTY);
	}

	Weapons_ViewPunchAngle([-2,0,0]);
#else
	if (!pl.glock_mag) {
		return;
	}

	TraceAttack_FireBullets(1, pl.origin + pl.view_ofs, 8, [0.1,0,1]);

	pl.glock_mag--;

	Weapons_PlaySound(pl, CHAN_WEAPON, "weapons/pl_gun3.wav", 1, ATTN_NORM);
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, __NULL__);
#endif

	pl.w_attack_next = 0.2f;
	pl.w_idle_next = 5.0f;
}
void w_glock_reload(void)
{
	player pl = (player)self;
	if (pl.w_attack_next > 0) {
		return;
	}
#ifdef CSQC
	if (pl.a_ammo1 >= 18) {
		return;
	}

	if (pl.a_ammo1) {
		Weapons_ViewAnimation(GLOCK_RELOAD);
	} else {
		Weapons_ViewAnimation(GLOCK_RELOAD_EMPTY);
	}
#else
	if (pl.glock_mag >= 18) {
		return;
	}
	if (!pl.ammo_9mm) {
		return;
	}

	Weapons_ReloadWeapon(pl, player::glock_mag, player::ammo_9mm, 18);
	Weapons_UpdateAmmo(pl, pl.glock_mag, pl.ammo_9mm, __NULL__);
#endif

	pl.w_attack_next = 2.0f;
	pl.w_idle_next = 10.0f;
}
void w_glock_release(void)
{
#ifdef CSQC
	player pl = (player)self;
	if (pl.w_idle_next > 0) {
		return;
	}

	int r = floor(random(0,3));
	switch (r) {
	case 0:
		Weapons_ViewAnimation(GLOCK_IDLE1);
		break;
	case 1:
		Weapons_ViewAnimation(GLOCK_IDLE2);
		break;
	case 2:
		Weapons_ViewAnimation(GLOCK_IDLE3);
		break;
	}
	pl.w_idle_next = 10.0f;
#endif
}
void w_glock_hud(void)
{
#ifdef CSQC
	static vector cross_pos;
	cross_pos = (video_res / 2) + [-12,-12];
	drawsubpic(cross_pos, [24,24], "sprites/crosshairs.spr_0.tga", [0.1875,0], [0.1875, 0.1875], [1,1,1], 1, DRAWFLAG_NORMAL);
	HUD_DrawAmmo1();
	HUD_DrawAmmo2();
#endif
}
void w_glock_hudpic(int s, vector pos)
{
#ifdef CSQC
	if (s) {
		drawsubpic(pos, [170,45], "sprites/640hud4.spr_0.tga", [0,45/256], [170/256,45/256], g_hud_color, 1, DRAWFLAG_ADDITIVE);
	} else {
		drawsubpic(pos, [170,45], "sprites/640hud1.spr_0.tga", [0,45/256], [170/256,45/256], g_hud_color, 1, DRAWFLAG_ADDITIVE);
	}
#endif
}

weapon_t w_glock =
{
	ITEM_GLOCK,
	1,
	0,
	w_glock_draw,
	w_glock_holster,
	w_glock_primary,
	w_glock_secondary,
	w_glock_reload,
	w_glock_release,
	w_glock_hud,
	w_glock_precache,
	w_glock_pickup,
	w_glock_vmodel,
	w_glock_wmodel,
	w_glock_pmodel,
	w_glock_deathmsg,
	w_glock_hudpic
};

#ifdef SSQC
void weapon_9mmhandgun(void) {
	Weapons_InitItem(WEAPON_GLOCK);
}
void weapon_glock(void) {
	Weapons_InitItem(WEAPON_GLOCK);
}
#endif