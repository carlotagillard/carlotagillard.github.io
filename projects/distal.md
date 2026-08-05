---
layout: default
title: Distal Forearm Fracture Model
---

**Team:** C. Gillard, C. Hanby, A. He, R. Rohr

**Tools:** OnShape, 3D printing, mechanical testing, Likert-scale user studies

<style>
  .project-name { font-size: clamp(1.75rem, 4vw, 2.5rem); }
  .project-tagline { display: none; }
</style>

<div class="figure-center">
  <figure>
    <a href="/PosterFinal.pdf" target="_blank">
      <img src="/images/distal/final-poster.png" alt="Final project poster for the 4Arms Colles distal forearm fracture reduction model" width="700">
    </a>
    <figcaption>Final project poster. Click for the full PDF.</figcaption>
  </figure>
</div>

## Overview

A Colles fracture is one of the most common wrist injuries, and residents need to practice reducing one before they do it on a patient. The training models hospitals can buy are expensive, fragile, and anatomically inaccurate, which makes them hard to justify investing in.

Dr. Josh Broder and engineer David Mercer asked our team to take an existing prototype and turn it into something Duke Hospital could actually train on. That prototype had a 3D-printed hand and forearm with a spring to replicate force and a "step" mechanism to mimic the fracture, but it moved horizontally in a way a real reduction does not, and it let a resident reach the end position without performing the correct sequence of motions. It taught the destination, not the manuver.

## Designing without a reference

The existing prototype gave us a printed hand and forearm and a force mechanism.
Everything that does the training, the part that decides what motion the user is required to perform, we had to design from nothing.

The real difficulty was not mechanical. None of us had ever performed a reduction or watched one performed in person. Our references were YouTube videos not detailed enough to teach a surgical resident, and one conversation with Dr. Broder, who sketched the movement for us and demonstrated it on a volunteer's hand. He could only approximate it: performing the actual manoeuvre at the force it requires would have injured the person he was demonstrating on. So the target motion, the thing our entire mechanism had to enforce, was something we had never directly observed and could not have observed safely.

We worked forward from that anyway. Early versions kept the original step mechanism and tried to constrain it further, which never resolved the underlying problem that a step tells you where to finish rather than how to get there. The maze came out of abandoning that approach entirely, and then we iterated the maze itself dozens of times, varying both the path shape and how it was built, before arriving at the version that felt right to the physicians who tested it.

## The mechanism

The core of our redesign is a **guided maze**. A square metal rod attached to the hand travels along a set of maze path walls inside the forearm, so the hand can only reach the reduced position by moving through the correct sequence: the geometry enforces the trajectory rather than merely permitting it.

Force comes from a tensioned wire pulling the rod in the opposite direction, so the resident feels resistance that has to be overcome, the way a real reduction does. A removable neoprene sleeve covers the fracture zone and gives the model a skin-like surface.

<div class="figure-row">
  <figure>
    <img src="/images/distal/final vertical fractured.jpg" alt="The final model in its fractured state" width="350">
    <figcaption>The final model in its fractured state.</figcaption>
  </figure>
  <figure>
    <img src="/images/distal/TeamPicture.png" alt="The four-person design team" width="350">
    <figcaption>The team.</figcaption>
  </figure>
</div>

## My role

I did most of the mechanical design. The team generated ideas together, but the two decisions that define how the device works were mine.

**The rod profile.** The original mechanism used a circular rod. In theory the maze forces the hand along the correct path, but a circle lets the hand rotate freely around it, so a user could keep the wrist straight and simply wiggle and pull the hand through. The path was technically still being followed, but none of the flexion and extension the real manoeuvre demands was required, which means the maze was training nothing. Switching to a square rod gave the mechanism flat faces to bear against, locking the wrist orientation to the path. Now the only way through is the motion itself.

**The maze path itself.** I designed the geometry that enforces the reduction sequence, then iterated it physically: printing a version, sanding, assembling, testing the motion by hand, and going back to CAD. That print, sand, assemble, test, revise loop ran dozens of times across the semester, and I ran most of them. The maze went through roughly fifty variations in shape and construction before we settled.

## Testing

We defined five criteria with numeric targets and tested each one rather than assessing the model by eye.

| Criterion | Method | Target | Result |
|---|---|---|---|
| Accurate mechanism | 8 physicians, 10 reductions each, 10-point scale | ≥ 8.0 | **8.3 pass** |
| Accurate forces | Same physicians, 10-point scale | ≥ 8.0 | **8.1 pass** |
| Safety | 20 students, 5-point scale | ≥ 4.5 | **4.9 pass** |
| Durability | Repeated reduction and reset, 3-point scale | ≥ 2.8 | **2.8 pass** |
| Easy reset | 20 students timed | < 5 s | **10.3 s fail** |
| Realism | 35 blindfolded participants, 5-point scale | ≥ 3.5 | **3.1 fail** |

<div class="figure-row">
  <figure>
    <img src="/images/distal/Testing at Hospital.jpeg" alt="Emergency physicians reducing the model" width="350">
    <figcaption>Physicians attempting a reduction on the model.</figcaption>
  </figure>
  <figure>
    <img src="/images/distal/BroderTestWResidents.jpeg" alt="Broder and a resident using the model" width="350">
    <figcaption>Dr. Broder with a resident using the model arm.</figcaption>
  </figure>
</div>

Given that we designed the motion from secondhand references, the physician ratings were the only real validation available: they were the first people to assess the mechanism who had actually performed the procedure.

The two criteria that mattered most both passed: physicians rated both the motion and the force as accurate, which was the whole point of replacing the one-step mechanism with the maze.

### The two failures

**Reset took 10.3 seconds against a 5 second target**, more than double. That matters more than it sounds: a training device that takes ten seconds to reset between attempts halves how many reductions a resident can practice in a session. The maze is what causes it, since the rod has to travel back through the same constrained path that makes the device work in the first place. Fixing it means finding a way to release the rod without discarding the guidance.

**Realism scored 3.1 against a 3.5 target** with 35 blindfolded participants. The mechanism feels right and the material does not: rigid printed plastic under a neoprene sleeve is not skin. Silicone over the fracture zone is the obvious next step.

## Future work

Beyond the two failures, the team identified two directions: an automated mechanism for calibrating and adjusting the resistance force, so the same device could simulate fractures of different severity, and a titanium maze in place of plastic to extend the life of the part that takes the most wear. 

## Additional Resources

<div class="button-row">
  <a href="https://cad.onshape.com/documents/eb6e289ed05d07266b6ba426/w/ca134d3ec821955ecd2be735/e/05d6ec63819e9a8e71cf58d3" target="_blank" class="resource-link">OnShape Model</a>
  <a href="https://youtu.be/4MaEyghUxlk" target="_blank" class="resource-link">Prototype Video</a>
  <a href="https://github.com/carlotagillard/carlotagillard.github.io/tree/main/images/distal" target="_blank" class="resource-link">All Photos</a>
  <a href="/PosterFinal.pdf" target="_blank" class="resource-link">Final Poster</a>
</div>

[← Back to Home](/)
