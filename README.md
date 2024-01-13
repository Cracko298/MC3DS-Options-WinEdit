# MC3DS-Options-WinEdit
- **Enables editing of "options.txt" from MC3DS using the Built-in Windows Notepad Application.**
- **Basically works with any Text Editor that treats `NULL` bytes as Spacing(s), like Notepad.**

## Download(s)
- **Download the Converter [Here](https://github.com/Cracko298/MC3DS-Options-WinEdit/releases/download/v1.1.0/options_converter.exe).**
- **Do you need a Python Version? I did that as well [Here](https://github.com/Cracko298/MC3DS-Options-WinEdit/releases/download/v1.1.0/options_converter.py).**
- **Want to convert it back to that Notepad Format? Sure I have you covered [Here](https://github.com/Cracko298/MC3DS-Options-WinEdit/releases/download/v1.1.0/options_revert.exe).**

## Building:
```
g++ -o options_converter.exe -O3 -s options_converter.cpp
g++ -o options_revert.exe -O3 -s options_revert.cpp
```

## Usage:
![](https://github.com/Cracko298/MC3DS-Options-WinEdit/releases/download/v1.0.0/showoff.gif)
### CLI Example:
- All scripts take the input file path as the 1st argument and if it wasn't specified, it defaults to `options.txt`.

### Example(s):
**Defualt Command Usage:**
```
options_convert my_cool_options.txt
```
**For Legacy Consoles:**
```
.\options_convert.exe my_cool_options.txt
```
