/usr/sbin/sshd -D &
ngrok tcp 2222 --log=stderr --authtoken=2P6z4ftpCttI88S9CjsbAPYEOyW_5dLGM5fGnKRDMM4hN54zC &

echo $RIVET_LOBBY_TOKEN > /RIVET_LOBBY_TOKEN

# pause
touch a
tail -f a

# export RIVET_LOBBY_TOKEN=`cat /RIVET_LOBBY_TOKEN`
# apt install libcurl4-openssl-dev git clang-13 libwebsocketpp-dev libboost-dev cmake make gdb --yes --no-install-recommends
# ln -s /usr/bin/clang++-13 /usr/bin/clang++
# ln -s /usr/bin/clang-13 /usr/bin/clang
# git clone https://github.com/PaulJohnson1/rrolf
# cd rrolf/Server
# git switch rivet
# mkdir build && cd build
# cmake -DDEBUG_BUILD=1 -DRIVET_PRODUCTION_BUILD=1 ..
# time make -j8
# ./rrolf-server