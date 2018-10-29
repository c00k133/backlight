# brightness

This is a small C program to change the brightness on my laptop (HP EliteBook 
820 G1).

It changes the brightness by modifying the `brightness` file under 
`/sys/class/backlight/intel_backlight/`, so if you are using anything else this 
will probably not work for you.

Before I used a bash script for changing the brightness - can be found under 
the folder `script/` - however I could not set the SUID bit with `root` as 
owner as this is prohibited for shebang (`#!`) scripts under Ubuntu. This 
program circumvents that restriction.

Just run `make install` to:
- compile the program
- change the owner to `root`
- change the permission accordingly  - 4754
- move the new file to `/usr/bin/bright`
    - if the file already exists, it will not be overwritten, the program will 
      simply compile and nothing else - equivalent to simply running `make`.

**DISCLAIMER**: I did not write the bash script myself, however, I cannot remember 
from where I got it from. I am keeping it for reference.
