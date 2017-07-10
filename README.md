# SettingsParser

This is simple class for reading and writing settings in a human readable from a text file.
It allows you to read a `std::string`, `bool`, `char`, `int`, `float`, `double` and some other types from a file.
You can then access these values from within your program.
You may also change the values and write them back to the file.
The syntax is basically a `key = value` pair.

Please note that the keys have to be unique.
If the same name is used twice, the value will be overwritten with the later one.

This class can also be found at the [SFML wiki](https://github.com/LaurentGomila/SFML/wiki/Source:-Settings-Parser).

### Simple settings file
This is an example of what a settings file looks like.

```text
# if a line starts with a '#' the line is a comment and will be ignored
# blank lines will also be ignored

# the syntax is
key = value

# screen size
width = 1024
height = 768

# window title
title = sfml tutorial

# phycics constants
g = 9.81

# player initials (since the key is the same the value will be set to 'X')
player = M
player = X

# video mode
fullscreen = TRUE
```

For a simple usage example take a look at the `main.cpp` file.

### Dependencies
This class depends on nothing, but the C++ standard library.

### License
The code is released under the very permissive [zlib License](https://en.wikipedia.org/wiki/Zlib_License), which means you don't have to credit me, but of course it would be very nice.
Also I'd love to hear about your project!
