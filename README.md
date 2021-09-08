# i3-pager

A plasmoid for integrating i3 with KDE Plasma.

![image](https://user-images.githubusercontent.com/1637715/72685652-676b4e80-3aec-11ea-8173-4c20daaa584e.png)

## Installation

+ Install system dependencies libsigc++-2.0 libjsoncpp extra-cmake-modules
  +  For Debian based distros:
      ```
      sudo apt install -y libsigc++-2.0-dev libjsoncpp-dev extra-cmake-modules
      ```

+ Build and install i3-pager:

  ```bash
  git clone https://github.com/duvholt/i3-pager.git --recurse-submodules
  cd i3-pager
  cmake -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix)  -B build .
  make -C build
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
