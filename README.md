# i3-pager
Plasmoid pager for integrating i3 with KDE Plasma.

![image](https://user-images.githubusercontent.com/1637715/72685652-676b4e80-3aec-11ea-8173-4c20daaa584e.png)


## Installation

Make sure extra-cmake-modules is installed.

Build and install i3-pager:
```bash
cmake -DCMAKE_INSTALL_PREFIX=$(kf5-config --prefix)  -B build .
make -C build
sudo make -C build install
```

Add i3-pager plasmoid to either Plasma dock or Latte-dock.

## Workspace name and icon

i3-pager supports setting name and icon per workspace using Font Awesome.

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

Available icons are listed here:
https://fontawesome.com/icons?d=gallery&s=solid&m=free

Select an icon and click "Copy Unicode Glyph".

If you can't see any icons make sure Font Awesome is installed as "Font Awesome 5 Free Solid". Try running `fc-match "Font Awesome 5 Free Solid"` and see if you get a match.

You can choose to hide workspace names in the plasmoid settings.

## Multiple monitors

If you use multiple monitors you need to add the plasmoid to each monitor as the plasmoid only shows workspaces for the monitor it is active on. This is a personal preference and I'm open to adding an option to show all workspaces regardless of monitor.
