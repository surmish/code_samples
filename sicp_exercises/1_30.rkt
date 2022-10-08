#!/usr/bin/racket
#lang racket/base

(define (sum term a next b)
  (define (iter a result)
    (if (> a b) 
      result
      (iter (next a) (+ (term a) result)  )
      )
    )
  (iter a 0)
  )

(define (sum-cubes a b)
  (sum (lambda (x) (* x x x))
       a
       (lambda (x) (+ x 1))
       b)
  )

(define (sum-integers a b)
  (sum (lambda (x) x)
       a
       (lambda (x) (+ x 1))
       b)
  )

(define (pi-sum a b)
  (sum (lambda (x) (/ 1.0 (* x (+ x 2))))
       a
       (lambda (x) (+ x 4))
       b)
  )

(define (integral f a b dx )
  (* (sum f
          (+ a (/ dx 2.0))
          (lambda (x) (+ x dx))
          b)
     dx)
  )

(sum-cubes 1 3)
(sum-integers 1 10)
(* 8 (pi-sum 1 200000))

(integral (lambda (x) (* x x x)) 0 1 0.01)
(integral (lambda (x) (* x x x)) 0 1 0.001)
(integral (lambda (x) (* x x x)) 0 1 0.0001)
