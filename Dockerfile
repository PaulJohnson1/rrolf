FROM ubuntu AS builder
RUN apt-get update && apt-get install --yes --no-install-recommends make cmake clang libwebsocketpp-dev libboost-dev
WORKDIR /usr/src
COPY . .
RUN cmake Server -DRIVET_BUILD=1 && make -j12

FROM alpine
WORKDIR /usr/src/app
COPY --from=builder /usr/src/rrolf-server .
CMD ["./rrolf-server"]