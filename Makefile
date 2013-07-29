APP = Operators

include $(SDK_DIR)/Makefile.defs

OBJS = $(ASSETS).gen.o ./src/gpx_func.o ./src/Cubes/Result.o ./src/Cubes/Timer.o ./src/Cubes/Question.o ./src/Cubes/Operator.o ./src/Cubes/Questioner.o ./src/Cubes/QuestionList.o ./src/Modes/Normal.o ./src/Modes/Mode.o ./src/Modes/PlayGame.o
ASSETDEPS += ./assets/*.png $(ASSETS).lua

ASSETS_BUILD_PROOF := yes

include $(SDK_DIR)/Makefile.rules
