#!/bin/sh

set -e

if [ ! -f "disc/fcdemo.d81" ]; then
  mkdir -p disc
  c1541 -format fcdemo,sk d81 disc/fcdemo.d81
fi

/bin/sh tools/buildResources.sh
cat cbm/wrapper.prg bin/fcdemo.c64 > bin/fcdemo.m65

c1541 <<EOF
attach disc/fcdemo.d81
delete autoboot.c65
delete fcdemo.m65
delete basloader
write cbm/autoboot.c65
write cbm/basloader
write bin/fcdemo.m65
EOF

for filename in gamedata/*; do
  c1541 disc/fcdemo.d81 -delete $(basename $filename)
  c1541 disc/fcdemo.d81 -write $filename
done

