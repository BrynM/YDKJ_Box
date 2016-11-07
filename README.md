# You Don't Know Jack in the Box (YDKJ_Box)

## YDKJ? WTF? BBQ?

A case/box/contraption for three game show style player button controllers to be used playing [You Don't Know Jack](https://en.wikipedia.org/wiki/You_Don%27t_Know_Jack_\(video_game_series\)) (available on [Steam](http://store.steampowered.com/sub/33692/)). This package is geared toward fun and portability. The "controllers" attach to a box containing a portable PC such as a [Zotac PI320](https://www.zotac.com/us/product/mini_pcs/pi320) with a [small bluetooth keyboard](http://www.centralcomputers.com/p-383937-comkia-mobikeys-b405-bluetooth-keyboardwith-touchpadproduct.aspx) and some circuitry based on the [Arduino Micro](https://www.arduino.cc/en/Main/ArduinoBoardMicro) used as a HID keyboard. The bluetooth keyboard is required for the bonus round questions and team names despite these additional controls.

If you want to go really crazy, consider including a [portable projector](https://rif6.com/product/cube/) in the box.

### Controller

Each controller has two buttons - the main  player "buzzer" button (in this case using arcade buttons) and a secondary "screw" button.

#### Controller Buttons

|Controller|Key(s)|Use|
|----|----|----|
|One|Q|Player One Main Buzzer|
|One|S|"Screw" Button|
|Two|B|Player Two Main Buzzer|
|Two|S|"Screw" Button|
|Three|P|Player Three Main Buzzer|
|Three|S|"Screw" Button|

# Box

Externally, the box itself has RJ11 connectors for the controllers, HDMI and power extensions for the mini PC, and the additional gameplay buttons mounted directly to it.

#### Box Buttons

|Button Group|Key(s)|Use|
|----|----|----|
|OneThroughFour|1-4|Primary Answers|
|AB|A, B|Game Mode Selectors|
|Main|[space]|Used for "skip" and misc. input|
|Main|N, Q, R, S|Used for menu choices|
|Main|[esc]|Used to pause, bring up the menu, or dismiss things|

## Schematic

![Schematic](circuit_plan_schem.png?raw=true "Schematic")

## Breadboard Plan

![Breadboard Plan](circuit_plan_bb.png?raw=true "Breadboard Plan")
