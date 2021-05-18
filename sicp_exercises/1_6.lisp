#!/usr/bin/racket
#lang racket/base

(define (average x y) (/ (+ x y) 2))

(define (good-enough? guess radicand) (< (abs (- (* guess guess) radicand)) 0.001))

(define (improve guess radicand) (average guess (/ radicand guess)))

#| (define (sqrt-iter guess radicand) |#
#|   (if (good-enough? guess radicand) |#
#|       guess |#
#|       (sqrt-iter (improve guess radicand) radicand))) |#
#| (define (sqrt radicand) (sqrt-iter 1.0 radicand)) |#

(define (new-if predicate then-clause else-clause)
  (cond
    [predicate then-clause]
    [else else-clause]))

(define (sqrt-iter guess radicand)
  (new-if (good-enough? guess radicand)
          guess
          (sqrt-iter (improve guess radicand) radicand)))
(define (sqrt radicand) (sqrt-iter 1.0 radicand))

#| (sqrt 65536) |#

; new-if is a function and applicative-order evaluation results in
; the second operand of new-if, the sqrt-iter call in the else-clause, 
; calling itself recursively. Even if the guess is good, the next step 
; in the substitution modle for procedure evaluation is reached only 
; after the expressions for parameter are evaluated.
