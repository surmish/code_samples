#!/usr/bin/racket
#lang racket/base

(define (p) (p))

(define (test x y)
  (if (= x 0)
      0
      y))

(test 0 (p))

; In applicative-order evaluation, the operand combinations are all evaluated at each
; step in the substitution model for procedure application. The compiler then tries to
; evaluate (p) which is defined as (p), thus entering an infinite loop resulting from
; recursive calls. The infinite loop can be clearly seen if (p) is defined as follows:
; (define (p) ((print "here") (p)))
