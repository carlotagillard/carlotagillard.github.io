---
layout: default
title: Sleep Study Signal Analysis
---

<style>
  .project-name { font-size: clamp(1.75rem, 4vw, 2.5rem); }
  .project-tagline { display: none; }
</style>

**Tools:** Python, SciPy, NumPy, matplotlib

## Overview
Sleep studies diagnose disorders like apnea and hypoxia by recording several physiological signals at once while a patient sleeps. This project takes those recordings, ECG, blood pressure, respiration, and blood oxygen saturation, and analyses them together: detecting events in each signal, then combining the results into a single assessment and a PDF report.

Analysing the signals separately is straightforward. The point of the system is that a diagnosis depends on how they interact, since a drop in oxygen saturation means something different depending on what breathing and heart rate were doing at the same moment.

## What I built

I owned two pieces of a four-person project.

**Blood oxygen saturation analysis.** Duration of the trace, minimum and maximum saturation, and detection of hypoxia episodes where saturation dropped below 85%, including the length of each episode. Results exported as JSON for the reporting layer to consume.

**The user interface and report generation.** A file selection dialog and a time-window prompt feeding the analysis pipeline, which produces a PDF report with plots of all four signals over the selected window. My teammates each owned one signal analyser; everything outside those four modules was mine.

## Validation

I checked each variable against the raw data before it reached the JSON output rather than trusting the pipeline end to end. Across the team, detected events were verified by comparing timestamps against peaks on the plotted signals, which is how we confirmed the detection was finding real features and not artifacts.

The code is in a private course repository and not publicly available.

## Results

Across three patient traces, the episode-length measurement turned out to matter more than the count. Patient 1 recorded 20 hypoxia episodes over 1200 seconds, none longer than 11 seconds. Patient 3 recorded a single episode, but it lasted 398 seconds, roughly 28% of the recording. Counting events alone would have ranked patient 3 as the least affected of the three; measuring duration shows the opposite.

All three patients' outputs were verified value by value against the instructor's reference results.

One boundary case is worth noting even so. Episode length is measured from the first sample below threshold to the last sample below it, so a single-sample dip reports as zero seconds, and patient 1's output contains one of those. Measuring to the first sample back above threshold instead would give it a duration of one sampling interval. Both definitions are defensible, but I would now define that boundary explicitly rather than letting it fall out of the loop structure.

[← Back to Home](/)
