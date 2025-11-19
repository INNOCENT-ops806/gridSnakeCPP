TARGET = main.out

SRCDIR = src
INCLUDEDIR = include
BUILD_DIR = build

SPLASHLIB_DIR = lib

SRC_MAIN_PROJECT = $(SRCDIR)/main.cpp \
                   $(SRCDIR)/Game.cpp \
                   $(SRCDIR)/Snake.cpp \
                   $(SRCDIR)/Food.cpp \
                   $(SRCDIR)/GameOverScreen.cpp \
                   $(SRCDIR)/Utils.cpp \
                   $(SRCDIR)/Config.cpp \
									 $(SRCDIR)/Menu.cpp    \
                   $(SRCDIR)/PausedMenu.cpp


SRC = $(SRC_MAIN_PROJECT)
OBJS = $(addprefix $(BUILD_DIR)/, $(patsubst %.cpp,%.o,$(notdir $(SRC))))

CXX = g++
CXXFLAGS = -Wall -std=c++17

CXXFLAGS += -I$(INCLUDEDIR) -g

LDFLAGS = -L$(SPLASHLIB_DIR)

LDFLAGS += -lSplash \
           -lraylib -lm -lpthread -ldl -lrt -lX11

FULL_LDFLAGS = $(LDFLAGS)

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

VPATH = $(SRCDIR)

$(BUILD_DIR)/%.o: $(SRCDIR)/%.cpp
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
