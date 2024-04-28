# i3-pager

A plasmoid for integrating i3 with KDE Plasma.

![image](https://user-images.githubusercontent.com/1637715/72685652-676b4e80-3aec-11ea-8173-4c20daaa584e.png)

## Plasma 6

The main branch only supports Plasma 6. Checkout the [plasma5](https://github.com/duvholt/i3-pager/tree/plasma5) branch for the last working Plasma 5 code.

## Installation

+ Install system dependencies (for Debian based distros):

```sh
sudo apt install -y libsigc++-2.0-dev libjsoncpp-dev extra-cmake-modules qml-module-qt-labs-qmlmodels make cmake libkf5plasma-dev qtbase5-dev qtdeclarative5-dev
```

+ Build and install i3-pager:

  ```bash
  git clone https://github.com/duvholt/i3-pager.git --recurse-submodules
  cd i3-pager
  cmake -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) -DCMAKE_BUILD_TYPE=Release -B build
  make -j $(nproc) -C build
  sudo make -C build install
  ```

+ Add i3-pager plasmoid to either Plasma dock or Latte-dock.

## Features

+ Shows current mode
+ Shows workspaces
  + Allows filtering by the current screen
  + Show workspace icons using `Font Awesome`

## Configuration

### Multiple screens

If you have multiple screens you need to either put i3-pager on both or you need to disable `Filter workspaces by current screen` in the plasmoid setting. Otherwise you are only going to see the workspaces on the current screen.

### Workspace name and icon

i3-pager supports setting name and icon per workspace using `Font Awesome`.

```bash
# <ws number>:<ws name>:<Font Awesome unicode glyph>
set $ws1 "1:General:�~J�"
set $ws2 "2:Chat:�~B~F"
set $ws3 "3:Code:�~D�"
set $ws4 "4:Terminal:�~D| "

# Use $ws1 etc as you normally would e.g:
bindsym $mod+1 workspace number $ws1
bindsym $mod+2 workspace number $ws2
bindsym $mod+3 workspace number $ws3
bindsym $mod+4 workspace number $ws4
```

Available icons are listed [here](https://fontawesome.com/icons?d=gallery&s=solid&m=free).

Select an icon and click `Copy Unicode Glyph`.

If you can't see any icons make sure `Font Awesome` is installed as `Font Awesome 5 Free Solid`. Try running `fc-match "Font Awesome 5 Free Solid"` and see if you get a match.

You can choose to hide workspace names in the plasmoid settings.

## Development

Build with debug mode:

```bash
cmake -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix) -DCMAKE_BUILD_TYPE=Debug -B build
make -C build
sudo make -C build install
```

This will install the plasmoid globally as I'm not aware of a way to access the plasmoid C++ plugin without globally installing it. To see changes restart Plasma:

```
killall plasmashell; kstart5 plasmashell
```

### Plasmoid

The `plasmoid` folder contains the code for the widget and settings.

To quickly prototype changes use plasmoidviewer:

```bash
plasmoidviewer --applet plasmoid
```

For better logging override QT's log format:

```
QT_MESSAGE_PATTERN="[%{type}] (%{function}:%{line}) - %{message}" plasmoidviewer --applet plasmoid
```

To see changes in plasmoidviewer has to be restarted, but there is no need to run make unless there are changes in the C++ plugin.
