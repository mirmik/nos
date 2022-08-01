docker build . -t arm32v7/nos -f tools/dockerfile.arch --build-arg ARCH=arm32v7
docker build . -t arm64v8/nos -f tools/dockerfile.arch --build-arg ARCH=arm64v8
docker build . -t nos -f tools/dockerfile.host