# Copyright (C) 2024  Paul Johnson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

ssh-keygen -A
/usr/sbin/sshd -D &
ngrok tcp 2222 --log=stderr --authtoken=2RQp4RPkxn4SVPW77mFtATPARWS_4XRt9xtwX2Gb3g6YCNUi &

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