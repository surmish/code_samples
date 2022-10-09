#!/usr/bin/racket
#lang racket/base

(define (product term a next b)
  (if (> a b) 1
      (* (term a) (product term (next a) next b))
      ))

(define (factorial n) (product identity 1 inc n))
(define (pi-term a) (/ (* (* a 2.0) (* (+ a 1) 2)) (square (+ (* 2 a) 1))))
(define (square x) (* x x))
(define (inc a) (+ a 1))
(define (identity a) a)

(factorial 5)
(* 4 (product pi-term 1 inc 10000))
