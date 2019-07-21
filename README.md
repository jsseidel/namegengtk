# namegen
namegen is a GTK+3.0 C application that generates fictitious names for characters or passwords.

## Features
1. male and female names
1. first and surname obscurity settings
1. name database from public US Census data

## Install

### Snap

The easiest and best way to install Namegen on Ubuntu systems is via snap:

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-white.svg)](https://snapcraft.io/namegen)

```bash
sudo snap install namegen
```

### PPA

```bash
sudo add-apt-repository ppa:jsseidel/namegen
sudo apt update
sudo apt install namegen
```

### Deb

[releases page](https://github.com/jsseidel/namegengtk/releases):

```bash
sudo apt install -y ./namegen_1.0.0_amd64.deb
```

## Uninstall

```bash
sudo apt remove --purge namegen
```

## Hack

On Ubuntu systems, to hack and compile Namegen, please install Build
Essentials, the GTK 3 development libraries, and Glade, the GTK interface
builder:

```bash
sudo apt install -y build-essential libgtk-3-dev libglib2.0-dev glade
```

Then:

```bash
git clone https://github.com/jsseidel/namegengtk
```

`make` will build the Namegen binary.

Use `./install_files/usr/share/applications/namegen.desktop` to install with an
icon wherever you see fit. Pretty icons are in
`./install_files/usr/share/icons/hicolor/*/namegen.png`.

