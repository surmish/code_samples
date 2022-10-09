#!/usr/bin/racket
#lang racket/base

(define (accumulator combiner null-value term a next b)
  (if (> a b) null-value
      (combiner (term a) (accumulator combiner null-value term (next a) next b))
      )
  )

(define (accumulator-iter combiner null-value term a next b)
  (define (iter a result) 
    (if (> a b)
      result
      (iter (next a) (combiner (term a) result))
    ))
  (iter a null-value)
  )

(define (pi-sum a b)
  (accumulator + 0 (lambda (x) (/ 1.0 (* x (+ x 2))))
       a
       (lambda (x) (+ x 4))
       b)
  )

(define (pi-sum-iter a b)
  (accumulator-iter + 0 (lambda (x) (/ 1.0 (* x (+ x 2))))
       a
       (lambda (x) (+ x 4))
       b)
  )

(define (integral f a b dx )
  (* (accumulator + 0 f
          (+ a (/ dx 2.0))
          (lambda (x) (+ x dx))
          b)
     dx)
  )
(define (integral-iter f a b dx )
  (* (accumulator-iter + 0 f
          (+ a (/ dx 2.0))
          (lambda (x) (+ x dx))
          b)
     dx)
  )

(define (cube x) (* x x x))
(define (square x) (* x x))
(define (pi-product-term a) (/ (* (* a 2.0) (* (+ a 1) 2)) (square (+ (* 2 a) 1))))
(define (inc a) (+ a 1))
(define (identity a) a)

(printf "linear recursive sum of cubes(3): ~a\n" (accumulator      + 0 cube 1 inc 3))
(printf "linear iterative sum of cubes(3): ~a\n" (accumulator-iter + 0 cube 1 inc 3))

(printf "linear recursive sum of integers(10): ~a\n" (accumulator      + 0 identity 1 inc 10))
(printf "linear iterative sum of integers(10): ~a\n" (accumulator-iter + 0 identity 1 inc 10))

(printf "linear recursive pi-sum (200000 terms): ~a\n" (* 8 (pi-sum      1 200000)))
(printf "linear iterative pi-sum (200000 terms): ~a\n" (* 8 (pi-sum-iter 1 200000)))

(printf "linear recursive integral (dx = 0.0001): ~a\n" (integral      cube 0 1 0.0001))
(printf "linear iterative integral (dx = 0.0001): ~a\n" (integral-iter cube 0 1 0.0001))

(printf "linear recursive factorial(5): ~a\n" (accumulator      * 1 identity 1 inc 5))
(printf "linear iterative factorial(5): ~a\n" (accumulator-iter * 1 identity 1 inc 5))

(printf "linear recursive pi-product: ~a\n" (* 4 (accumulator      * 1 pi-product-term 1 inc 10000)))
(printf "linear iterative pi-product: ~a\n" (* 4 (accumulator-iter * 1 pi-product-term 1 inc 10000)))
