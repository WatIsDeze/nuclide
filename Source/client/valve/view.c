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

void View_UpdateWeapon(entity vm, entity mflash)
{
	player pl = (player)pSeat->ePlayer;
	
	if (pSeat->fLastWeapon != pl.activeweapon) {
		pSeat->fLastWeapon = pl.activeweapon;
		if (pl.activeweapon) {
			Weapons_Draw();
			skel_delete( mflash.skeletonindex );
			mflash.skeletonindex = skel_create( vm.modelindex );
			pSeat->fNumBones = skel_get_numbones( mflash.skeletonindex ) + 1;
			pSeat->fEjectBone = pSeat->fNumBones + 1;
		}
	}
}
