# Questions and answers



Questions | Answers
-----|-----
Can I use less to see the highlighted output | In Windows the answer is "no", as Windows does not support ANSI by default, so Kitty uses Windows' internal system for that which Less (if you have it install in Windows) doesn't pick up. On Linux, it's a different story, as most Linux distros have ANSI by default, however LESS won't accept ANSI by default, but by adding the -r switch it will, so that will be "kitty source.c | less -r", and things should work.
Can I view multiple files with Kitty in once? | Yes, just add multiple files as parameters.
Does Kitty support wildcards? | No, which may be bothersome in Windows. On Linux it doesn't need to support it, as Linux will parse the wildcards and give it through Kitty accordingly. If you compile Kitty for Mac (or any other Unix based system) it will likely be the same story as for Linux.
My favorite language is not yet supported by Kitty. Are you willing to add it? | The more the merrier, actually. But you cannot expect me to know all the languages in the world. For most languages all I will need to know is whether the language cares about upper and lower case (C, C++ and C# do, but BASIC and Pascal do not), and what keywords there are. When it comes to "esolangs" where a completely different approach is required, I may most often have to pass. I added Brainfuck and Whitespace since they were easy to implement, but I cannot make any promises about other esotoric languages.
