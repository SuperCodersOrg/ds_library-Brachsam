# Session 2
**Date:** June 25

## Duration: 
2:00 p.m. – 4:00 p.m. (2 Hours)

## Goal

Complete advanced HashMap functionality and perform comprehensive testing.

## Problem Encountered

Rehashing required redistributing every existing key-value pair into a larger bucket array while preserving all mappings. I also needed to verify that advanced helper functions continued to work correctly after resizing.

## What I Tried

Implemented:

- rehash()
- keys()
- values()
- merge()
- print()

Created comprehensive test cases covering:

- Automatic resizing and rehashing
- Updating existing keys
- Multiple key and value data types
- User-defined key hashing (Point)
- keys() and values()
- merge()
- Load factor validation
- Retrieval after resizing

## Outcome

Successfully completed the first working version of the HashMap implementation.

Verified that:

- Rehash preserves all existing key-value mappings.
- Bucket count doubles after the load factor threshold is exceeded.
- keys() and values() return the expected collections.
- merge() inserts only missing keys.
- Primitive, string, and user-defined key types are supported.
- Comprehensive test cases were created to validate all implemented operations.