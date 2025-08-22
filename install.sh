#!/bin/bash
set -e # Exit immediately if a command exits with a non-zero status.

# --- Global Variables ---
RAYLIB_REPO="https://github.com/raysan5/raylib.git"
RAYLIB_DIR="raylib" # Directory name after cloning

# --- Function to check if the script is run as root ---
check_root() {
  if [ "$EUID" -ne 0 ]; then
    echo "This script must be run with sudo. Please run: sudo ./install.sh"
    exit 1
  fi
}

# --- Function to install build tools
install_build_tools() {
  echo "Installing essential build tools..."
  if command -v apt &>/dev/null; then
    sudo apt update || {
      echo "Failed to update apt. Exiting."
      exit 1
    }
    sudo apt install -y build-essential || {
      echo "Failed to install build-essential. Exiting."
      exit 1
    }
  elif command -v dnf &>/dev/null; then
    sudo dnf update -y || {
      echo "Failed to update dnf. Exiting."
      exit 1
    }
    sudo dnf group install -y "Development Tools" || {
      echo "Failed to install Development Tools. Exiting."
      exit 1
    }
  elif command -v pacman &>/dev/null; then
    sudo pacman -Syu --noconfirm || {
      echo "Failed to update pacman. Exiting."
      exit 1
    }
    sudo pacman -S --needed --noconfirm base-devel || {
      echo "Failed to install base-devel. Exiting."
      exit 1
    }
  else
    echo "Error: No supported package manager found (apt, dnf, pacman)."
    echo "Please install 'make' manually."
    exit 1
  fi
  echo "Build tools installed successfully."
}

# Function to install raylib from source
install_raylib_from_source() {
  echo "Attempting to install raylib from GitHub source..."

  # Clean up any previous partial clones
  if [ -d "$RAYLIB_DIR" ]; then
    echo "Warning: '$RAYLIB_DIR' already exists. Removing it..."
    rm -rf "$RAYLIB_DIR"
  fi

  git clone "$RAYLIB_REPO" "$RAYLIB_DIR" || {
    echo "Failed to clone raylib repository. Exiting."
    exit 1
  }
  cd "$RAYLIB_DIR/src" || {
    echo "Failed to change directory to $RAYLIB_DIR/src. Exiting."
    exit 1
  }

  echo "Compiling and installing raylib..."
  make || {
    echo "Failed to compile raylib. Exiting."
    exit 1
  }

  make install || {
    echo "Failed to install raylib. Exiting."
    exit 1
  }

  # Clean up
  cd ../.. || { echo "Failed to change directory back. Manual cleanup might be needed."; }
  echo "Removing temporary raylib repository..."
  rm -rfv "$RAYLIB_DIR"

  echo "raylib installation from source complete. You can now compile and run your game."
}

check_root

echo "Starting raylib installation script..."

INSTALL_SUCCESS=false

if command -v apt &>/dev/null; then
  echo "Found Debian-based package manager (apt)."
  sudo apt update || { echo "Failed to update apt. Skipping direct raylib install."; }
  echo "Attempting to install raylib via apt..."
  if sudo apt install -y libraylib-dev; then
    echo "raylib installed successfully via apt."
    INSTALL_SUCCESS=true
  else
    echo "Failed to install libraylib-dev via apt."
  fi
elif command -v dnf &>/dev/null; then
  echo "Found Fedora/RHEL-based package manager (dnf)."
  sudo dnf update -y || { echo "Failed to update dnf. Skipping direct raylib install."; }
  echo "Attempting to install raylib via dnf..."
  if sudo dnf install -y raylib-devel; then
    echo "raylib installed successfully via dnf."
    INSTALL_SUCCESS=true
  else
    echo "Failed to install raylib-devel via dnf."
  fi
elif command -v pacman &>/dev/null; then
  echo "Found Arch Linux-based package manager (pacman)."
  sudo pacman -Syu --noconfirm || { echo "Failed to update pacman. Skipping direct raylib install."; }
  echo "Attempting to install raylib via pacman..."
  if sudo pacman -S --needed --noconfirm raylib; then
    echo "raylib installed successfully via pacman."
    INSTALL_SUCCESS=true
  else
    echo "Failed to install raylib via pacman."
  fi
else
  echo "No supported system package manager found (apt, dnf, pacman)."
fi

# GitHub install if package manager installation failed
if [ "$INSTALL_SUCCESS" = false ]; then
  echo "Automatic installation via system package manager failed or was not possible."
  read -r -p "Do you want to install raylib from GitHub source? (Y/n): " response
  response=${response,,} # Convert to lowercase

  case "$response" in
  y | yes)
    install_build_tools # Install build tools before source compilation
    install_raylib_from_source
    ;;
  n | no)
    echo "User cancelled raylib installation."
    echo "Exiting installation."
    exit 0
    ;;
  *)
    echo "Invalid input. Please answer with 'y' or 'n'."
    exit 1
    ;;
  esac
fi

echo "All raylib installation attempts completed."
echo "Please verify your setup if you encounter compilation issues."
exit 0
