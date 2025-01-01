# -----------------------------------------------------------------------------
#                                    Epidemic 2023
# -----------------------------------------------------------------------------
#
CC = gcc
INCLUDE_DIR = ./include
CPPFLAGS = -I $(INCLUDE_DIR) -D_REENTRANT
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g

# libraries to link (-lXXX ex: -lm for maths)
# Detect OS
UNAME_S := $(shell uname -s)
LDFLAGS = -lrt -lpthread

ifeq ($(UNAME_S), Darwin)
  LDFLAGS = -lpthread
endif

BUILD_DIR = .tmp
SRC_DIR = ./src
LIB_DIR = ./lib
TEST_DIR = ./tests
OUTPUT_DIR = ./out

OBJS_LIST = epidemic_sim.o citizen.o plot.o city.o
OBJS = $(addprefix $(BUILD_DIR), $(OBJS_LIST))

TARGET = timer epidemic_sim citizen_manager gtk_press_agency viewer

.PHONY: all pipeline run run_citizen clean format structure

all: structure $(TARGET)

pipeline: structure timer epidemic_sim citizen_manager

run: $(TARGET)
	$(OUTPUT_DIR)/epidemic_sim &
	$(OUTPUT_DIR)/viewer &
	$(OUTPUT_DIR)/gtk_press_agency

run_citizen:
	$(OUTPUT_DIR)/citizen_manager

# -----------------------------------------------------------------------------
#                                    Timer
# -----------------------------------------------------------------------------
#
timer: .tmp/timer/main.o .tmp/timer/timer.o
	$(CC) $^ -o $(OUTPUT_DIR)/timer $(LDFLAGS)
	chmod u+x $(OUTPUT_DIR)/$@

.tmp/timer/main.o: $(SRC_DIR)/timer/main.c $(INCLUDE_DIR)/timer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

.tmp/timer/timer.o: $(SRC_DIR)/timer/timer.c $(INCLUDE_DIR)/timer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

# ADD YOU FILES IF NECESSARY

# -----------------------------------------------------------------------------
#                                  Citizen manager
# -----------------------------------------------------------------------------
#
citizen_manager: .tmp/citizen_manager/main.o .tmp/citizen_manager/citizen_manager.o \
                 .tmp/logger.o
	$(CC) $^ -o $(OUTPUT_DIR)/$@ $(LDFLAGS)
	chmod u+x $(OUTPUT_DIR)/$@

.tmp/citizen_manager/main.o: $(SRC_DIR)/citizen_manager/main.c $(INCLUDE_DIR)/citizen_manager.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

.tmp/citizen_manager/citizen_manager.o: $(SRC_DIR)/citizen_manager/citizen_manager.c $(INCLUDE_DIR)/citizen_manager.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

# ADD YOU FILES IF NECESSARY

# -----------------------------------------------------------------------------
#                                  Press agency
# -----------------------------------------------------------------------------
#
# ------------------------------- GTK VERSION ---------------------------------
ifeq ($(UNAME_S), Darwin)
gtk_press_agency: .tmp/gtk_press_agency/main.o .tmp/gtk_press_agency/gtk_press_agency.o \
              .tmp/mq_close.o .tmp/mq_getattr.o .tmp/mq_internal_fs.o .tmp/mq_notify.o \
              .tmp/mq_open.o .tmp/mq_receive.o .tmp/mq_send.o .tmp/mq_setattr.o \
              .tmp/mq_timedreceive.o .tmp/mq_timedsend.o .tmp/mq_unlink.o \
              .tmp/channel.o .tmp/logger.o
	$(CC) $^ -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)
	chmod u+x $(OUTPUT_DIR)/$@
else
gtk_press_agency: .tmp/gtk_press_agency/main.o .tmp/gtk_press_agency/gtk_press_agency.o \
                  .tmp/logger.o .tmp/channel.o
	$(CC) $^ -o $(OUTPUT_DIR)/$@ $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)
	chmod u+x $(OUTPUT_DIR)/$@
endif

.tmp/gtk_press_agency/main.o: $(SRC_DIR)/gtk_press_agency/main.c $(INCLUDE_DIR)/gtk_press_agency.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/gtk_press_agency/gtk_press_agency.o: $(SRC_DIR)/gtk_press_agency/gtk_press_agency.c $(INCLUDE_DIR)/gtk_press_agency.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

# -----------------------------------------------------------------------------
#                                  Viewer
# -----------------------------------------------------------------------------
#
viewer: .tmp/viewer/main.o .tmp/viewer/viewer.o .tmp/patterns/facade.o .tmp/logger.o .tmp/simulation_memory.o
	$(CC) $^ -o $(OUTPUT_DIR)/viewer $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)

.tmp/viewer/main.o: $(SRC_DIR)/viewer/main.c $(INCLUDE_DIR)/viewer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $@

.tmp/viewer/viewer.o: $(SRC_DIR)/viewer/viewer.c $(INCLUDE_DIR)/viewer.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $@

.tmp/patterns/facade.o: $(SRC_DIR)/patterns/facade.c $(INCLUDE_DIR)/facade.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ADD YOU FILES IF NECESSARY

# -----------------------------------------------------------------------------
#                              Epidemic sim
# -----------------------------------------------------------------------------
#
ifeq ($(UNAME_S), Darwin)
epidemic_sim: .tmp/epidemic_sim/main.o .tmp/epidemic_sim/epidemic_sim.o \
              .tmp/logger.o .tmp/mq_close.o .tmp/mq_getattr.o .tmp/mq_internal_fs.o \
              .tmp/mq_notify.o .tmp/mq_open.o .tmp/mq_receive.o .tmp/mq_send.o \
              .tmp/mq_setattr.o .tmp/mq_timedreceive.o .tmp/mq_timedsend.o \
              .tmp/mq_unlink.o
	$(CC) $^ -o $(OUTPUT_DIR)/$@ $(LDFLAGS)
else
epidemic_sim: .tmp/epidemic_sim/main.o .tmp/epidemic_sim/epidemic_sim.o .tmp/logger.o
	$(CC) $^ -o $(OUTPUT_DIR)/$@ $(LDFLAGS)
endif

.tmp/epidemic_sim/main.o: $(SRC_DIR)/epidemic_sim/main.c $(INCLUDE_DIR)/epidemic_sim.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

.tmp/epidemic_sim/epidemic_sim.o: $(SRC_DIR)/epidemic_sim/epidemic_sim.c $(INCLUDE_DIR)/epidemic_sim.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

# -----------------------------------------------------------------------------
#                              VARIOUS FILES
# -----------------------------------------------------------------------------
#

.tmp/logger.o: $(SRC_DIR)/logger.c $(INCLUDE_DIR)/logger.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

.tmp/simulation_memory.o: $(SRC_DIR)/simulation_memory.c $(INCLUDE_DIR)/simulation_memory.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

.tmp/channel.o: $(SRC_DIR)/channel.c $(INCLUDE_DIR)/channel.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

# -----------------------------------------------------------------------------
#                              Mac OS mqueue
# -----------------------------------------------------------------------------
#
ifeq ($(UNAME_S), Darwin)
.tmp/mq_close.o: $(SRC_DIR)/mqueue/mq_close.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_getattr.o: $(SRC_DIR)/mqueue/mq_getattr.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_internal_fs.o: $(SRC_DIR)/mqueue/mq_internal_fs.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_notify.o: $(SRC_DIR)/mqueue/mq_notify.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_open.o: $(SRC_DIR)/mqueue/mq_open.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_receive.o: $(SRC_DIR)/mqueue/mq_receive.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_send.o: $(SRC_DIR)/mqueue/mq_send.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_setattr.o: $(SRC_DIR)/mqueue/mq_setattr.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_timedreceive.o: $(SRC_DIR)/mqueue/mq_timedreceive.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_timedsend.o: $(SRC_DIR)/mqueue/mq_timedsend.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
.tmp/mq_unlink.o: $(SRC_DIR)/mqueue/mq_unlink.c $(INCLUDE_DIR)/macosx/mqueue.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)
endif

# -----------------------------------------------------------------------------
#                   Slope (Plotting library on Gtk 3.0)
# -----------------------------------------------------------------------------
#
animation: .tmp/slope/animation.o .tmp/slope/chart.o .tmp/slope/drawing.o .tmp/slope/figure.o \
           .tmp/slope/item.o .tmp/slope/legend.o .tmp/slope/sampler.o .tmp/slope/scale.o \
           .tmp/slope/view.o .tmp/slope/xyaxis.o .tmp/slope/xyscale.o .tmp/slope/xyseries.o
	$(CC) $^ -o $(TEST_DIR)/out/$@ $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)

simple: .tmp/slope/simple.o .tmp/slope/chart.o .tmp/slope/drawing.o .tmp/slope/figure.o \
        .tmp/slope/item.o .tmp/slope/legend.o .tmp/slope/sampler.o .tmp/slope/scale.o \
        .tmp/slope/view.o .tmp/slope/xyaxis.o .tmp/slope/xyscale.o .tmp/slope/xyseries.o
	$(CC) $^ -o $(TEST_DIR)/out/$@ $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)

widgets: .tmp/slope/widgets.o .tmp/slope/chart.o .tmp/slope/drawing.o .tmp/slope/figure.o \
         .tmp/slope/item.o .tmp/slope/legend.o .tmp/slope/sampler.o .tmp/slope/scale.o \
         .tmp/slope/view.o .tmp/slope/xyaxis.o .tmp/slope/xyscale.o .tmp/slope/xyseries.o
	$(CC) $^ -o $(TEST_DIR)/out/$@ $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0)

.tmp/slope/animation.o: $(TEST_DIR)/slope/animation.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/simple.o: $(TEST_DIR)/slope/simple.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/widgets.o: $(TEST_DIR)/slope/widgets.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/chart.o: $(LIB_DIR)/slope/chart.c $(INCLUDE_DIR)/slope/chart.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/drawing.o: $(LIB_DIR)/slope/drawing.c $(INCLUDE_DIR)/slope/drawing.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/figure.o: $(LIB_DIR)/slope/figure.c $(INCLUDE_DIR)/slope/figure.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/item.o: $(LIB_DIR)/slope/item.c $(INCLUDE_DIR)/slope/item.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/legend.o: $(LIB_DIR)/slope/legend.c $(INCLUDE_DIR)/slope/legend.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/sampler.o: $(LIB_DIR)/slope/sampler.c $(INCLUDE_DIR)/slope/sampler.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/scale.o: $(LIB_DIR)/slope/scale.c $(INCLUDE_DIR)/slope/scale.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/view.o: $(LIB_DIR)/slope/view.c $(INCLUDE_DIR)/slope/view.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/xyaxis.o: $(LIB_DIR)/slope/xyaxis.c $(INCLUDE_DIR)/slope/xyaxis.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/xyscale.o: $(LIB_DIR)/slope/xyscale.c $(INCLUDE_DIR)/slope/xyscale.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

.tmp/slope/xyseries.o: $(LIB_DIR)/slope/xyseries.c $(INCLUDE_DIR)/slope/xyseries.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0) -c $< -o $(@)

# -----------------------------------------------------------------------------
#                                  Tests
# -----------------------------------------------------------------------------
#
ifeq ($(UNAME_S), Darwin)
test_channel: .tmp/tests/test_channel.o .tmp/channel.o .tmp/logger.o \
              .tmp/mq_close.o .tmp/mq_getattr.o .tmp/mq_internal_fs.o .tmp/mq_notify.o \
              .tmp/mq_open.o .tmp/mq_receive.o .tmp/mq_send.o .tmp/mq_setattr.o \
              .tmp/mq_timedreceive.o .tmp/mq_timedsend.o .tmp/mq_unlink.o
	$(CC) $^ -o $(TEST_DIR)/out/$@ $(LDFLAGS)
	chmod u+x $(TEST_DIR)/out/$@
else
test_channel: .tmp/tests/test_channel.o .tmp/logger.o .tmp/channel.o
	$(CC) $^ -o $(TEST_DIR)/out/$@ $(LDFLAGS)
	chmod u+x $(TEST_DIR)/out/$@
endif

.tmp/tests/test_channel.o: $(TEST_DIR)/test_channel.c $(INCLUDE_DIR)/channel.h $(INCLUDE_DIR)/minunit.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $(@)

# -----------------------------------------------------------------------------
#                                 Cleaning
# -----------------------------------------------------------------------------
#
clean:
	rm -rf out/*
	rm -rf .tmp/*.o
	rm -rf .tmp/timer/*.o
	rm -rf .tmp/viewer/*.o
	rm -rf .tmp/patterns/*.o
	rm -rf .tmp/gtk_press_agency/*.o
	rm -rf .tmp/citizen_manager/*.o
	rm -rf .tmp/epidemic_sim/*.o
	rm -rf .tmp/slope/*.o
	rm -rf .tmp/tests/*.o
	rm -rf $(TEST_DIR)/out/*
	rm -f $(TARGET)
	killall -9 epidemic_sim 2> /dev/null || :
	killall -9 citizen_manager 2> /dev/null || :
	killall -9 timer 2> /dev/null || :
	killall -9 gtk_press_agency 2> /dev/null || :
	killall -9 gnuplot_x11 2> /dev/null || :


# Format all .c and .h files using clang-format
format:
	for i in `find . -name "*.[ch]"`; do clang-format -i $$i; done

structure:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/sdl_press_agency $(BUILD_DIR)/timer $(BUILD_DIR)/gtk_press_agency $(BUILD_DIR)/citizen_manager $(BUILD_DIR)/epidemic_sim $(BUILD_DIR)/patterns $(BUILD_DIR)/viewer
	mkdir -p $(OUTPUT_DIR)
#	mkdir -p $(TEST_DIR)/out

