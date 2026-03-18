#!/usr/bin/env bash
set -euo pipefail

# build.sh [Debug|Release] [Generator] [jobs]
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PROJECT_ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
BUILD_DIR="$PROJECT_ROOT/build"
CONFIG=${1:-Debug}
GENERATOR=${2:-"MinGW Makefiles"}
JOBS=${3:-$(nproc || echo 4)}

mkdir -p "$BUILD_DIR"
cmake -S "$PROJECT_ROOT" -B "$BUILD_DIR" -G "$GENERATOR" -DCMAKE_BUILD_TYPE=$CONFIG
cmake --build "$BUILD_DIR" -- -j${JOBS}

echo "Built (${CONFIG}) -> $PROJECT_ROOT/bin/practica.exe"