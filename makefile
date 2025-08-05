TARGET = main.out

SRCDIR = src
INCLUDEDIR = include
BUILD_DIR = build

SPLASHLIB_DIR = lib/SplashLib
SPLASHLIB_SRCDIR = $(SPLASHLIB_DIR)/src

SRC_MAIN_PROJECT = $(SRCDIR)/main.cpp \
                   $(SRCDIR)/Game.cpp \
                   $(SRCDIR)/Snake.cpp \
                   $(SRCDIR)/Food.cpp \
                   $(SRCDIR)/GameOverScreen.cpp \
                   $(SRCDIR)/Utils.cpp \
                   $(SRCDIR)/Config.cpp \
									 $(SRCDIR)/Menu.cpp    \
                   $(SRCDIR)/PausedMenu.cpp

SRC_SPLASHLIB = $(SPLASHLIB_SRCDIR)/Splash.cpp

SRC = $(SRC_MAIN_PROJECT) $(SRC_SPLASHLIB)
OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.cpp,%.o,$(notdir $(SRC))))

CXX = g++
CXXFLAGS = -Wall -std=c++17

CXXFLAGS += -I$(INCLUDEDIR)
CXXFLAGS += -I$(SPLASHLIB_DIR)/include -g

LDFLAGS = -L$(SPLASHLIB_DIR)/lib

LDFLAGS += -lSplash \
           -lraylib -lm -lpthread -ldl -lrt -lX11

FULL_LDFLAGS = $(LDFLAGS)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

VPATH = $(SRCDIR):$(SPLASHLIB_SRCDIR)

$(BUILD_DIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SPLASHLIB_SRCDIR)/%.cpp
	@echo "Compiling $< to $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)"
	$(CXX) $(OBJS) -o $(TARGET) $(FULL_LDFLAGS)

clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Clean complete."

.PHONY: all clean
