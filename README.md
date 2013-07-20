starlow - chiptune music synthesis for game developers
======

Installation
------
`make && sudo make install`

Usage
------
`starlow <input-file> <note-type>`, where `<input-file>` is a file containing a single line of lowercase letters a through g, with *one* optional space character after each letter. This will be more flexible in the future, once I get dynamic rests and multi-channel audio set up. `<note-type>` denotes the length of each note: a note type of 2 will generate audio with half second notes, and a note type of 8 will create notes an eight of a second long.

Writing Input Files
------
An input file is just a string of notes, possibly delimited with spaces. Spaces denote a half-note rest, and cannot be placed in succession at the moment (so no longer rests by chaining spaces). However, it is perfectly possible to chain notes without spaces. Want to play an A for 2 seconds, then rest, then a C for 1/2 second? Simply set `<note-type>` to 2, and provide "aaaa c" in the input file.

Output
------
It writes music to a file `out.wav` in the current directory. Currently, all of the audio is squarewave: sawtooth and triangle are coming soon, as are multiple channels, longer rests, and using `getopt` for arguments. Right now, if you need that stuff, just throw the output into Audacity. It should work fine.

License
------
See LICENSE.md
