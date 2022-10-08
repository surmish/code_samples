#!/usr/bin/racket
#lang racket/base

(define (sum f a next dx b k n)
  (cond
   ((= k n) (f a))
   ((= k 0) (+ (f a) 
               (sum f (next a dx) next dx b (+ k 1) n)))
   ((= (remainder k 2) 1) (+ (* 4.0 (f a))
                             (sum f (next a dx) next dx b (+ k 1) n)))
   (else (+ (* 2.0 (f a)) (sum f (next a dx) next dx b (+ k 1) n)))
   )
  )

(define (next a dx) (+ a dx))

(define (cube x) (* x x x))

(define (simpsons-method f a b n)
  (/ (* (sum f a next (/ (- b a) n) b 0 n) (/ (- b a) n)) 3.0)
  )

(simpsons-method cube 0 1 10)
(simpsons-method cube 0 1 100)
(simpsons-method cube 0 1 1000)
