#!/usr/bin/env sh

D="$(dirname "$0")"

LD_LIBRARY_PATH="$D/lib:$LD_LIBRARY_PATH" exec -a voidsprite "$D/__freesprite" $@

