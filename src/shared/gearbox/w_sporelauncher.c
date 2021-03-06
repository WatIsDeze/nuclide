/*
 * Copyright (c) 2016-2020 Marco Hladik <marco@icculus.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*QUAKED weapon_sporelauncher (0 0 1) (-16 -16 0) (16 16 32)
"model" "models/w_spore_launcher.mdl"

HALF-LIFE: OPPOSING FORCE (1999) ENTITY

Sporelauncher Weapon

*/

enum
{
	SPORE_IDLE1,
	SPORE_FIDGET,
	SPORE_RELOAD1,
	SPORE_RELOAD2,
	SPORE_RELOAD3,
	SPORE_FIRE,
	SPORE_HOLSTER,
	SPORE_DRAW,
	SPORE_IDLE2
};

enum
{
	SLSTATE_IDLE,
	SLSTATE_RELOAD_START,
	SLSTATE_RELOAD,
	SLSTATE_RELOAD_END
};

#ifdef SERVER
void Sporelauncher_Fire(entity spawner, vector org, vector dir)
{
	static void Spore_Touch(void) {
		int r;
		string hitsnd;

		if (other.takedamage == DAMAGE_YES) {
			Damage_Apply(other, self.owner, 50, WEAPON_SPORELAUNCHER, DMG_GENERIC);
		} else {
			Decals_Place(self.origin, sprintf("{yblood%d", floor(random(1,7))));
		}

		r = floor(random(0,3));
		hitsnd = "weapons/spore_hit1.wav";
		switch (r) {
		case 0:
			hitsnd = "weapons/spore_hit2.wav";
			break;
		case 1:
			hitsnd = "weapons/spore_hit3.wav";
			break;
		}
		sound(self, CHAN_BODY, hitsnd, 1.0f, ATTN_NORM);
		remove(self);
	}
	
	entity blob = spawn();
	setmodel(blob, "models/spore.mdl");
	blob.owner = spawner;
	blob.velocity = dir * 2000;
	blob.movetype = MOVETYPE_BOUNCE;
	blob.solid = SOLID_BBOX;
	//bolt.flags |= FL_LAGGEDMOVE;
	blob.gravity = 0.5f;
	blob.angles = vectoangles(blob.velocity);
	blob.avelocity[2] = 10;
	blob.touch = Spore_Touch;
	setsize(blob, [0,0,0], [0,0,0]);
	setorigin(blob, org);
	
	sound(spawner, CHAN_WEAPON, "weapons/splauncher_fire.wav", 1, ATTN_NORM);
}
void Sporelauncher_AltFire(entity spawner, vector org, vector dir)
{
	static void Spore_Explode(void) {
		int r;
		string hitsnd;

		Damage_Radius(self.origin, self.owner, 100, 256, 1, WEAPON_SPORELAUNCHER);
		r = floor(random(0,3));
		hitsnd = "weapons/spore_hit1.wav";
		switch (r) {
		case 0:
			hitsnd = "weapons/spore_hit2.wav";
			break;
		case 1:
			hitsnd = "weapons/spore_hit3.wav";
			break;
		}
		sound(self, CHAN_BODY, hitsnd, 1.0f, ATTN_NORM);
		remove(self);
	}
	static void Spore_Touch(void) {
		Decals_Place(self.origin, sprintf("{yblood%d", floor(random(1,7))));
		if (other.takedamage == DAMAGE_YES) {
			Spore_Explode();
		} else if (self.think == __NULL__) {
			self.think = Spore_Explode;
			self.nextthink = time + 2.0f;
		}
		self.velocity *= 0.5f;
	}
	
	entity blob = spawn();
	setmodel(blob, "models/spore.mdl");
	blob.owner = spawner;
	blob.velocity = dir * 2000;
	blob.movetype = MOVETYPE_BOUNCE;
	blob.solid = SOLID_BBOX;
	//bolt.flags |= FL_LAGGEDMOVE;
	blob.gravity = 0.5f;
	blob.angles = vectoangles(blob.velocity);
	blob.avelocity[2] = 10;
	blob.touch = Spore_Touch;
	setsize(blob, [0,0,0], [0,0,0]);
	setorigin(blob, org);
	
	sound(spawner, CHAN_WEAPON, "weapons/splauncher_fire.wav", 1, ATTN_NORM);
}
#endif

void
w_sporelauncher_precache(void)
{
#ifdef SERVER
	precache_model("models/spore.mdl");
	precache_model("models/w_spore_launcher.mdl");
	precache_sound("weapons/splauncher_altfire.wav");
	precache_sound("weapons/splauncher_bounce.wav");
	precache_sound("weapons/splauncher_fire.wav");
	precache_sound("weapons/splauncher_impact.wav");
	precache_sound("weapons/splauncher_pet.wav");
	precache_sound("weapons/splauncher_reload.wav");
	precache_sound("weapons/spore_ammo.wav");
	precache_sound("weapons/spore_hit1.wav");
	precache_sound("weapons/spore_hit2.wav");
	precache_sound("weapons/spore_hit3.wav");
#else
	precache_model("models/v_spore_launcher.mdl");
	precache_model("models/p_spore_launcher.mdl");
#endif

}
void
w_sporelauncher_updateammo(player pl)
{
#ifdef SERVER
	Weapons_UpdateAmmo(pl, pl.sporelauncher_mag, pl.ammo_spore, -1);
#endif
}

string
w_sporelauncher_wmodel(void)
{
	return "models/w_spore_launcher.mdl";
}

string
w_sporelauncher_pmodel(void)
{
	return "models/p_spore_launcher.mdl";
}
string
w_sporelauncher_deathmsg(void)
{
	return "";
}

int
w_sporelauncher_pickup(int new, int startammo)
{
#ifdef SERVER
	player pl = (player)self;

	if (new) {
		pl.sporelauncher_mag = 5;
	} else {
		if (pl.ammo_spore < 20) {
			pl.ammo_spore = bound(0, pl.ammo_spore + 5, 20);
		} else {
			return FALSE;
		}
	}
#endif
	return TRUE;
}

void
w_sporelauncher_draw(void)
{
#ifdef CLIENT
	Weapons_SetModel("models/v_spore_launcher.mdl");
	Weapons_ViewAnimation(SPORE_DRAW);
#else
	player pl = (player)self;
	Weapons_UpdateAmmo(pl, pl.sporelauncher_mag, pl.ammo_spore, -1);
#endif
}

void
w_sporelauncher_holster(void)
{
	Weapons_ViewAnimation(SPORE_HOLSTER);
}

void
w_sporelauncher_primary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

#ifdef SERVER
	if (pl.sporelauncher_mag <= 0) {
		return;
	}

	Weapons_MakeVectors();
	Sporelauncher_Fire(self, Weapons_GetCameraPos() + (v_forward * 16), v_forward);

	pl.sporelauncher_mag--;
	Weapons_UpdateAmmo(pl, pl.sporelauncher_mag, pl.ammo_spore, -1);
#else
	if (pl.a_ammo1 <= 0) {
		return;
	}

	Weapons_ViewPunchAngle([-2,0,0]);
	Weapons_ViewAnimation(SPORE_FIRE);
#endif

	pl.w_attack_next = 0.75f;
	pl.w_idle_next = 10.0f;
}

void
w_sporelauncher_secondary(void)
{
	player pl = (player)self;

	if (pl.w_attack_next > 0.0) {
		return;
	}

#ifdef SERVER
	if (pl.sporelauncher_mag <= 0) {
		return;
	}
	
	Weapons_MakeVectors();
	Sporelauncher_AltFire(self, Weapons_GetCameraPos() + (v_forward * 16), v_forward);

	pl.sporelauncher_mag--;
	Weapons_UpdateAmmo(pl, pl.sporelauncher_mag, pl.ammo_spore, -1);
#else
	if (pl.a_ammo1 <= 0) {
		return;
	}

	Weapons_ViewPunchAngle([-2,0,0]);
	Weapons_ViewAnimation(SPORE_FIRE);
#endif

	pl.w_attack_next = 0.75f;
	pl.w_idle_next = 10.0f;
}

void w_sporelauncher_release(void)
{
	player pl = (player)self;

	if (pl.w_idle_next > 0.0) {
		return;
	}

	if (pl.a_ammo3 == SLSTATE_IDLE) {
		int r = (float)input_sequence % 3;
		switch (r) {
		case 0:
			Weapons_ViewAnimation(SPORE_IDLE1);
			pl.w_idle_next = 2.0f;
			break;
		case 1:
			Weapons_ViewAnimation(SPORE_FIDGET);
			pl.w_idle_next = 4.0f;
			break;
		case 2:
			Weapons_ViewAnimation(SPORE_IDLE2);
			pl.w_idle_next = 4.0f;
			break;
		}
	} else if (pl.a_ammo3 == SLSTATE_RELOAD_START) {
		Weapons_ViewAnimation(SPORE_RELOAD1);
		pl.a_ammo3 = SLSTATE_RELOAD;
		pl.w_idle_next = 0.65f;
	} else if (pl.a_ammo3 == SLSTATE_RELOAD) {
		Weapons_ViewAnimation(SPORE_RELOAD2);
#ifdef CLIENT
		pl.a_ammo1++;
		pl.a_ammo2--;

		if (pl.a_ammo2 <= 0 || pl.a_ammo1 >= 5) {
			pl.a_ammo3 = SLSTATE_RELOAD_END;
		}
#else
		pl.sporelauncher_mag++;
		pl.ammo_spore--;

		if (pl.ammo_spore <= 0 || pl.sporelauncher_mag >= 5) {
			pl.a_ammo3 = SLSTATE_RELOAD_END;
		}
#endif
		pl.w_idle_next = 1.0f;
	} else if (pl.a_ammo3 == SLSTATE_RELOAD_END) {
		Weapons_ViewAnimation(SPORE_RELOAD3);

		pl.a_ammo3 = SLSTATE_IDLE;
		pl.w_idle_next = 10.0f;
		pl.w_attack_next = 0.5f;
	}
}

void
w_sporelauncher_reload(void)
{
	player pl = (player)self;

#ifdef CLIENT
	if (pl.a_ammo1 >= 5) {
		return;
	}
	if (pl.a_ammo2 <= 0) { 
		return;
	}
#else
	if (pl.sporelauncher_mag >= 5) {
		return;
	}
	if (pl.ammo_spore <= 0) {
		return;
	}
#endif

	if (pl.a_ammo3 > SLSTATE_IDLE) {
		return;
	}

	pl.a_ammo3 = SLSTATE_RELOAD_START;
	pl.w_idle_next = 0.0f;
}

void
w_sporelauncher_crosshair(void)
{
#ifdef CLIENT
	vector cross_pos;
	vector aicon_pos;

	/* crosshair */
	cross_pos = g_hudmins + (g_hudres / 2) + [-12,-12];
	drawsubpic(
		cross_pos,
		[24,24],
		"sprites/ofch1.spr_0.tga",
		[24/72,24/72],
		[24/72,24/72],
		[1,1,1],
		1.0,
		DRAWFLAG_NORMAL
	);

	/* ammo counters */
	HUD_DrawAmmo1();
	HUD_DrawAmmo2();

	/* ammo icon */
	aicon_pos = g_hudmins + [g_hudres[0] - 48, g_hudres[1] - 42];
	drawsubpic(
		aicon_pos,
		[24,24],
		"sprites/640hud7.spr_0.tga",
		[200/256,48/128],
		[24/256, 24/128],
		g_hud_color,
		pSeat->m_flAmmo2Alpha,
		DRAWFLAG_ADDITIVE
	);
#endif
}

float
w_sporelauncher_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIMBOW : ANIM_AIMBOW;
}

void
w_sporelauncher_hudpic(int selected, vector pos, float a)
{
#ifdef CLIENT
	if (selected) {
		drawsubpic(
			pos,
			[170,45],
			"sprites/640hudof04.spr_0.tga",
			[0,0],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	} else {
		drawsubpic(
			pos,
			[170,45],
			"sprites/640hudof03.spr_0.tga",
			[0,0],
			[170/256,45/256],
			g_hud_color,
			a,
			DRAWFLAG_ADDITIVE
		);
	}
#endif
}

weapon_t w_sporelauncher =
{
	.name		= "sporelauncher",
	.id			= ITEM_SPORELAUNCHER,
	.slot		= 6,
	.slot_pos	= 0,
	.draw		= w_sporelauncher_draw,
	.holster	= w_sporelauncher_holster,
	.primary	= w_sporelauncher_primary,
	.secondary	= w_sporelauncher_secondary,
	.reload		= w_sporelauncher_reload,
	.release	= w_sporelauncher_release,
	.crosshair	= w_sporelauncher_crosshair,
	.precache	= w_sporelauncher_precache,
	.pickup		= w_sporelauncher_pickup,
	.updateammo	= w_sporelauncher_updateammo,
	.wmodel		= w_sporelauncher_wmodel,
	.pmodel		= w_sporelauncher_pmodel,
	.deathmsg	= w_sporelauncher_deathmsg,
	.aimanim	= w_sporelauncher_aimanim,
	.hudpic		= w_sporelauncher_hudpic
};

#ifdef SERVER
void
weapon_sporelauncher(void)
{
	Weapons_InitItem(WEAPON_SPORELAUNCHER);
}
#endif

