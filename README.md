---
# Dero-Baccarat
Ui for [dReam Tables](https://dreamtables.net) Dero Baccarat Smart Contracts.
![dReamTablesFooter](https://user-images.githubusercontent.com/84689659/170848696-9e9a58bf-65cb-4a21-85d7-7f90a319142d.png)
Written in C++/Qt. Used Qt 5.12.8 to build the Ui. This app is made to play Dero Baccarat on **Dero Stargate**. 

The first dReams Tables game. This smart contract is a simple version of the casino game Baccarat. It uses a private _Dero token_ called dReams for betting. Users can trade _Dero_ for dReams, & dReams can also be converted back into _Dero_. For more info on the game mechanics read the menu when the app starts, you can also refer to the game smart contracts.

### Mainnet

- Dero Baccarat Contract: [eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88](https://explorer.dero.io/tx/eb0bfd7205a8753282ebf62a103451cdb30f161db301db742b50dc1b9f2a5c88)

- dReams Token Contract: [dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7](https://explorer.dero.io/tx/dbfa9257e8cdaeacd35797402fd44e180c4c31c085989294c542c990706973d7)

### Testnet

- Dero Baccarat Testnet Contract: [8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d](https://testnetexplorer.derohe.com/tx/8817f03755a562cc1f34c6e90389ef9cc416a32d6084c0ebb4b245bc76da5c9d)

- Chips Token Testnet Contract: [a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce](https://testnetexplorer.derohe.com/tx/a30c6602a791fae5464b974ca268e3720c2bae870d20804a8694b0f0917b8bce)

![mainScreen](https://user-images.githubusercontent.com/84689659/169942785-1b07fc8c-4ae3-465a-96d2-2d7cb2b56633.png)
### Donations
- **Dero Address**: dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn

![DeroDonations](https://user-images.githubusercontent.com/84689659/165414903-44164e7e-4277-44f8-b1fe-8d139f559db1.jpg)


## Requirements to play
To be able to play you will need to have a synced **Dero daemon** running and a registered **Dero wallet**.

For more info on how to set up Dero daemon and wallet you can refer to the Dero documentation [here](https://docs.dero.io/)

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

**App path to system**

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

---

- ### Using [Qt Creator](https://www.qt.io/)

Alternatively you can also build on any system using Qt Creator. 

- Download and install Qt for your system. 
- Download repo and click on `Dero-Baccarat.pro` to open project in Qt.
- Click configure project then click build.
