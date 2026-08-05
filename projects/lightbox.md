---
layout: default
title: Integrated Embedded System
---

<style>
  .project-name { font-size: clamp(1.75rem, 4vw, 2.5rem); }
  .project-tagline { display: none; }
</style>

**Tools:** C++, PlatformIO, Arduino Nano Every, KiCad, OnShape, 3D printing, Python

<div class="figure-center">
  <figure>
    <img src="/images/lightbox/OutsideOn.png" alt="The finished enclosure with all three LEDs lit" width="600">
    <figcaption>The finished device: three LEDs under independent firmware control, with the heartbeat holding 1 Hz to within 0.5% while they run.</figcaption>
  </figure>
</div>

## Overview

A self-contained battery-powered device: a 3D-printed figure whose two eye LEDs and one logo LED are driven by firmware on an Arduino Nano Every, mounted on a PCB I designed and laid out myself, with panel-mounted controls for brightness and blink rate.

The interesting part is that it's three disciplines in one object. The enclosure has to hold the board and a 9 V battery securely while staying under 15 cm. The board has to route single-sided traces to five off-board connectors. The firmware has to run a state machine driving three outputs at three different rates simultaneously. Any one of them being wrong makes the whole thing fail.

The hardest part was not designing any single piece, it was debugging the assembled system. For several days I could get one or two LEDs working but never all three, and the failure moved depending on what I changed.

The first cause was in the firmware: I had misassigned pin macros, so the code was driving pins that were not connected to what I thought they were. The wiring itself was correct.

The second cause was more instructive. After finally getting the third LED working, the other two stopped. I had spent hours re-checking every solder joint and re-reading the code before realizing that in the process of swapping cables to isolate the fault, I had reconnected two of them to the wrong sockets. Changing them back fixed it immediately.

## Circuit design

I designed the schematic and PCB in KiCad. Each output LED is driven by a digital pin into an IRFZ44 MOSFET rather than directly from the microcontroller. A microcontroller pin is meant to carry a control signal, not to power a load: each I/O pin on the Nano Every can source only about 20 mA. The MOSFET separates those jobs, so the pin only has to charge the gate, which draws almost nothing, while the LED current comes from the regulated 5 V rail through a 1 kΩ series resistor. The same pattern shows up anywhere a microcontroller drives something bigger than itself, from motors to relays.

<div class="figure-row">
  <figure>
    <a href="/images/lightbox/SCHEMATIC.png" target="_blank">
      <img src="/images/lightbox/SCHEMATIC.png" alt="KiCad schematic" width="350">
    </a>
    <figcaption>Schematic (Click to enlarge).</figcaption>
  </figure>
  <figure>
    <img src="/images/lightbox/PCB-LAYOUT.png" alt="KiCad PCB layout" width="350">
    <figcaption>Single-sided PCB layout.</figcaption>
  </figure>
</div>

Single-sided routing meant every trace had to reach its destination on one layer, which made the ground pour the hard part. A pour is only useful if it stays continuous: route a signal across it in the wrong place and you cut off a region into an island that is no longer connected to ground. Most of the layout time went into ordering and positioning traces so the pour stayed whole. I ran ERC on the schematic and DRC on the layout throughout rather than only before submission, which is how I confirmed no regions were isolated and every net was actually connected rather than just visually adjacent.

I placed the Nano Every at the board edge because its USB connector is horizontal while the surrounding sockets and connectors sit tall and vertical. With the Nano in the middle of the board, those neighbouring parts would have blocked the plug. I also kept the board as small as the components allowed, to leave room for wire runs inside an enclosure I had not yet designed.

## Firmware

The firmware runs a state machine with interrupt-driven event handling, built in PlatformIO. Three outputs run concurrently at independent rates:

- Two eye LEDs, on for 5 seconds after a button press, brightness set by potentiometer via PWM
- One logo LED, on for 10 seconds, blinking at a rate set by a second potentiometer from 5 to 10 Hz
- An onboard heartbeat LED at 1 Hz, running in every state

<div class="figure-side">
  <figure>
    <img src="/images/lightbox/STATE-MACHINE.png" alt="State machine diagram showing IDLE, READ_ADC, CALC_ON_TIME, and the two-phase TOGGLE_LED output sequence">
  </figure>
  <div markdown="1">

The device sits in `IDLE` with only the heartbeat LED running. A button press moves it through two transient states, `READ_ADC` and `CALC_ON_TIME`, which sample both potentiometers and convert those readings into a PWM duty cycle for the eyes and a blink interval for the logo.

`TOGGLE_LED` then runs the output sequence: eyes and logo together for the first five seconds, logo alone for the next five, and back to `IDLE` at ten.

The heartbeat running in every state is the constraint that shapes the architecture. Nothing in the output sequence is allowed to block, because a blocking delay would stall the heartbeat and make the timing visibly wrong.

  </div>
</div>

One consequence of reading the ADCs once per press: turning a potentiometer mid-sequence has no effect until the next press. That was a deliberate reading of the specification, but continuous sampling would be the more natural behaviour for someone holding the device and turning a knob.

The button is handled by an interrupt rather than polled, and the ISR does exactly one thing: set the next state. There is no time-based debounce in the firmware, because the state machine makes one unnecessary. `READ_ADC` detaches the interrupt as its first action and `IDLE_EXIT` reattaches it once the sequence finishes, so contact bounce during the ten-second output has nothing to fire at. Bounce on the initial press is harmless for a different reason: a repeated ISR call only assigns `state = READ_ADC`, which is already the current state. One mechanism covers two requirements, since detaching the interrupt also enforces that a press mid-sequence is ignored rather than restarting it.

## Enclosure

I modelled the enclosure in OnShape and 3D printed it, sized to keep every linear dimension under 15 cm. The design work happened in two directions at once: the outside had to look like something, and the inside had to hold a PCB, a 9 V battery, and five panel-mounted components without any of them moving.

I designed the lid first as a shape I liked, then reused that sketch to extrude the box backwards and hollow it out, which guaranteed the two halves matched. The lid has two layers: an outer face carrying the design, and a thinner inner lip sized to slide into the box. I originally intended that lip as a snap fit. It was not one, and my professor was right to say so, so the halves are held with threaded heat-set inserts instead. That change also made the box openable repeatedly without wearing out the fit, which mattered more than I expected once debugging started.

### Where the time actually went

Cutting the holes for the potentiometers, switch, button and LEDs was the single most iterated part of the whole project, and for an avoidable reason: I had rescaled the figure several times during modelling, so I no longer knew what scale my sketch dimensions were in. Any measurement I typed came out subtly wrong. I eventually got every hole to fit by iterating, but the underlying lesson is that rescaling a model after you have started dimensioning features against it invalidates every number you have already committed to.

Aligning the lid holes to the box was the one part that went cleanly. I taped the underside of the lid, seated it on the box, and pushed a pen through each hole. The mark transferred position exactly, giving me a guide for drilling and for seating the inserts without measuring anything.

### Securing the internals

I had assumed the PCB and battery could sit loose inside the shell. They could not, and finding that out late meant redesigning the interior around components that were already fixed. Adapting an approach a teammate had used, I added a snap fit on the floor of the box to hold the battery, and four posts rising from just below where the board's mounting holes sit, with threaded inserts at the top so the PCB mounts flat above the battery. Getting the post positions right meant importing the PCB into the CAD model and measuring against it rather than guessing, and it needed a small change to the box outline to accommodate.

<div class="figure-row">
  <figure>
    <img src="/images/lightbox/InsidePCB.jpg" alt="PCB mounted on standoffs above the battery inside the enclosure" width="350">
    <figcaption>PCB mounted above the battery on threaded standoffs.</figcaption>
  </figure>
  <figure>
    <img src="/images/lightbox/CAD-INTERNALS.png" alt="CAD view showing the battery snap fit and PCB mounting posts" width="350">
    <figcaption>The same arrangement in CAD.</figcaption>
  </figure>
</div>

## Testing and results

I characterised the device against its specification using measured data rather than visual inspection, with eight samples per condition.

<div class="figure-row">
  <figure>
    <img src="/images/lightbox/EYE-BRIGHTNESS-PLOT.png" alt="Duty cycle against potentiometer voltage with linear fit, R squared 0.99995" width="350">
    <figcaption>Eye brightness against potentiometer voltage.</figcaption>
  </figure>
  <figure>
    <img src="/images/lightbox/BLINK-RATE-PLOT.png" alt="Blink rate against potentiometer voltage with linear fit, R squared 0.98893" width="350">
    <figcaption>Logo LED blink rate against potentiometer voltage.</figcaption>
  </figure>
</div>

**Eye brightness against potentiometer voltage** is strongly linear: y = 16.19x + 19.42, R² = 0.99995, slope 95% CI [16.07, 16.31].

**Heartbeat timing** held to specification in both states. Idle: mean 1.0021 Hz, SD 0.0024, 95% CI [1.00010, 1.00415]. During the output sequence: mean 1.0011 Hz, SD 0.00064, 95% CI [1.00059, 1.00166]. Both within 0.5% of the 1 Hz target, and the variance was actually lower while the eye PWM and logo blink were running, which confirms the non-blocking architecture: driving three outputs concurrently did not cost the heartbeat any timing accuracy.

### Two deviations, one cause

Measured brightness spans roughly 20% to 73% duty cycle, and blink rate spans 5.0 to 7.5 Hz. The specification asks for 0 to 100% and 5 to 10 Hz.

The lower brightness bound is deliberate: I set `EYE_MIN_BRIGHTNESS` to a PWM value of 50 because below that the LEDs are effectively invisible, and a control whose bottom fifth does nothing is worse than a narrower one. That floor is visible directly in the regression intercept, since 50/255 is 19.6% and the fit gives 19.42%.

Both upper bounds have the same cause, which I did not catch until analysing the data. The potentiometers are supplied from the 3.3 V rail while the ADC reference is VDD at 5 V, so full rotation only sweeps about two thirds of the ADC range and neither `map` call reaches its upper endpoint. 3.3/5 corresponds to roughly ADC 675, and `map(675, 0, 1023, 50, 255)` gives 185, or 72.5% duty cycle. I measured 72.8%. The fix is either supplying the potentiometers from 5 V or calling `analogReference(INTERNAL)` to match the reference to the actual input range.

### The blink-rate curve

Blink rate fits a line less well, R² = 0.98893, and the residuals curve systematically rather than scattering. That is not noise, it is the wrong model. The firmware maps the ADC linearly to a half period, and frequency is the reciprocal of period, so the true relationship is a hyperbola:

    f = 50 / (10 − V)

That model predicts every measured point within 0.03 Hz: 5.00 against 5.02 at 0 V, 5.88 against 5.90 at 1.5 V, 6.25 against 6.28 at 2.0 V, and 7.46 against 7.47 at 3.3 V. The apparent non-linearity is the firmware working exactly as written, and fitting a straight line to it was my error in analysis rather than a defect in the device.

## What I would do differently

Two things I would change are already covered above: supplying the potentiometers from the same rail as the ADC reference, and fitting the model the firmware actually implements rather than assuming linearity. The third is CAD discipline. Rescaling the figure mid-design cost me more hours than any electrical problem did, and the fix is simply to settle the overall size before dimensioning a single feature against it.

## Additional Resources

<div class="button-row">
  <a href="https://drive.google.com/file/d/1Oyo2Yig61s7r94PN0SATIG2fRzrDWWWT/view?usp=sharing" target="_blank" class="resource-link">Technical Report</a>
  <a href="images/lightbox" target="_blank" class="resource-link">CAD Design and Other Images</a>
  <a href="https://drive.google.com/file/d/1VgZQsWjYh7gtf-GQDh_f_wE7VAOO2NiW/view?usp=sharing" target="_blank" class="resource-link">Source Code</a>
  <a href="https://drive.google.com/file/d/1HkEIZk3AFVnCUBC4BZb21UNOI9UsR4C_/view?usp=sharing" target="_blank" class="resource-link">Demo Video</a>
</div>

[← Back to Home](/)
