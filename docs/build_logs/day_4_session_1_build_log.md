# Session 1

**Date:** June 25

**Duration:** 9:00 a.m. – 10:30 a.m. (1 Hour 30 Minutes)

## Goal

Design the HashMap architecture and implement hashing support for different key types.

## Problem Encountered

Designing a generic hashing mechanism that could support multiple primitive, string, and user-defined key types while keeping the HashMap implementation reusable was initially challenging.

## What I Tried

Implemented:

* Generic `Hash<K>` template
* Hash specializations for:

  * `int`
  * `char`
  * `float`
  * `double`
  * `string`
  * `const char*`
* `Pair<K, V>` structure for storing key-value entries
* Helper functions:

  * `error()`
  * `homeIndex()`

Created small test cases to verify that different key types generated valid bucket indices.

## Outcome

Successfully completed the hashing framework.

Verified that:

* All implemented hash specializations correctly map supported key types to bucket indices.
* Hash specializations are selected automatically by the compiler.
* Key-value pairs can be stored independently of the hashing logic.