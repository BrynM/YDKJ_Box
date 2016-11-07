# You Don't Know Jack in the Box (YDKJ_Box)

## YDKJ? WTF? BBQ?

A case/box/contraption for three game show style player button controllers to be used playing [You Don't Know Jack](https://en.wikipedia.org/wiki/You_Don%27t_Know_Jack_\(video_game_series\)) (available on [Steam](http://store.steampowered.com/sub/33692/)). This package is geared toward fun and portability. The "controllers" attach to a box containing a portable PC such as a [Zotac PI320](https://www.zotac.com/us/product/mini_pcs/pi320) with a [small bluetooth keyboard](http://www.centralcomputers.com/p-383937-comkia-mobikeys-b405-bluetooth-keyboardwith-touchpadproduct.aspx) and some circuitry based on the [Arduino Micro](https://www.arduino.cc/en/Main/ArduinoBoardMicro) used as a HID keyboard. The bluetooth keyboard is required for the bonus round questions and team names despite these additional controls.

If you want to go really crazy, consider including a [portable projector](https://rif6.com/product/cube/) in the box.

## Schematic

![Schematic](circuit_plan_schem.png?raw=true "Schematic")

Rather than try to squeeze some weird button matrix scheme for 18 buttons into 10 digital inputs, I used linear [resistor ladders](https://en.wikipedia.org/wiki/Resistor_ladder) and grouped buttons together on the Micro's analog inputs. Each group only takes up a single analog input. In a resistor ladder, the first (primary) button on the chain will win out.

Each controller is a two step ladder with the "buzzer" arcade button in the primary position. This gives each player an equal timing chance to buzz in for an answer. Since we're basically using the Micro as a proxy for keyproesses, we can fire on input changes right away. The player can only "screw" another player after buzzing in. With the buzzer being the primary, a panicky player can squeeze both buttons at once and register their buzzer.

The rest of the buttons are meant to be mounted on the main box. They are in three groups - "OnetThruFour" for making answer selections, "AB" for making game mode selections, and "Main" for invoking the game menu and making choices with it. Each group has its own resistor ladder. The only consideration given to button order among these groups was for the Main group. With that group, the `[escape]` key is the most important and thus takes the primary spot. It should be noted that the buttons in the Main group are to be mounted onto the box exterior in the reverse order of their circuit due to this consideration.

The switch and LED are for programming the Micro. It's a little bit of a pain to have it sending keystrokes to your IDE or serial monitor while testing, so the switch disables sending keystrokes. When blocking keystrokes is enabled, the LED is lit as a warning.

## Breadboard Plan

![Breadboard Plan](circuit_plan_bb.png?raw=true "Breadboard Plan")

### Controller

Each controller has two buttons - the main  player "buzzer" button (in this case using arcade buttons) and a secondary "screw" button.

#### Controller Buttons

|Controller|Key(s)|Analog Value|Use|
|----|----|----|----|
|*ContOne*|`Q`|-|Player One Main Buzzer|
|*ContOne*|`S`|-|"Screw" Button|
|*ContTwo*|`B`|-|Player Two Main Buzzer|
|*ContTwo*|`S`|-|"Screw" Button|
|*ContThree*|`P`|-|Player Three Main Buzzer|
|*ContThree*|`S`|-|"Screw" Button|

### Box

Externally, the box itself has RJ11 connectors for the controllers, HDMI and power extensions for the mini PC, and the additional gameplay buttons mounted directly to it.

#### Box Buttons

|Button Group|Key(s)|Analog Value|Use|
|----|----|----|----|
|*OnetThruFour*|-|~1024|(idle input)|
|*OnetThruFour*|`1`|~0|Primary Answer|
|*OnetThruFour*|`2`|~130|Primary Answer|
|*OnetThruFour*|`3`|~315|Primary Answer|
|*OnetThruFour*|`4`|~480|Primary Answer|
|*AB*|`A`|-|Game Mode Selector|
|*AB*|`B`|-|Game Mode Selector|
|*Main*|`[space]`|-|Used for "skip" and misc. input|
|*Main*|`N`|-|Used for menu choices|
|*Main*|`Q`|-|Used for menu choices|
|*Main*|`R`|-|Used for menu choices|
|*Main*|`S`|-|Used for menu choices|
|*Main*|`[esc]`|-|Used to pause, bring up the menu, or dismiss things|
