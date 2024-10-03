

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled_setup.c

	ifdef EZPLIT_ENABLE
		ifeq ($(strip $(EZPLIT_ENABLE)), yes)
			SRC += ./animations/ezplit.c
			OPT_DEFS += -DEZPLIT_ENABLE
    	endif
	endif
	ifndef EZPLIT_ENABLE
		SRC += ./animations/ezplit.c
		OPT_DEFS += -DEZPLIT_ENABLE
	endif

	ifdef OCEAN_DREAM_ENABLE
		ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
			SRC += ./animations/ocean_dream.c
			OPT_DEFS += -DOCEAN_DREAM_ENABLE
    	endif
	endif
	ifndef OCEAN_DREAM_ENABLE
		SRC += ./animations/ocean_dream.c
		OPT_DEFS += -DOCEAN_DREAM_ENABLE
	endif

	ifdef LUNA_ENABLE
		ifeq ($(strip $(LUNA_ENABLE)), yes)
			SRC += ./animations/luna.c
			OPT_DEFS += -DLUNA_ENABLE
		endif
	endif
	ifndef LUNA_ENABLE
		SRC += ./animations/luna.c
		OPT_DEFS += -DLUNA_ENABLE
	endif

	ifdef ARASAKA_ENABLE
		ifeq ($(strip $(ARASAKA_ENABLE)), yes)
			SRC += ./animations/arasaka.c
			OPT_DEFS += -DARASAKA_ENABLE
		endif
	endif
	ifndef ARASAKA_ENABLE
		SRC += ./animations/arasaka.c
		OPT_DEFS += -DARASAKA_ENABLE
	endif

	ifdef BONGO_ENABLE
		ifeq ($(strip $(BONGO_ENABLE)), yes)
			SRC += ./animations/bongo.c
			OPT_DEFS += -DBONGO_ENABLE
		endif
	endif
	ifndef BONGO_ENABLE
		SRC += ./animations/bongo.c
		OPT_DEFS += -DBONGO_ENABLE
	endif
endif
