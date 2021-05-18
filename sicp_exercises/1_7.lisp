#!/usr/bin/racket
#lang racket/base

(define (average x y) (/ (+ x y) 2))

(define (good-enough? guess radicand) (< (abs (- (* guess guess) radicand)) 0.001))

(define (improve guess radicand) (average guess (/ radicand guess)))

(define (sqrt-iter guess radicand number-of-iterations)
  (cond ((good-enough? guess radicand) (printf "result: ~a, iterations: ~a, and "
                                               guess number-of-iterations ) guess)
        (else (sqrt-iter (improve guess radicand)
                         radicand
                         (+ number-of-iterations 1)))))

(define (sqrt-impl radicand) (sqrt-iter 1.0 radicand 1))

(define (error-in-sqrt-impl radicand)
  (printf "Radicand: ~a, " radicand )
  (- (sqrt radicand)
     (sqrt-impl radicand)))
(define (process radicand) (printf "error: ~a\n" (error-in-sqrt-impl radicand)))

(process 0.0000000001)
(process 0.000000001)
(process 0.00000001)
(process 0.0000001)
(process 0.000001)
(process 0.00001)
(process 0.0001)
(process 0.001)
(process 0.01)
(process 0.1)
(process 1)
(process 10)
(process 100)
(process 1000)
(process 10000)
(process 100000)
(process 1000000)
(process 10000000)
(process 100000000)
(process 1000000000)
(process 10000000000)

; For large radicands, the number of recursive calls to sqrt-iter keep but the returns
; becoming diminishing since the error between the calculated value and the actual value
; become negligible.
; For smaller radicands, the number of iterations remains the same since the successive
; guesses fall within the error margin defined in the 'improve-guess' procedure. Once
; the guess becomes good enough, the result is returned. This result deviates from the actual
; square root when the radicand gets smaller.

; A better solution would be to ensure that the differences between successive guesses get
; within a tolerable range, w.r.t to the current guess
; For large radicands, this approach would result in fewer recursive calls, while keeping the
; error within margin
; For small radicals, this approach would result in 
