#!/usr/bin/racket
#lang racket/base

(define (sum_of_squares a b)
  (+ (* a a)
     (* b b)))

(define (sum_of_squares_of_two_larger_numbers a b c)
  (if (> a b)
      (if (> b c)
          (sum_of_squares a b)
          (sum_of_squares a c))
      (if (> a c)
          (sum_of_squares a b)
          (sum_of_squares b c))))

(sum_of_squares_of_two_larger_numbers 3 5 7)
(sum_of_squares_of_two_larger_numbers 3 7 5)
(sum_of_squares_of_two_larger_numbers 5 3 7)
(sum_of_squares_of_two_larger_numbers 5 7 3)
(sum_of_squares_of_two_larger_numbers 7 3 5)
(sum_of_squares_of_two_larger_numbers 7 5 3)
