all:
	make menu
	make games
	make mods
	make plugs

menu:
	cd menu-fn && $(MAKE)

games:
	cd client/valve && $(MAKE)
	cd server/valve && $(MAKE)
	cd client/tfc && $(MAKE)
	cd server/tfc && $(MAKE)
	cd client/rewolf && $(MAKE)
	cd server/rewolf && $(MAKE)
	cd client/gearbox && $(MAKE)
	cd server/gearbox && $(MAKE)
	#cd client/wastes && $(MAKE)
	#cd server/wastes && $(MAKE)

mods:
	cd client/cstrike && $(MAKE)
	cd server/cstrike && $(MAKE)
	cd client/scihunt && $(MAKE)
	cd server/scihunt && $(MAKE)
	cd client/poke646 && $(MAKE)
	cd server/poke646 && $(MAKE)
	cd client/hunger && $(MAKE)
	cd server/hunger && $(MAKE)

plugs:
	cd plugins && $(MAKE)
