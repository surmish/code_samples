#!/usr/bin/racket
#lang racket/base

(define (a-plus-abs-b  a b)
  ((if (> b 0) + -) a b))

(a-plus-abs-b 0 3)
(a-plus-abs-b 0 -3)
(a-plus-abs-b 0 0)

; if b is positive, add a and b
; if b is non-positive, subtract b from a
