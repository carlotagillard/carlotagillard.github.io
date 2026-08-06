---
layout: default
title: Technical Explorations & Skill-Building
---

<style>
  .project-name { font-size: clamp(1.75rem, 4vw, 2.5rem); }
  .project-tagline { display: none; }
</style>

## On this page

- [2D Blueprint to 3D CAD Reproduction](#2d-blueprint-to-3d-cad-reproduction)
- [Laser-Cut Phone Stand and Box](#laser-cut-acrylic-phone-stand-and-cardboard-box)
- [CAD to Cast Part](#cad-to-cast-part)
- [First CAD Project: Pen and Desk Organizer](#first-cad-project-pen-and-desk-organizer)

## 2D Blueprint to 3D CAD Reproduction

**Tools:** OnShape

<div class="figure-center">
  <figure>
    <img src="/images/6YO/load-cell-instructions.png" alt="Provided 2D engineering drawing of the load cell" width="600">
    <figcaption>The 2D drawing provided as a guide.</figcaption>
  </figure>
</div>

<div class="figure-center">
  <figure>
    <img src="/images/6YO/load-cell-carlota.jpeg" alt="My 2D drawing of the reproduced load cell" width="500">
    <figcaption>My drawing of the reproduced part.</figcaption>
  </figure>
</div>

Reproducing a load cell from the Hybrid III 6-year-old crash test dummy, working from a multi-view 2D engineering drawing to a 3D model. The exercise is less about modeling speed than about reading: inferring a feature's geometry from two or three orthographic views, and building the model so that design intent survives. A model that merely looks correct will break the moment a dimension changes; one built with proper constraints and relationships updates cleanly.

This was the most complex part in a series of reproduction exercises working from 2D engineering drawings.

## Laser-Cut Acrylic Phone Stand and Cardboard Box

**Tools:** Adobe Illustrator, laser cutter, acrylic bender

I designed both pieces as vector cut files in Adobe Illustrator, then cut and engraved them on a laser cutter.

<div class="figure-row">
  <figure>
    <img src="/images/SkillBuilding/Dimensioned Drawings and Self Assesment.pdf" alt="Hand sketch of the phone stand with dimensions" width="350">
    <figcaption>Phone stand: initial sketch with dimensions.</figcaption>
  </figure>
  <figure>
    <img src="/images/SkillBuilding/phone stand.ai" alt="Illustrator cut file for the phone stand" width="350">
    <figcaption>Phone stand: the Illustrator cut file.</figcaption>
  </figure>
</div>

The acrylic stand was heat-bent to shape after cutting, which meant the flat pattern had to account for where the bends would go: the part is designed flat but has to be correct once it is no longer flat.

<div class="figure-center">
  <figure>
    <img src="/images/SkillBuilding/CarlotaGillardBox.ai" alt="Illustrator cut file for the cardboard box" width="500">
    <figcaption>Box: the cut and engrave file.</figcaption>
  </figure>
</div>

The box is a flat pattern too, designed so that once cut the pieces could fit into each other like puzzle pieces.

## CAD to Cast Part

**Tools:** OnShape, 3D printing, Oogoo silicone casting

I modeled a keychain in OnShape, printed it, and used the printed part as a master to cast a mould from it.

<div class="figure-row">
  <figure>
    <img src="/images/SkillBuilding/Tool Bits 2 _ Carlota Gillard.pdf" alt="OnShape model of the keychain" width="350">
    <figcaption>The OnShape model.</figcaption>
  </figure>
  <figure>
    <img src="/images/SkillBuilding/IMG_0100.jpeg" alt="The finished cast keychain" width="350">
    <figcaption>The finished cast part.</figcaption>
  </figure>
</div>

The main difficulty was avoiding trapped air: making sure no bubbles formed while mixing and pouring, and that the material reached every part of the mould rather than bridging over the finer detail. Both failures show up the same way, as voids in the finished part, and both come down to how you pour rather than what you pour.

The cast came out imperfect, and I sanded it back until it matched the original design closely. The two things I would change are related: the holes in the peace sign were too small, and I would pour the Oogoo differently to reduce trapped air. Both produce the same failure, voids where material should be, and both are more likely when the material has to reach into fine features.

The same casting approach came back later on the distal forearm fracture model, where we cast a test piece to see whether a moulded skin was worth pursuing. It tore almost immediately, and we moved on to neoprene.

<div class="figure-row">
  <figure>
    <img src="/images/SkillBuilding/IMG_9689.jpeg" alt="Casting the skin for the fracture model" width="350">
  </figure>
  <figure>
    <img src="/images/SkillBuilding/IMG_9703.jpeg" alt="The cast skin for the fracture model" width="350">
  </figure>
</div>

## First CAD Project: Pen and Desk Organizer

**Tools:** SolidWorks

My first CAD project, modeled in SolidWorks in an internship at Weo during high school. Rather than copying an existing design, I started from what was wrong with the organizers I already owned. Alongside the usual compartments for pens, pencils and highlighters, I added a thin extra-deep pocket for rulers, which had always ended up lying across everything else and getting in the way. Sizing a compartment around the thing that annoyed me turned out to be the whole design.

## Java Coursework

Data structures and algorithms in Java: lists, trees, sets, maps, and graphs, with an emphasis on abstract data types and recursion.

[← Back to Home](/)
