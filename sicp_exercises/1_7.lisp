#!/usr/bin/racket
#lang racket/base

(define (average x y) (/ (+ x y) 2))
(define (good-enough? guess radicand) (< (abs (- (* guess guess) radicand)) 0.001))
(define (improve guess radicand) (average guess (/ radicand guess)))
(define (sqrt-iter guess radicand number-of-iterations)
  (cond ((good-enough? guess radicand) (printf "\n  result: ~a, iterations: ~a, and "
                                               guess number-of-iterations ) guess)
        (else (printf "\n  guess is: ~a" guess) (sqrt-iter (improve guess radicand)
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
(process 100000000000)

; For large radicands, the number of recursive calls to sqrt-iter keep increasing but 
; the returns becoming diminishing since the error between the calculated value and the 
; actual value become negligible (w.r.t the guess).
; For smaller radicands, the number of iterations remains the same since the successive
; guesses fall within the error margin defined in the 'improve-guess' procedure. Once
; the guess becomes good enough, the result is returned. This result deviates from the actual
; square root when the radicand gets smaller. 
; Since the error tolerance is a fixed number independent of the size of the radicand, the 
; error of the guessed result and the actual result is very high.

; A better solution would be to compare successive guesses and keep the difference within
; a fraction of the guessed value.
; For large radicands, this approach would result in fewer recursive calls.
; For small radicands, this will lead to more recursive calls 

(define (calc-guess guess old-guess) (if (= old-guess 0) guess (/ (abs(- old-guess guess)) old-guess)))
(define (good-enough-2? guess old-guess) (< (calc-guess guess old-guess)  0.01))
(define (sqrt-iter-2 guess radicand number-of-iterations old-guess)
  (cond ((good-enough-2? guess old-guess) (printf "\n  result: ~a, iterations: ~a, and " guess number-of-iterations ) guess)
        (else (printf "\n  guess is: ~a" guess) (sqrt-iter-2 (improve guess radicand) radicand (+ number-of-iterations 1) guess))))

(define (sqrt-impl-2 radicand) (sqrt-iter-2 1.0 radicand 1 0))

(define (error-in-sqrt-impl-2 radicand)
  (printf "Radicand: ~a, " radicand )
  (- (sqrt radicand)
     (sqrt-impl-2 radicand)))
(define (process-2 radicand) (printf "error: ~a\n" (error-in-sqrt-impl-2 radicand)))

(process-2 0.0000000001)
(process-2 0.000000001)
(process-2 0.00000001)
(process-2 0.0000001)
(process-2 0.000001)
(process-2 0.00001)
(process-2 0.0001)
(process-2 0.001)
(process-2 0.01)
(process-2 0.1)
(process-2 1)
(process-2 10)
(process-2 100)
(process-2 1000)
(process-2 10000)
(process-2 100000)
(process-2 1000000)
(process-2 10000000)
(process-2 100000000)
(process-2 1000000000)
(process-2 10000000000)
(process-2 100000000000)

