## about
hotwheels-sdk - made for hotwheels v3 
- recode of classy's sdk in snake_case and better organization. [11/3/2021]

### dep libs
- Justas Masiulis's lazyimporter, made to hide win_api calls in dll disassembly.
- Chris Foster's tinyformat, made for easier string formatting.
- Cristei Gabriel-Marian's/Wini's mocking-bird, used for exception handling.

### notes

> if you have issues using clang-format, download `Clang Power Tools` and `Clang Format` in the VS2019 extension manager.

## general TO-DO's
###### 
**- implement all necessary interfaces into the g_interface global**
#
**- hook basic stuff that will be used in the future**
###### > fsn, do_post_screen_effects, dme, emit_sound, override_mouse, etc...
#
**- better looking/easier to use hooking system, this one is not bad but sure can be better**
#
**- start on a simple aimbot**
###### > remember to use backtrack ticks as a readable entity for aimbot, also make aimbot as optimized as possible without losing potentional since literally 0 movement hacks have a decent aimbot that doesnt kill your fps.
###### > also note that this aimbot won't be your simple little legit get hitbox and smooth your aim to head aimbot, this will use ragebot calculations such as best damage, best backtrack tick, multipoints, hitscan, mindamage, autowall blablablalbal
**- start on cheat security**
###### > note that me(dream) is not the one that messes with security. im fucking retarded i have no clue how to do shit about it
