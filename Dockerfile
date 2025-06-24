FROM debian:stable-slim

RUN apt update && apt install -y \
    build-essential gcc make file procps bash libc6-dev && \
    rm -rf /var/lib/apt/lists/*

COPY . /rootkit-lab
WORKDIR /rootkit-lab/rootkit

RUN make

CMD LD_PRELOAD=/rootkit-lab/rootkit/rootkit.so ls /rootkit-lab 
