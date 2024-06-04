# ds2-inventory-cleaner
A program designed to easily and efficiently remove invalid items from your inventory in Dark Souls 2, written by Boblord. 
Provides a quick and easy fix to getting weapons with upgrade levels +11 to +15 injected in your inventory from an invader and being softlocked as a result. 

Removes all weapons that cause the game to crash when the equipment section opens. 

## Info
### Discord
If you need to contact me directly find me on discord at `@boblord.` or in [Bob's Shack](https://discord.gg/YAUChSMeRB)

## Latest Release
Executable: [v1.0](https://github.com/boblord14/Dark-Souls-2-SotFS-CT-Bob-Edition/releases/latest)
Game: App ver. 1.03 | Calibrations 2.02
Scholar of the First Sin only. Vanilla DS2 is not supported.

## How To Use:
This application is **WINDOWS ONLY**. It will **NOT** work on any linux variants/mac. Most likely not compatible with anything below Windows 10 either. 
1. Download the [latest release](https://github.com/boblord14/ds2-inventory-cleaner/releases/latest)
2. Unpack the exe to a file location of your choosing
    1. Make sure your antivirus doesn't act up. Allow the exe past your antivirus if need be
    2. See the concerns section later on if you are worried about security or don't trust the exe download
3. Run the exe and follow the instructions in the window that pops up
    1. Running as administrator is required. See the concerns sections below if you are worried about this.
4. As long as you followed the instructions in the window, any invalid items in your inventory should be removed, and the game should no longer crash when you open your inventory
5. If this did not work, an alternative solution can be found by using the [Dark Souls 2 Cheat Engine Table](https://github.com/boblord14/Dark-Souls-2-SotFS-CT-Bob-Edition/releases/latest). See that page for further information

## Concerns:
### What am I downloading?
This program is a *packed exe*. There is a second .dll file packed inside of the main .exe file that you run. On launch, this file is extracted to a temp directory for later use in the program. 
The exe then proceedes to inject this dll into the DarkSoulsII.exe process, giving the code in the .dll file easy access to the memory of DS2, which then does the item discard work. 

### What about softbans?
No, this program does *not* get you softbanned ingame from the online servers. You do not need to run DS2 offline, the anticheat doesn't check much, certainly not the pieces used by this software. 

### Why does this need to run as administrator?
Administrator permissions mitigate the possibility for errors in the file extraction/access and the dll injection/loading in the ds2 exe. Realistically the program should be able to run without, but to I'd rather remove the possibility of a potential error in return for just granting admin access. 

### Is this safe?
As mentioned before, this program might trip antiviruses. Similar to Cheat Engine, this program performs a fair bit of memory editing on the Dark Souls II exe. A number of antiviruses don't like this, as it is a common technique used by numerous malicious programs. The dll injection and extraction of a packed file additionally don't do this program any favors in the eyes of antivirus software. Regardless of what any antiviruses may say, this is a safe piece of software. I'm not stupid enough to burn my credibility by publishing a virus on github. 

### How do I know that you're not lying to me?
The source code for both the exe and the dll are public in this github repository. If you're sufficiently savvy with C++, you can clearly tell that they don't do anything malicious. 

### What if I still don't trust you?
You are more than welcome to compile the code yourself. For transparency and ease of access, a complete tutorial on how to do so can be found [here](https://github.com/boblord14/ds2-inventory-cleaner/blob/4a347fabe5f775fd6abdeda0ae61637cf8d97550/Compilation%20Instructions.md).




  
   
