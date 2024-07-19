# Satisfactory-AB_CableChoices
The development source for the Satisfactory mod AB_CableChoices

See the [mod page](https://ficsit.app/mod/AB_CableMod) for details

# Setup
If you want to play the mod, install it via SMM.

If you want to do development work with this content first understand the structure:
* `/_promo/`
  * Promotional pictures and references for remote linking
* `/.gitignore/`
  * This will list important files that must exist but can easily be regenerated
* `/PluginFolder/`
  * The content folder that should be added to your dev build as the /mods/modref folder
  * I recommend a [symlink](https://www.howtogeek.com/16226/complete-guide-to-symbolic-links-symlinks-on-windows-or-linux/) to this folder rather than any other approach
* `/<other>/`
  * Folder for major pieces of content's sources and any related resource files

I use the following software:

* GIT-LFS
* Blender
* Affinity Designer
* Substance Painter

Given how important files are ignored you'll need to re-export fbxs from blender and tgas from substance/affinity as you change the sources, but the uassets in the content folders should already be cached and work fine.

# License
All work is free to use or redistribute for the purpose of Satisfactory modification, given proper attribution to me and identical restrictions on derivative content.

If I've abandoned this and you would like ownership, let me know. If I'm dead, go nuts.
