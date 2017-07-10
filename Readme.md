# QTStickies

A cross platform, modern take on OSX's stickies.

![Screenshot](https://www.dropbox.com/s/3r6x7qvsmszx48r/Screenshot%202017-07-10%2010.03.00.png?dl=0)

Status: Very much WIP

What works:
  * Save state between runs
  * Draggable
  * Collapsable
  * Editable
  * Resizeable
  * Yellow
  * Multiple stickies
  * Many Colors
  * Save position & size

TODO better code:
  * use QPROPERTIES rather than passing strings around for color
  * less code duplication around sql queries

TODO for parity:
  * Fonts
  * Inline images

Above and Beyond:
  * Server sync!
  * Check boxes
  * Abstracted Storage back-end

## Buidling

```
$ qmake
$ make
```

## Running

`$ open qtstickies.app`
