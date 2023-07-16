FROM alpine AS builder
RUN apk update && apk add --no-cache llvm-dev make cmake clang libwebsockets-dev curl-dev musl-dev
WORKDIR /usr/src
COPY . .
RUN cmake Server -DDEBUG_BUILD=0 -DRIVET_BUILD=1 && make -j2
# RUN cmake Server -DDEBUG_BUILD=1 -DRIVET_BUILD=1 -DCMAKE_C_FLAGS="-DPROTO_BUG_NDEBUG" && make -j2

FROM alpine
RUN apk update && apk add --no-cache ca-certificates curl-dev libwebsockets && apk cache clean
WORKDIR /usr/src/app
COPY --from=builder /usr/src/rrolf-server .
CMD ./rrolf-server

# # small ssh server
# FROM alpine
# RUN apk update && \
#     apk upgrade && \
#     apk add --no-cache openssh-server wget unzip && \
#     mkdir /var/run/sshd && \
#     sed 's/#Port 22/Port 2222/' -i /etc/ssh/sshd_config

# COPY --from=builder /usr/src/ /usr/src

# # install ngrok
# RUN wget https://bin.equinox.io/c/bNyj1mQVY4c/ngrok-v3-stable-linux-amd64.zip --no-check-certificate && \
#     unzip ngrok-v3-stable-linux-amd64.zip && \
#     rm -f ngrok-v3-stable-linux-amd64.zip && \
#     chmod +x ngrok && \
#     mv ngrok /usr/local/bin

# RUN mkdir /root/.ssh/ && echo "ssh-rsa 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 paul@ubuntu" > /root/.ssh/authorized_keys

# COPY start.sh /
# CMD sh start.sh
