#!/usr/bin/env bash
set -euo pipefail

# run.sh [args...]
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
PROJECT_ROOT=$(cd "$SCRIPT_DIR/../.." && pwd)
EXE="$PROJECT_ROOT/bin/practica.exe"
if [ ! -x "$EXE" ]; then
  echo "Executable not found: $EXE"
  exit 1
fi

"$EXE" "$@"