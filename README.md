# gtk-3-no-portal-cheat

Make GTK 3 not use portals for dialogs.

## Preview

| before                | after               |
| --------------------- | ------------------- |
| ![before](before.png) | ![after](after.png) |


## How to compile

### Steps

0. Clone this repository:

```bash
git clone https://gitlab.gnome.org/ikem-krueger/gtk-3-no-portal-cheat
cd gtk-3-no-portal-cheat
```

1. Install [Flatpak SDK](https://flathub.org/apps/org.freedesktop.Sdk):

```bash
flatpak install org.freedesktop.Sdk
```

2. Build:

```bash
flatpak run --filesystem=$PWD --cwd=$PWD org.freedesktop.Sdk build.sh
```

This creates `gtk-3-no-portal-cheat.so`.

3. Install:

```bash
mkdir -p $HOME/.local/lib
mv gtk-3-no-portal-cheat.so $HOME/.local/lib
```

## How to use

### One-time use

```bash
flatpak run --env=LD_AUDIT=$HOME/.local/lib/gtk-3-no-portal-cheat.so org.gimp.GIMP.Nightly
```

### Enable by default

```bash
flatpak override --user --env=LD_AUDIT=$HOME/.local/lib/gtk-3-no-portal-cheat.so org.gimp.GIMP.Nightly
```

### Reset / disable

This resets all overrides for `org.gimp.GIMP.Nightly`.

```bash
flatpak override --user --reset org.gimp.GIMP.Nightly
```

For fine-grained control use [Flatseal](https://flathub.org/apps/com.github.tchx84.Flatseal).

