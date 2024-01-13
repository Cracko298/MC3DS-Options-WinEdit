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

### Release Hashes:
```
options_revert.exe    -    SHA256  -    17d0825669c08fd59201464630f55d6f43ba4c518243987a0612f30daa8e013e
options_revert.exe    -    SHA1    -    7a29bcc836e935e352a369426f18d6b4d2941886
options_revert.exe    -    MD5     -    9252dfa2db109d5db5877a91fa0ee04a

options_convert.exe   -    SHA256  -    ecc6880332dd1926d4bd1a7a6f7661a49ab79325f5b1bdc103971652d6b8ef1c
options_convert.exe   -    SHA1    -    407fcc7933eaab23ee5dc7896be0a995341652bb
options_convert.exe   -    MD5     -    f9495f28d862055144a4dbb1ecc75056
```
