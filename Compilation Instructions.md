# Compilation  Instructions
A complete guide on how to compile the exe yourself

## Building the .exe and the .dll files
- The files in this github repo are the exact ones used to compile the final exe in the releases tab.
  - Treat the exe folder and the dll folder as two seperate projects, and compile them individually. 
- This project was compiled with CMAKE via CLion. The respective CMAKE files are included in the folders for both pieces.
- While it was written in CLion, this software uses the Visual Studio C++ compiler, which can be set in CLion assuming you have VS installed as well.
  - Compiler can be set in the Toolchains section of the CLion settings menu.
  - Compiling in release or debug mode doesn't matter too much, but I use release mode for the final product(obviously)

## Running the program as two seperate files
- If `discardItems.dll` is found in the same directory as the main exe when run, the program uses that dll instead of extracting a packed copy
- Simply place both compiled parts in the same directory, and run the exe. It'll work just fine that way.
- If you just want to compile and run the software to fix your ds2 save, you don't need to go any further. 

## Building the full release product
- Only go further on from here if you want to build a copy of the product I have in the releases section.
- The exe needs a copy of the dll packed into the `RT_RCDATA` of the exe binary.
- Use [Resource Hacker](https://www.angusj.com/resourcehacker/) to add the dll to the exe file
  - Use the `Add binary or image resource` option, and set the resource name to `DISCARDITEMS`
- Go to the Manifest section in Resource Hacker and make the following change
  - Change `<requestedExecutionLevel level='asInvoker' uiAccess='false' />`
  - To `<requestedExecutionLevel level='requireAdministrator' uiAccess='false' />`
  - Compile the script, save the completed exe file somewhere, and it should be all set.
