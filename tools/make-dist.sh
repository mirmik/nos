docker build . -t arm32v7/nos -f tools/dockerfile.arch --build-arg ARCH=arm32v7
docker build . -t arm64v8/nos -f tools/dockerfile.arch --build-arg ARCH=arm64v8
docker build . -t nos -f tools/dockerfile.host

mkdir -p dist
mkdir -p dist/arm32v7
mkdir -p dist/arm64v8

docker run --rm --entrypoint cat nos /root/nos/libnos.so > dist/libnos.so
docker run --rm --entrypoint cat arm32v7/nos /root/nos/libnos.so > dist/arm32v7/libnos.so
docker run --rm --entrypoint cat arm64v8/nos /root/nos/libnos.so > dist/arm64v8/libnos.so

docker run --rm --entrypoint cat nos /root/nos/libnos.a > dist/libnos.a
docker run --rm --entrypoint cat arm32v7/nos /root/nos/libnos.a > dist/arm32v7/libnos.a
docker run --rm --entrypoint cat arm64v8/nos /root/nos/libnos.a > dist/arm64v8/libnos.a