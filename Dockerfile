FROM ubuntu AS builder
RUN echo test
RUN apt-get update && apt-get install --yes make cmake clang libwebsocketpp-dev libboost-dev libcurl4-openssl-dev ca-certificates
WORKDIR /usr/src
COPY . .
RUN cmake Server -DDEBUG_BUILD=1 -DRIVET_PRODUCTION_BUILD=1 && make
FROM ubuntu
RUN apt-get update && apt-get install --yes ca-certificates
WORKDIR /usr/src/app
# COPY --from=builder /usr/src/rrolf-server .
COPY --from=builder /usr/src/ .
# maybe a better way? I don't want to copy every SO
COPY --from=builder /usr/lib/x86_64-linux-gnu/ /usr/lib/x86_64-linux-gnu/
CMD ./rrolf-server


# # a simple ssh server
# # FROM ubuntu
# RUN apt-get update
# RUN apt-get install --yes --no-install-recommends openssh-server wget unzip
# RUN mkdir /var/run/sshd
# RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
# RUN sed 's/#Port 22/Port 2222/' -i /etc/ssh/sshd_config
# RUN mkdir /root/.ssh/ && echo "ssh-rsa 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 paul@ubuntu" > /root/.ssh/authorized_keys
# # EXPOSE 2222

# # install ngrok
# RUN wget https://bin.equinox.io/c/bNyj1mQVY4c/ngrok-v3-stable-linux-amd64.zip --no-check-certificate && \
#     unzip ngrok-v3-stable-linux-amd64.zip && \
#     rm -f ngrok-v3-stable-linux-amd64.zip && \
#     chmod +x ngrok && \
#     mv ngrok /usr/local/bin

# COPY start.sh /
# CMD ["/bin/bash", "/start.sh"]

# FROM alpine:3.14
# RUN apk --no-cache add curl
# WORKDIR /app
# RUN echo 'echo "Env:"; env; echo "resolv.conf"; cat /etc/resolv.conf; READY_URL="$RIVET_MATCHMAKER_API_URL/lobbies/ready"; echo "Sending ready to $READY_URL"; curl --fail --insecure --request POST --header "Content-Type: application/json" --header "Authorization: Bearer $RIVET_TOKEN" --data "{}" "$READY_URL"; echo "Success"; echo "Waiting indefinitely"; tail -f /dev/null;' > ./run.sh
# RUN chmod +x ./run.sh
# CMD ["sh", "-ecx", "/app/run.sh"]
