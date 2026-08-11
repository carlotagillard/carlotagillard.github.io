---
layout: default
title: Autonomous Robotics & Integrated Design Challenge
---

<style>
  .project-name { font-size: clamp(1.75rem, 4vw, 2.5rem); }
  .project-tagline { display: none; }
</style>

<img src="/images/IDC/IDC_top.png" alt="test" width="400">

**Tools:** Arduino, QTI line sensors, RFID, XBee, serial LCD

## Overview

Our three-person team built one of five autonomous robots for a multi-bot collaborative course. Each robot had to autonomously navigate a black-line track, stop at hashmarks, handle onboard sensor triggers (our group used RFID), and coordinate wirelessly via XBee to assemble and display a shared result.

The course runs along a black line marked by seven hashmarks:
- Hashmarks 1–5: The robot stops, flashes a unique onboard RGB LED color for each crossbar, and polls the RFID reader. An external LED lights up green if an RFID card is present or red if absent.
- Waiting at Hash 5: After detecting the 5th hashmark, the bot executes a programmed delay based on its preset queue order. This ensures the preceding four bots safely cross the open white space to prevent collisions.
- Crossing Open Space: Once the wait timer expires, the bot moves forward across the unguided white space. It travels straight by driving both  servos at the same speed in opposite direction until its sensors detect the 6th hash.
- Hashmark 6: Upon hitting the 6th hash, the bot performs a precise 90-degree right turn to align with the new path. The bot transitions to following a new curved black line (which contains no additional hashes) until it successfully reaches Hash 7, where the line ends.
- Hashmark 7: The robot stops for good (servos detatch) and switches from driving to communicating.

Navigating this course was exceptionally difficult due to two major hurdles:
- Precision Sensor Placement: Getting the onboard LEDs to flash correctly when identifying RFID tags required strict mechanical calibration. Because the RFID sensor has a wide detection range, positioning it too far forward caused it to trigger prematurely on the wrong or previous hashmark, requiring us to place the sensor precisely parallel to the back half of the bot.
- Wireless Collision and Timing Bottlenecks: Managing five XBee radios on a single channel created severe congestion. Because our bot finished last in the sequence, the faster leading bots would often receive all prior data, calculate the total, and trigger the final show before our messages could fully propagate—leaving us bombarded with rapid incoming data and highly susceptible to dropped packets.

## System architecture

The robot runs a deterministic Arduino state machine where every transition is triggered by sensor input rather than elapsed time, ensuring that a slow trial degrades gracefully instead of desynchronising.

<div class="figure-center">
  <figure>
    <a href="/images/IDC/IDC_StateMachine_Full.jpeg" target="_blank">
      <img src="/images/IDC/IDC_StateMachine_Partial.jpeg" alt="State machine diagram showing line following, hashmark handling, and the wireless result-sharing phase" width="700">
    </a>
    <figcaption>Simplified control flow. Click for the full state diagram.</figcaption>
  </figure>
</div>

QTI line sensors: Three sensors (left, centre, right) measured RC discharge time in microseconds (anything under 400 microseconds counted as white). We tuned this threshold directly against the lighting on our course.

State calculation: Readings were thresholded and collapsed into a single integer state:

    state = 4·(left) + 2·(centre) + 1·(right)

- State 5 (White-Black-White): Centred, drive straight.
- States 1 & 3: Drifted right, nudge left.
- States 4 & 6: Drifted left, nudge right.
- State 0 (All black): Crossbar detected.
- State 7 (All white): Line ended.

Steering: Corrections were kept intentionally small. Turn commands sat at 1475 and 1525 microseconds against a 1500-microsecond neutral, preventing oscillation across the line.

RFID: At the first five crossbars, the robot stopped, flashed a unique onboard RGB LED colour, and polled the RFID reader. A card present set 'position' to that crossbar number and blinked the external LED green; no card blinked it red—providing instant visual feedback across the room. That two-color feedback made it possible to tell from across the room whether a scan had succeeded, which mattered during testing.

Data encoding: Each tag encoded specific positional data, designed so that only one of the five crossbars held a card for any given bot.

### Wireless coordination

Each bot encodes its identity and its result into a single byte: `group × 10 + 50 + position`. The receiving bot inverts it to figure out which group sent it and what their result was.

Since five bots shared one radio channel without built-in addressing or acknowledgments, they simply rebroadcast their data once every 100 loops until everyone had the complete list. If a message dropped, it was automatically sent again a moment later, making the communication reliable without needing complex retry code.

Incoming messages filled a 5-slot list, updating the LCD screen with the running total and full array every time a new value arrived. Once all data was collected, two special reserved codes (36 and 37) triggered a synchronized music and light show.

## Testing and Results

The robot completed the course successfully: it followed the line through all seven crossbars, crossed the gap, read its RFID tag, and stopped at the finish. On a couple of trials, one of the five values still showed -1 at the end, meaning the run finished before we managed to receive that specific bot's broadcast.

That gap points at the communication layer rather than the navigation. Because there is no acknowledgement in the protocol, a bot has no way to know whether its message was heard, and a receiver has no way to request a resend. Every bot rebroadcasts on a loop, so given more time the array would likely have filled, but "given more time" is not a design. With acknowledgements, or with staggered transmit intervals so five radios stop talking over each other, those slots would have filled deterministically.

## What I would do differently

Two things stand out in the code.

The state machine handles seven of its eight possible states. State 2, black-white-black, has no case, which means the robot straddling the line with only the outer sensors on it would issue no motor command at all. It never came up on our course geometry, but an unhandled state is an unhandled state, and I would either give it a recovery behaviour or assert on it.

The five crossbar cases are near-identical copies of each other, differing only in the flash color and the position value. There is also a duplicate `else if` branch testing the same condition as the `if` above it, so it can never execute. Both would collapse into one parameterized function taking color and index, which would have made the RFID logic easier to change when we were tuning it.

## Additional Resources

<div class="button-row">
  <a href="https://drive.google.com/file/d/1LtZbab9C3GHFc-kH8qjYp9a1_5a5_3Sb/view?usp=sharing" target="_blank" class="resource-link">Challenge Completion Video</a>
  <a href="https://github.com/carlotagillard/carlotagillard.github.io/tree/main/images/IDC" target="_blank" class="resource-link">All Photos</a>
  <a href="https://github.com/carlotagillard/carlotagillard.github.io/blob/main/images/IDC/IDC_v4.0_xBee_LCD.ino" target="_blank" class="resource-link">Source Code</a>
</div>

[← Back to Home](/)
