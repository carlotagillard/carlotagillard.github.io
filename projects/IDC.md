---
layout: default
title: Autonomous Robotics & Integrated Design Challenge
---

# Autonomous Robotics & Integrated Design Challenge

**Systems Integration Engineer** · Duke University, ECE 110L · Jan 2026 to May 2026  
**Tools:** C++, Arduino, QTI line sensors, RFID, XBee, serial LCD

## Overview

A five-robot team where each bot had to navigate a course autonomously, read RFID
tags at fixed waypoints, and then coordinate wirelessly to assemble a shared
result. I owned sensor integration and the communication layer.

The course runs along a black line marked by seven crossbars. At the first five,
the robot stops and checks for an RFID card; whichever crossbar has one becomes
that bot's position value. After the sixth crossbar the line ends, and the robot
has to cross open floor on dead reckoning to reach the final segment. At the
seventh it stops for good and switches from driving to communicating.

[Two sentences on what made it hard. The dead-reckoning gap and five radios on one
channel are both worth naming. If the course had a specific turn radius or timing
budget that shaped your tuning, say so.]

## System architecture

The robot runs a C++ state machine. Every transition is triggered by sensor input
rather than elapsed time, so a slow trial degrades gracefully instead of
desynchronising.

![State machine](/images/idc/state-machine.svg)

Three QTI sensors read the surface beneath the robot. Each reading is thresholded
and collapsed to one bit, and the three bits combine into a single integer:

    state = 4·(left) + 2·(centre) + 1·(right)

Eight possible states from one line of arithmetic. State 5, white-black-white,
means centred, so drive straight. States 1 and 3 mean the robot has drifted right,
so nudge left; 4 and 6 mean the opposite. State 0, all three black, is a crossbar.
State 7, all three white, means the line has ended.

The crossbar handler branches on a running count rather than on sensor input,
because each of the seven crossbars means something different: five scan points,
one departure point, one finish.

### Sensing

**QTI line sensors.** Three sensors mounted left, centre and right. Each one is
read by charging the pin high, flipping it to input, and timing the decay in
microseconds, which is the standard RC discharge measurement. Anything under 400
microseconds counts as white. [Say whether you took 400 from the lab manual or
tuned it against the lighting on your course. If you tuned it, that is the most
interesting sentence in this section.]

Steering corrections are deliberately small: the turn commands sit at 1475 and
1525 microseconds against a 1500 microsecond neutral, so the robot converges back
onto the line rather than oscillating across it.

**RFID.** At each of the first five crossbars the robot stops, flashes a colour
unique to that crossbar on its onboard RGB LED, and polls the RFID reader. A card
present sets `position` to the current crossbar number and blinks the external LED
green; no card blinks it red. That two-colour feedback made it possible to tell
from across the room whether a scan had succeeded, which mattered during testing.

[What was actually encoded on the tags, and why only one of the five crossbars had
a card for any given bot.]

### Wireless coordination

Each bot encodes its identity and its result into a single byte: `group × 10 + 50 +
position`. The receiving bot inverts it with integer division and modulo to recover
which group sent the message and what they found.

That encoding is why the whole exchange fits in one byte per message, which matters
when five radios share a channel. There is no addressing and no acknowledgement.
Instead every bot rebroadcasts its own value roughly once every hundred passes
through the receive loop, and keeps rebroadcasting until its local `results` array
is complete. A dropped message simply gets sent again a moment later, so the
protocol converges without any retry logic.

The array starts as five values of -1. Each incoming message fills one slot, and
the LCD redraws the full array plus the running sum every time a new value arrives.
Two reserved bytes, 36 and 37, trigger a synchronised song and light show once the
whole team has finished.

## Testing and results

I validated performance across five consecutive trials, measuring timing precision
and sensor accuracy.

[The numbers. Completion rate out of five, run time and how much it varied, how
often the RFID read succeeded on the first stop, how long the array took to fill
once all bots reached the end. Even rough figures beat none.]

## What I would do differently

Two things stand out in the code.

The state machine handles seven of its eight possible states. State 2,
black-white-black, has no case, which means the robot straddling the line with only
the outer sensors on it would issue no motor command at all. It never came up on
our course geometry, but an unhandled state is an unhandled state, and I would
either give it a recovery behaviour or assert on it.

The five crossbar cases are near-identical copies of each other, differing only in
the flash colour and the position value. There is also a duplicate `else if` branch
testing the same condition as the `if` above it, so it can never execute. Both would
collapse into one parameterised function taking colour and index, which would have
made the RFID logic easier to change when we were tuning it.

[Optional third: a bug that cost you real time. The 35 second hold at crossbar 5 is
clearly a synchronisation point, so if that number was found by trial and error
rather than derived, that is a good story.]

## Additional Resources

<div class="button-row">
  <a href="[link]" target="_blank" class="resource-link">Detailed State Machine</a>
  <a href="[link]" target="_blank" class="resource-link">Challenge Completion Video</a>
  <a href="[link]" target="_blank" class="resource-link">All Photos</a>
  <a href="[link]" target="_blank" class="resource-link">Source Code</a>
</div>
