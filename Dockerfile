FROM ubuntu AS builder
RUN apt-get update && apt-get install --yes --no-install-recommends openssh-server make cmake clang libwebsocketpp-dev libboost-dev libcurl4-openssl-dev
WORKDIR /usr/src
COPY . .
RUN cmake Server -DDEBUG_BUILD=1 -DRIVET_PRODUCTION_BUILD=1 && make -j12

FROM ubuntu
WORKDIR /usr/src/app
COPY --from=builder /usr/src/rrolf-server .
# maybe a better way? I don't want to copy every SO
COPY --from=builder /usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/
CMD ./rrolf-server
