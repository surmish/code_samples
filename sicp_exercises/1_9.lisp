#!/usr/bin/racket
#lang racket/base

(define (inc x) (- x -1))
(define (dec x) (- x 1))

(define (+ a b)
  (if (= a 0) b (inc (+ (dec a) b))))
; this is a linear recursive process since the increment operation
; occurs during a 'contraction'. The state of the process is stored
; not just in the variables, a and b, but also in the 'recursion'
; stack

(define (+-2 a b)
  (if (= a 0) b (+-2 (dec a) (inc b))))
; this is a tail-recursive implementation (iterative process), since
; the state of the process is stored in a and b at any given time and
; can be used to compute the result of the process.

