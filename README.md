# rrolf
## Installation Guide: 

### This guide is for Debian only.
### Install dependencies
- the [NEWEST version of emscripten](https://emscripten.org/docs/getting_started/downloads.html)
- libwebsockets, ``apt install libwebsockets-dev``
- cmake, make, gcc/clang, npm, curl, etc. (hopefully you already have these installed)

### Build
Clone the repository, install node modules:

```sh
git clone https://github.com/PaulJohnson1/rrolf.git
cd rrolf
npm i
```

Build the client:

```sh
cd Client
mkdir build
cd build
cmake .. -DWASM_BUILD=1 -DDEBUG_BUILD=0
make -j`nproc`
cp ../../RivetStaticPage/index.html .
```

Build the server:
```sh
cd Server
mkdir build
cd build
cmake .. -DDEBUG_BUILD=0
make -j`nproc`
```

Get node packages for master server:
```sh
cd MasterServer
npm i
```
### Run

Master Server: ``node main.js`` (in rrolf/MasterServer)

Game Server instance: ``./rrolf-server`` (in rrolf/Server/build)

Host the client: Any server will do, for example ``python3 -m http.server`` (in rrolf/Client/build)

## Ideas for future forks of rrolf
- a way to prestige to get skill points that can for example double your damage
- sandbox pvp maybe similar to diep

## Unofficial rrolf fork discord servers
- to add your own, make an issue with an invite to your server and I will consider adding it
