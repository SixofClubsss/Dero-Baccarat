---
# Dero-Baccarat
Ui for [dReam Tables](https://dreamtables.net) Dero Baccarat Smart Contracts.
![dReamTablesFooter](https://user-images.githubusercontent.com/84689659/170848696-9e9a58bf-65cb-4a21-85d7-7f90a319142d.png)
Written in C++/Qt. Used Qt 5.12.8 to build the Ui. This app is made to play Dero Baccarat on **Dero Stargate**. 

The first dReams Tables game. This smart contract is a simple version of the casino game Baccarat. It uses a private _Dero token_ called dReams for betting. Users can trade _Dero_ for dReams, & dReams can also be converted back into _Dero_. For more info on the game mechanics read the menu when the app starts, you can also refer to the game smart contracts.

### Mainnet

- Dero Baccarat Contract: [8289c6109f41cbe1f6d5f27a419db537bf3bf30a25eff285241a36e1ae3e48a4](https://explorer.dero.io/tx/8289c6109f41cbe1f6d5f27a419db537bf3bf30a25eff285241a36e1ae3e48a4)

- dReams Token Contract: [ad2e7b37c380cc1aed3a6b27224ddfc92a2d15962ca1f4d35e530dba0f9575a9](https://explorer.dero.io/tx/ad2e7b37c380cc1aed3a6b27224ddfc92a2d15962ca1f4d35e530dba0f9575a9)

### Testnet

- Dero Baccarat Testnet Contract: [8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d](https://testnetexplorer.derohe.com/tx/8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d)

- Chips Token Testnet Contract: [a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce](https://testnetexplorer.derohe.com/tx/a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce)

![v1 2 0](https://user-images.githubusercontent.com/84689659/179346268-e67dabeb-d9ac-4ca6-8244-dbfee8d38f92.png)

### Donations
- **Dero Address**: dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn

![DeroDonations](https://user-images.githubusercontent.com/84689659/165414903-44164e7e-4277-44f8-b1fe-8d139f559db1.jpg)


## Requirements to play
To be able to play you will need to have connection to a synced **Dero Node** and a registered **Dero wallet**. While you can play using a remote node, it is recommended that you run your own node.

For more info on how to set up Dero node and wallet you can refer to the Dero documentation [here](https://docs.dero.io/)

To play download the latest [release](https://github.com/SixofClubsss/Dero-Baccarat/releases) or build the app from source.
- Qt is a required dependency for the app.
  - Linux - `sudo apt install qtbase5-dev`
  - MacOs - `brew install qt@5`
  - Windows - [msys2](https://www.msys2.org/) and `pacman -S mingw-w64-x86_64-qt5-static`

## Build

- ### Linux

**Install dependencies**
```
sudo apt update
sudo apt install build-essential qt5-qmake curl libcurl4-openssl-dev
sudo apt install --no-install-recommends qtbase5-dev qttools5-dev libqt5svg5-dev
```

**Download repo & build**
```
git clone https://github.com/SixofClubsss/Dero-Baccarat.git
cd Dero-Baccarat/Mainnet-Baccarat
qmake
make
```

**Start app**
```
./Dero-Baccarat 
```
For testnet build use ```cd Dero-Baccarat/Testnet-Baccarat``` & ```./Testnet-Baccarat``` to start

---
- ### MacOs

**Install [Brew](https://brew.sh/)**
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**Install dependencies**
```
brew install qt@5
```

**Add path to system**
```
export PATH="/usr/local/opt/qt@5/bin:$PATH"
export LDFLAGS="-L/usr/local/opt/qt@5/lib"
export CPPFLAGS="-I/usr/local/opt/qt@5/include"
~/.zshrc
```

**Download repo & build**
```
git clone https://github.com/SixofClubsss/Dero-Baccarat.git
cd Dero-Baccarat/Mainnet-Baccarat
qmake
make
```

**Start app**
```
./Dero-Baccarat 
```

---

- ### Windows

**Download [msys2](https://www.msys2.org/) and [cUrl](https://curl.se/windows/)**

**Install dependencies with msys2**
```
pacman -S mingw-w64-x86_64-gcc make git mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-qt5-base mingw-w64-x86_64-qt5-tools
pacman -S mingw-w64-x86_64-qt5-static
```

**Add path to system**

In `control panel`, go to `system` then `advanced system settings`. In the advanced tab click `environment variables`, find `Path` in the system variables section and edit to add `C:\msys64\mingw64\bin`, `C:\msys64\usr\bin` and `C:\Program Files\Git\cmd` to path.

**Download repo**
```
git clone https://github.com/SixofClubsss/Dero-Baccarat.git
```

Move cUrl `lib` & `include` files to `C:\msys64\mingw64\qt5-static`

**Remove comments in .pro file for windows build**
```
CONFIG += c++11 static
LIBS += -llibcurl
```

**Build**
```
cd Dero-Baccarat/Mainnet-Baccarat
qmake
make
```

Move `curl-7.84.0_3-win64-mingw\libcurl-x64.dll` file to same folder as `Dero-FiveCardDraw.exe`

For issues with SSL remove comments from `curl_easy_setopt(curlDaemonCheck, CURLOPT_SSL_VERIFYPEER, 0);` in .cpp files.

Build preformed on Windows 10 system.

---

- ### Using [Qt Creator](https://www.qt.io/)

Alternatively you can also build on any system using Qt Creator. 

- Download and install Qt for your system. 
- Download repo and click on `Dero-Baccarat.pro` to open project in Qt.
- Click configure project then click build.

---

![baccMenu-v1 1 2](https://user-images.githubusercontent.com/84689659/177011509-c7636172-fbb6-4388-acd1-aa3ba4055ca5.png)
