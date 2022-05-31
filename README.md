# Configuration files for Suckless' softwares

I enjoyed the privilege of being a unix noob and made a lot of mistakes when
managing my custom Suckless configuration. These mistakes led me to a conclusion that I
need a repository to *solely* store my config files, so here we are. In this
repository, I tracked the changes in my configuration. My main focus is to make
a minimally configured build that I can replicate in any machine. The fonts I'm
using are `Inconsolata` and `FontAwesome`.

# Suckless patches

## Dynamic Window Manager (`dwm`)

I'm buying the ideas of having a custom layout in each tag, thus `pertag` *was*
a no brainer option for me. However, after further reading, the idea behind
`flextile` becomes more lucrative. [This patch](https://dwm.suckless.org/patches/flextile/)
allows me to have a totally flexible tiling layout I could configure. This
patch modifies the default behaviour in `dwm.c` (of course), `config.def.h`
(which I adjusted to `config.h`), and create a new file `flextile.h`. By
default, I'm using `Mod4Mask` (the window key) as a modifier key, but to manage
window I'm using `Mod1Mask` (the alt key).

## Suckless Terminal (`st`)

I find aesthetically-looking terminal rather appealing, so I'm not too keen on
seeing a useless gap produced by `st` as a default behaviour when it's tiled in
`dwm`. Worry not, there comes `anysize.diff` to the rescue, because this patch
allows me to have the full functionality of my screen real estate without any
useless gap. To my regret though, the current patch still seems to leave some
gaps on the bottom of the screen (*sigh heavily*). As I don't have the luxury
of fluent comprehension of `C` source code, I might need to learn a new thing
or two before start breaking down the code.
