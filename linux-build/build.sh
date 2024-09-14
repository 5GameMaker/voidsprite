set -e
cmake -G Ninja
ninja
mkdir -p dist
cp -r lib dist/
find ../freesprite \( -name "*.ico" -o -name "*.ttf" \) -exec cp {} dist/ \;
cp -r ../freesprite/assets/ dist/
cp freesprite dist/__freesprite
cp _voidsprite.sh dist/voidsprite
