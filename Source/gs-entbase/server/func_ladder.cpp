/*
 * Copyright (c) 2016-2019 Marco Hladik <marco@icculus.org>
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

string g_laddersnd[] = {
	"player/pl_ladder1.wav",
	"player/pl_ladder2.wav",
	"player/pl_ladder3.wav",
	"player/pl_ladder4.wav"
};

class func_ladder:CBaseEntity
{
	void() func_ladder;
#ifdef CSQC
	virtual void() Initialized;
#endif
};

void func_ladder :: func_ladder ( void )
{
#ifdef SSQC
	setmodel( this, model );
	movetype = MOVETYPE_NONE;
	skin = CONTENT_LADDER;
	solid = SOLID_BSP;

	#ifdef GS_DEVELOPER
		alpha = 0.5f;
		effects = EF_FLAG2;
	#else
		alpha = 0.0001f;
		//effects = EF_NODRAW;
	#endif
#else
	Init();
#endif
}

void func_ladder :: Initialized (void)
{
	setmodel( this, model );
	movetype = MOVETYPE_NONE;
	skin = CONTENT_LADDER;
	solid = SOLID_BSP;
}
