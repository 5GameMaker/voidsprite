set -e

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
    SOURCE=$(readlink "$SOURCE")
    [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

echo ':: building imagecdylib ::'

cd ../freesprite/imagecdylib
cargo build --release
cd "$DIR"

echo ':: building voidsprite ::'

cmake -G Ninja
ninja

echo ':: packaging ::'

mkdir -p dist/lib/

cp ../freesprite/imagecdylib/target/release/lib* dist/lib/

find ../freesprite \( -name "*.ico" -o -name "*.ttf" \) -exec cp {} dist/ \;
cp -r ../freesprite/assets/ dist/
cp freesprite dist/__freesprite
cp _voidsprite.sh dist/voidsprite

echo ':: done ::'
