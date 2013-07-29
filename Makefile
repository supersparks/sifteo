APP = Operators

include $(SDK_DIR)/Makefile.defs

OBJS = $(ASSETS).gen.o Operator.o Questioner.o QuestionList.o Mode.o MultCompetitive.o PlayGame.o ShowStat.o Teamwork.o gpx_func.o
ASSETDEPS += *.png $(ASSETS).lua

ASSETS_BUILD_PROOF := yes

include $(SDK_DIR)/Makefile.rules
