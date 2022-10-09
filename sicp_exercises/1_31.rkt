#!/usr/bin/racket
#lang racket/base

; recursive
(define (product term a next b)
  (if (> a b) 1
      (* (term a) (product term (next a) next b))
      ))

; linear iterative
(define (product-iter term a next b)
  (define (iter a result) 
    (if (> a b)
        result
        (iter (next a) (* (term a) result))
      )
    )
  (iter a 1)
  )

(define (factorial n) (product-iter identity 1 inc n))
(define (pi-term a) (/ (* (* a 2.0) (* (+ a 1) 2)) (square (+ (* 2 a) 1))))
(define (square x) (* x x))
(define (inc a) (+ a 1))
(define (identity a) a)

(product      identity 1 inc 5)
(product-iter identity 1 inc 5)

(* 4 (product      pi-term 1 inc 10000))
(* 4 (product-iter pi-term 1 inc 10000))
