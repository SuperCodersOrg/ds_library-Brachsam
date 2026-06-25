# Session 2

**Date:** Date: June 25

## Duration: 
10:30 a.m. – 1:00 p.m. (2 Hours 30 Minutes)

## Goal

Implement the core HashMap operations and collision handling.

## Problem Encountered

While implementing insertion, I needed to ensure duplicate keys updated existing values instead of creating multiple entries. I also had to design collision handling that minimized probe lengths while still supporting overflow through chaining.

## What I Tried

Implemented:

- Constructor
- Destructor
- size()
- loadFactor()
- set()
- get()
- exists()
- remove()

Implemented hybrid bounded probing with chaining fallback for collision resolution.

Created test cases for:

- Insertions
- Updating existing keys
- Key lookup
- Existence checks
- Removal
- Collision handling
- Outcome

Successfully completed all core HashMap operations.

Verified that:

- Existing keys update correctly.
- Duplicate entries are avoided.
- Collision handling works using bounded probing with chaining fallback.
- Load factor updates after insertions and removals.
- Key lookup returns the expected values.