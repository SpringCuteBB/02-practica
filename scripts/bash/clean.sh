#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PROJECT_ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)

rm -rf "$PROJECT_ROOT/build"
rm -rf "$PROJECT_ROOT/bin"
rm -rf "$PROJECT_ROOT/lib"
rm -f "$PROJECT_ROOT/CMakeCache.txt"
rm -rf "$PROJECT_ROOT/CMakeFiles"

echo "Cleaned build/, bin/, lib/ in $PROJECT_ROOT"